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
import collections

ListEntry = collections.namedtuple('ListEntry', 'sha1 source date size name')

HOST = 'freeciv.zielinscy.org.pl'

class RequestError(Exception):
    pass

class LoginError(RequestError):
    pass

class Session(object):
    def __init__(self, sessid=None):
        self._sessid = sessid
    
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
        url = '/sync.cgi?mode=upload&source=%s&name=%s' % (source, name)
        upload =  _Upload(url, content, 'fcsession=' + self.sessid)
        upload.header()
        return upload
    
    def upload_content(self, source, name, content):
        self.upload(source, name, content).send_all_console()
    
    def download(self, sha1):
        return self._request('/sync.cgi?mode=download&sha1=%s' % sha1)
    
    def download_content(self, sha1):
        return self.download(sha1).read()
    
    def list(self):
        l = []
        for line in self._request('/sync.cgi?mode=list').read().splitlines():
            sha1, source, date, size, name = line.split(None, 4)
            l.append(ListEntry(sha1, source, int(date), int(size), name))
        return l
    
    def _login_or_register(self, url, payload):
        set_cookie = request(url, payload, return_cookie=True)
        if not set_cookie.startswith('fcsession='):
            raise ValueError('Invalid set-cookie (%r).' % set_cookie)
        set_cookie = set_cookie[len('fcsession='):]
        if ';' in set_cookie:
            set_cookie, _ = set_cookie.split(';', 1)
        set_cookie = set_cookie.strip()
        self._sessid = set_cookie
    
    def _request(self, url, payload=None):
        return request(url, payload, self.sessid)
    
def request(url, payload=None, sessid=None, return_cookie=False):
    conn = httplib.HTTPConnection(HOST)
    headers = {}
    if sessid:
        headers['cookie'] = 'fcsession=' + sessid
    conn.request('POST' if payload else 'GET', url, body=payload, headers=headers)
    response = conn.getresponse()
    headers = dict(response.getheaders())
    if 'x-login-error' in headers:
        raise LoginError(headers['x-login-error'])
    if 'x-request-error' in headers:
        raise RequestError(headers['x-request-error'])
    if response.status not in (200, 301, 302):
        print '=== Server returned error ==='
        print response.read()
        print '============================='
        raise RequestError('Invalid HTTP status code %d.' % response.status)
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
    def __init__(self, url, data, cookie):
        self.url = url
        self.content_type, self.data = encode_multipart_formdata(data)
        self.cookie = cookie
        self.i = 0
    
    def header(self):
        self.h = httplib.HTTPConnection(HOST)
        self.h.putrequest('POST', self.url)
        self.h.putheader('content-type', self.content_type)
        self.h.putheader('content-length', str(len(self.data)))
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
        if 'x-login-error' in headers:
            raise LoginError(headers['x-login-error'])
        if 'x-request-error' in headers:
            raise RequestError(headers['x-request-error'])
        if response.status not in (200, 301, 302):
            print '=== Server returned error ==='
            print response.read()
            print '============================='
            raise RequestError('Invalid HTTP status code %d.' % response.status)
    
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

    