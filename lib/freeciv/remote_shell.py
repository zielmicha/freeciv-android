import SocketServer
import select
import time
import features
import os
import osutil
import subprocess
import threading

class ThreadingServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
    allow_reuse_address = True
    
class Handler(SocketServer.StreamRequestHandler):
    def handle(self):
        print 'incoming remote connection from', self.client_address
        f = self.request.makefile('r+')
        self.check_password(f)
        self.run_shell(f)
        self.request.close()
    
    def check_password(self, f):
        passphase = features.get('debug.remote.passphase')
        if not passphase:
            f.write('Passphase not required.\n')
            return True
        while True:
            f.write('Password: ')
            f.flush()
            pswd = f.readline().strip()
            if pswd != passphase:
                f.write('Invalid password.\n')
                f.flush()
                time.sleep(1)
            else:
                return True
    
    def run_shell(self, f):
        f.write('There is no pty - remember to use -i option when running some programs.\n')
        f.flush()
        os.environ['DATA_PATH'] = '/data/data/pl.org.zielinscy.freeciv.debug/'
        if osutil.is_desktop:
            cmd = ('sh',)
        else:
            busybox_path = '/data/local/tmp/busybox'
            if os.path.exists(busybox_path):
                cmd = (busybox_path, 'sh')
                os.environ['PATH'] += ':/data/local/tmp'
            else:
                cmd = ('/system/bin/sh',)
        subprocess.call(cmd + ('-i',), stdin=f.fileno(), stdout=f.fileno(), stderr=f.fileno())

def start():
    os.environ['PS1'] = '$ '
    threading.Thread(target=run).start()

def run():
    print 'starting remote'
    server = ThreadingServer(('127.0.0.1', features.get('debug.remote.port')), Handler)
    server.serve_forever()

def patch_pickle():
    # patch pickle module so it works on Android
    import pickle
    
    def string_unescape(rep):
        i = 0
        c = []
        while i < len(rep):
            ch = rep[i]
            if ch == '\\':
                nch = rep[i+1]
                if nch == '\'':
                    c.append('\'')
                elif nch == '"':
                    c.append('"')
                elif nch == 'n':
                    c.append('\n')
                elif nch == 'r':
                    c.append('\r')
                elif nch == 't':
                    c.append('\t')
                else:
                    if nch != 'x':
                        raise ValueError(rep[i+1])
                    c.append(chr(int(rep[i+2] + rep[i+3], 16)))
                i += 1
            else:
                c.append(ch)
                i += 1
        return ''.join(c)
    
    def load_string(self):
        rep = self.readline()[:-1]
        for q in "\"'": # double or single quote
            if rep.startswith(q):
                if not rep.endswith(q):
                    raise ValueError, "insecure string pickle"
                rep = rep[len(q):-len(q)]
                break
        else:
            raise ValueError, "insecure string pickle"
        self.append(string_unescape(rep))

    # types.UnboundMethodType(lambda self:self, None, T)

    pickle.Unpickler.dispatch[pickle.STRING] = load_string

patch_pickle()