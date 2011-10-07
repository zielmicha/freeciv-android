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

import civsync
import client 

import os
import BaseHTTPServer
import random
import thread
import urllib
import traceback
import urllib
import socket
import sys
import httplib
import cgi
import platform
import webbrowser

civpath = client.civpath
pidfile = os.path.join(civpath, 'civsync.pid.txt')
port = random.randint(1500, 8000)

session = client.session

is_windows = platform.system().lower() == 'windows'

def request_login():
    print 'request_login'
    session._sessid = None
    show_main()

client.request_login = request_login

class Handler(BaseHTTPServer.BaseHTTPRequestHandler):
    def do_GET(self):        
        path = self.path
        
        if '?' in path:
            cmd, query = path.split('?')
        else:
            cmd = path
            query = ''
        if query:
            query = dict( v.split('=', 1) for v in query.split('&') )
            query = dict( (urllib.unquote(k), urllib.unquote(v)) for k, v in query.items() )
        else:
            query = {}
        
        #print query
            
        write = self.wfile.write
        
        cmd = cmd[1:]
        
        if cmd.startswith('f/'):
            self.send_response(200)
            self.end_headers()
            fn = cmd[len('f/'): ]
            write(open(fn, 'rb').read())
        
        elif cmd == 'login':
            try:
                session.login(query.get('login', ''), query.get('password', ''))
                print 'login done'
            except civsync.RequestError, e:
                self.send_response(302)
                self.send_header('location', '/form?error=' + e[0])
                self.end_headers()
                self.wfile.write('Error, <a href=/form?error=' + e[0] + '>go here</a>')
            except Exception, e:        
                self.send_response(302)
                e = urllib.quote(str(e))
                self.send_header('location', '/form?error=' + e)
                self.end_headers()
                self.wfile.write('Error, <a href=/form?error=' + e + '>go here</a>')
                
                traceback.print_exc()
            else:        
                self.send_response(302)
                self.send_header('Location', '/form?status=1')
                self.end_headers()
                self.wfile.write('Logged, <a href=/form?status=1>go here</a>')
        
        elif cmd == 'register':
            self.send_response(302)
            self.send_header('location', '/form?error=Not yet implemented.')
            self.end_headers()
        
        elif cmd == 'close':    
            self.send_response(200)
            try:
                windows[query['role']].write('close\r\n')
            except:
                self.send_header('content-type', 'text/plain')
                self.end_headers()
                write(traceback.format_exc())
            else:
                self.end_headers()
                write('ok')
        
        elif cmd == 'open_main':
            self.send_response(200)
            self.end_headers()
            show_main()
        
        elif cmd == 'state':
            self.send_response(200)
            self.end_headers()
            #if client.current_state == 'work':
            #    name, perc = client.current_entry
            #    write('%.1f%% %s<br>' % (perc * 100, cgi.escape(name) ))
            #    for spec in client.entries_to_work:
            #        write('%s %s<br>' % (spec[0], spec[1]))
            #else:
            #    write(client.current_state)
            #if client.current_state == 'civnotrun':
            #    # actually never displayed
            #    write('It looks like you have never run Freeciv.'
            #          '<br><button onclick="location.href=\'runciv\'">Run Freeciv!</button>')
            if client.civ_not_found:
                write('It looks like you have not installed Freeciv.'
                      '<br><button onclick="location.href=\'getciv\'">Download Freeciv!</button><br>')
            if False:
                pass
            else:
                state = client.current_state
                write('<style>.b { font-weight:bold;display:block;color:#D29B1F;margin-top:0.3em; }</style>')
                write('Status: %s<br>' % state)
                if state in ('uploading', 'downloading'):
                    write('File: %s<br>' % cgi.escape(client.current_entry))
                    write('<img src=/f/loading.gif><br>')
                
                if client.to_download:
                    write('<span class=b>Download queue</span>')
                    for entry in client.to_download:
                        write('%s<br>' % cgi.escape(client.trim_save_name(entry.name)))
                
                if client.to_upload:
                    write('<span class=b>Upload queue</span>')
                    for name in client.to_upload:
                        write('%s<br>' % cgi.escape(client.trim_save_name(name)))
                
                
        
        elif cmd == 'runciv':
            civclient = client.find_civ_client()
            self.send_response(302)
            if not civclient:
                self.send_header('Location', '/form?error=Freeciv-GTK binary not found.')
            else:
                self.send_header('Location', '/form')
            self.end_headers()
            if is_windows:
                os.system(civclient)
            else:
                os.system('%s &' % civclient)
        
        elif cmd == 'getciv':
            civclient = client.find_civ_client()
            self.send_response(302)
            self.end_headers()
            webbrowser.open_new_tab('http://freeciv.org/')
        
        elif cmd == 'form': 
            self.send_response(200)
            self.send_header('content-type', 'text/html')
            self.end_headers()
            write('<title>freeciv sync</title>')
            write('<meta charset=utf-8>\n<script src="/f/jquery.js"></script>')
            write('<body style="text-align: center; background: #987654">')
            write('''
            <script>
            if(navigator.userAgent.indexOf('ndroid') == -1)
                document.write('<img src="/f/bg.jpg" style="position:fixed;_position:absolute;width:100%;top:0;left:0;z-index:-3;opacity:0.5;filter(alpha=50);">')
            </script>
            ''')
            write('<div style="display:inline-block;">')
            write('<h1 style="font-family: Ubuntu; margin-bottom: 0em;">freeciv sync</h1>')
            write('<div style="margin-bottom: 0.7em;">Synchronize your Civilization saves!</div>')
            write('''<style> 
            a { color: blue } 
            </style>''')
            
            write('<br>' * 1)
            
            write('<div style="text-align: left; border: 1px solid gray; background: white;padding: 0.2em 0.7em; margin-top: 3em;">')
            
            if not session.is_logged():
                write('''
                <div style="font-weight: bolder; color: red;">%s</div>
                <form action=/login method=get id=login onsubmit="$('[type=submit]').attr('disabled', true).val('Loading...'); return true;">
                    You are not logged. <br>
                    <table>
                    <tr><td>Login: <td><input type=text name=login>
                    <tr><td>Password: <td><input type=password name=password>
                    </table>
                    <input type=submit value=Login>
                    <a href="javascript:void(0)" onclick="$(\'#register\').slideDown(); $(\'#login\').slideUp()">Register</a>
                </form>
                <form action=register method=get id=register style="display:none;" name=regf 
                    onsubmit="if(this.password.value != this.password2.value){alert(\'Passwords not matching!\');return false;}else{$('[type=submit]').attr('disabled', true).val('Loading...'); return true;}">
                    <table>
                    <tr><td>Login: <td><input type=text name=login> <br>
                    <tr><td>Password: <td><input type=password name=password> <br>
                    <tr><td>Password: <td><input type=password name=password2> <br>
                    <tr><td>Mail: <td><input type=text name=mail> <br>
                    </table>
                    <input type=submit value=Register>
                    <a href="javascript:void(0)" onclick="$(\'#login\').slideDown(); $(\'#register\').slideUp()">Back</a>
                </form>''' % query.get('error', ''))
            else:
                write('''
                <script>
                setInterval(function(){
                    $("#state").load("/state")
                }, 500)
                </script>
                <a href=/remotelogin>Uploaded saves</a>
                |
                <a href=/checknow>Check now</a>
                <div id=state>
                
                </div>
                ''')
        
        elif cmd == 'remotelogin':
            url = 'http://%s/remotelogin?sessid=%s&url=/' % (civsync.HOST, client.session.sessid)
            webbrowser.open_new_tab(url)
            self.send_response(302)
            self.send_header('Location', '/form')
            self.end_headers()
        
        elif cmd == 'checknow':
            client.request_check = True
            self.send_response(302)
            self.send_header('Location', '/form')
            self.end_headers()
        
        else:    
            self.send_response(404)
            print 'fail -', cmd
    
    def log_message(self, format, *args):
        return
        #s = format % args
        #if 'GET /state ' in s:
        #    return
        #print '[server]', s

