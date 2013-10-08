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
        self.ctrl_file.write(message + '\n')

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
    streamin, streamout = os.pipe()
    ctrlin, ctrlout = os.pipe()
    inferior = subprocess.Popen(['bash', './main.sh',
                                 'freeciv.main',
                                 '-f:stream.enable', '-f:stream.fd=%d' % streamout,
                                 '-f:ctrl.enable', '-f:ctrl.fd=%d' % ctrlin,
                                 '-f:ui.enable_anim=false', '-f:app.debug=false'])
    os.close(streamout)
    os.close(ctrlin)
    WSHandler.ctrl_file = os.fdopen(ctrlout, 'w', 0)
    threading.Thread(target=stream_data, args=[streamin]).start()

    application = web.Application([
        (r'/ws', WSHandler),
    ])

    http_server = httpserver.HTTPServer(application)
    http_server.listen(PORT)
    ioloop.IOLoop.instance().start()
