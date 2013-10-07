from tornado import web, websocket, ioloop, httpserver
import subprocess
import threading
import os

PORT = 8002

class WSHandler(websocket.WebSocketHandler):
    handlers = []

    def open(self):
        self.handlers.append(self)

    def on_message(self, message):
        pass

    def on_close(self):
        pass

    @classmethod
    def broadcast(self, data):
        for handler in self.handlers:
            if handler.ws_connection:
                handler.write_message(data)

def stream_data(fdin):
    f = os.fdopen(fdin, 'r', 1)

    print 'read stream'
    while True:
        line = f.readline()
        if not line: break
        ioloop.IOLoop.instance().add_callback(WSHandler.broadcast, line)
    print 'stream finished'

if __name__ == u"__main__":
    fdin, fdout = os.pipe()
    inferior = subprocess.Popen(['bash', './main.sh',
                                 'freeciv.main',
                                 '-f:stream.enable', '-f:stream.fd=%d' % fdout])
    os.close(fdout)
    threading.Thread(target=stream_data, args=[fdin]).start()

    application = web.Application([
        (r'/ws', WSHandler),
    ])

    http_server = httpserver.HTTPServer(application)
    http_server.listen(PORT)
    ioloop.IOLoop.instance().start()