windows = {}

def show(url, role=None):
    buffering = -1 if is_windows else 1
    windows[role] = os.popen('python clientui.py \'http://localhost:%d/%s\'' % (port, url), 'w', buffering)

def show_main():
    try:
        windows['main'].write('close\r\n')
    except (KeyError, IOError):
        pass
    show('form', role='main')

def run():
    if not os.path.exists(client.civpath):
        os.mkdir(client.civpath)
    try:
        f = open(pidfile, 'w')
        f.write(str(port) + '\r\n' + str(os.getpid()))
        f.close()
    except IOError:
        print 'failed to write PID to file'
    client.prepare()
    print 'serving at', port
    client.start()
    serv = BaseHTTPServer.HTTPServer(('localhost', port), Handler)
    serv.serve_forever()

def try_run(is_deamon):
    try:
        lines = open(pidfile).read().splitlines()
    except IOError:
        lines = None
    
    servpid = False
    
    try:
        if lines:
            servport, servpid = map(int, lines)
        else:
            servport, servpid = None, None
    except ValueError:
        servport, servpid = None, None
    
    if not is_deamon:
        try:
            print 'http://localhost:%s/open_main' % servport
            urllib.urlopen('http://localhost:%s/open_main' % servport).read()
        except (socket.error, httplib.InvalidURL, IOError):
            print 'starting deamon'
            show('form', role='main')
            run()
    else:
        if servpid:
            try:
                os.kill(servpid, 9)
                print 'deamon killed'
            except OSError:
                print 'couldn\'t kill deamon'
        run()

if __name__ == '__main__':
    is_deamon = False
    host = None
    
    for arg in sys.argv[1:]:
        if arg == '--deamon':
            is_deamon = True
        elif arg.startswith('--synchost='):
            host = arg[len('--synchost='):]
        else:
            print 'Unrecognized argument', arg
    
    if host:
        civsync.HOST = host
    
    try_run(is_deamon)
