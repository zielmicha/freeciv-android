import ui
import io
import threading

import jnius
import reflect as jnius_reflect

from urllib import urlencode, quote, unquote

class URLopener:
    version = 'JavaHTTPS/0.0'

URLHelper = None

_local = threading.local()

def _init():
    _local.main = True
    global URLHelper
    if not URLHelper:
        URLHelper = jnius_reflect.autoclass('com.zielm.freeciv.URLHelper')

def urlopen(url):
    if getattr(_local, 'main', False):
        raise RuntimeError('HTTP request on main thread')
    return Request(url).execute()

class Request:
    def __init__(self, url):
        self.url = url
        self.helper = None
        self.cond = threading.Condition()
        self.result = None
        self.error = None

    def execute(self):
        with self.cond:
            self.begin()
            self.cond.wait()

        if self.error:
            raise IOError(self.error)
        else:
            return io.BytesIO(self.result)

    @ui.execute_later_decorator
    def begin(self):
        _init()
        print 'Starting URLHelper', self.url
        self.helper = URLHelper(self.url, URLopener.version)
        self.check()

    @ui.execute_later_decorator
    def check(self):
        if self.helper.isFinished():
            print 'URLHelper finished'
            self.result = self.helper.getResult()
            self.error = self.helper.getError()
            with self.cond:
                self.cond.notify_all()
        else:
            self.check()
