# Copyright (C) 2011 Michal Zielinski (michal@zielinscy.org.pl)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

import httplib
import urllib
import os
import re
import collections

ListEntry = collections.namedtuple('ListEntry', 'sha1 source date size name')

HOST = 'freeciv.zielinscy.org.pl'
API_VERSION = '1'
USER_AGENT = 'CivSyncGeneric/1'

minimal_wait = 10

class RequestError(Exception):
    pass

class LoginError(RequestError):
    pass

class UpdateRequiredError(RequestError):
    def __init__(self, url):
        RequestError.__init__(self, url)
        self.url = url

class Session(object):
    def __init__(self, sessid=None):
        self._sessid = sessid
        self._proxy_re = None
        self._proxy_host = None
    
    @property
    def sessid(self):
        if self._sessid == None:
            raise LoginError('Not logged')
        return self._sessid
    
    def is_logged(self):
        return bool(self._sessid)
    
    def login(self, login, password):
        self._login_or_register('/login.cgi', make_payload(login=login, password=password))
    
    def register(self, login, password, mail):
        self._login_or_register('/register.cgi', make_payload(login=login, password=password, mail=mail))
    
    def logout(self, all=False):
        url = '/logout.cgi'
        if all:
            url += '?all=true'
        self._request(url)
        self._sessid = None
    
    def upload(self, source, name, content):
        url = '/sync/upload?source=%s&name=%s' % (source, name)
        upload =  _Upload(url, content, 'fcsession=%s' % self.sessid, host=self.get_host(url))
        upload.header()
        return upload
    
    def upload_content(self, source, name, content):
        self.upload(source, name, content).send_all_console()
    
    def upload_log(self, content, install_time):
        url = '/sync/log_upload?time=%s' % install_time
        upload =  _Upload(url, content, 'fcsession=%s' % self._sessid)
        upload.header()
        upload.send_all_console()
    
    def download(self, sha1):
        return self._request('/sync/download?sha1=%s' % sha1)
    
    def download_content(self, sha1):
        return self.download(sha1).read()
    
    def list(self):
        l = []
        for line in self._request('/sync/list').read().splitlines():
            sha1, source, date, size, name = line.split(None, 4)
            l.append(ListEntry(sha1, source, int(date), int(size), name))
        return l
    
    def updates(self, install_time):
        return request('/sync/updates?install_time=%d' % install_time, strict_update=True)
    
    def _login_or_register(self, url, payload):
        set_cookie = request(url, payload, return_cookie=True, host=self.get_host(url))
        if not set_cookie.startswith('fcsession='):
            raise ValueError('Invalid set-cookie (%r).' % set_cookie)
        set_cookie = set_cookie[len('fcsession='):]
        if ';' in set_cookie:
            set_cookie, _ = set_cookie.split(';', 1)
        set_cookie = set_cookie.strip()
        self._sessid = set_cookie
    
    def _request(self, url, payload=None):
        return request(url, payload, self.sessid, host=self.get_host(url))
    
    def get_host(self, url):
        if url.startswith('/sync/updates'):
            return HOST
        if not self._proxy_re:
            proxy_re, self._proxy_host = request('/sync/get_proxy', None, None, host=HOST).read().splitlines()
            self._proxy_re = re.compile(proxy_re)
        if self._proxy_re.match(url):
            host = self._proxy_host
        else:
            host = HOST

def check_response(response, headers, strict_update=False):
    if 'x-login-error' in headers:
        raise LoginError(headers['x-login-error'])
    if 'x-request-error' in headers:
        raise RequestError(headers['x-request-error'])
    if 'x-update' in headers:
        update = headers['x-update']
        type, url = update.split(';')
        type = type.strip()
        url = url.strip()
        if strict_update or type == 'required':
            raise UpdateRequiredError(url)
    if 'x-minimal-wait' in headers:
        new_wait = int(headers['x-minimal-wait'])
        global minimal_wait
        minimal_wait = new_wait
    if response.status not in (200, 301, 302):
        print '=== Server returned error ==='
        print response.read()
        print '============================='
        raise RequestError('Invalid HTTP status code %d.' % response.status)

def request(url, payload=None, sessid=None, return_cookie=False, strict_update=False, host=None):
    conn = httplib.HTTPConnection(host or HOST)
    headers = {}
    headers['x-user-agent'] = USER_AGENT
    headers['x-api-version'] = API_VERSION
    if sessid:
        headers['cookie'] = 'fcsession=' + sessid
    conn.request('POST' if payload else 'GET', url, body=payload, headers=headers)
    response = conn.getresponse()
    headers = dict(response.getheaders())
    check_response(response, headers, strict_update=strict_update)
    if return_cookie:
        try:
            return headers['set-cookie']
        except KeyError:
            raise RequestError('Cookie not set.')
    else:
        return response

def encode_multipart_formdata(value):
    BOUNDARY = '----------' + os.urandom(10).encode('hex')
    CRLF = '\r\n'
    L = []
    L.append('--' + BOUNDARY)
    L.append('Content-Disposition: form-data; name="content"; filename="void"')
    L.append('Content-Type: application/x-freeciv-save')
    L.append('')
    L.append(value)
    L.append('--' + BOUNDARY + '--')
    L.append('')
    body = CRLF.join(L)
    content_type = 'multipart/form-data; boundary=%s' % BOUNDARY
    return content_type, body

class _Upload(object):
    def __init__(self, url, data, cookie, host):
        self.url = url
        self.content_type, self.data = encode_multipart_formdata(data)
        self.cookie = cookie
        self.host = host
        self.i = 0
    
    def header(self):
        self.h = httplib.HTTPConnection(self.host)
        self.h.putrequest('POST', self.url)
        self.h.putheader('content-type', self.content_type)
        self.h.putheader('content-length', str(len(self.data)))
        self.h.putheader('x-user-agent', USER_AGENT)
        self.h.putheader('x-api-version', API_VERSION)
        self.h.putheader('cookie', self.cookie)
        self.h.endheaders()
    
    def send_part(self):
        bs = 1024 * 10
        data = self.data[self.i: self.i + bs]
        self.i += bs
        
        self.h.send(data)
        
        if self.i >= len(self.data):
            return 1
        else:
            return float(self.i) / len(self.data)
    
    def finish(self):
        response = self.h.getresponse()
        headers = dict(response.getheaders())
        check_response(response, headers)
    
    def send_all(self, callback):
        while True:
            status = self.send_part()
            callback(status)
            if status == 1:
                self.finish()
                break
            
    
    def send_all_console(self):
        def wr(perc):
            print '%.2f %%' % (perc*100)
        self.send_all(wr)
    
    
def make_payload(**args):
    return urllib.urlencode(dict(**args))

    