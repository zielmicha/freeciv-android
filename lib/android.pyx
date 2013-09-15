from graphics import SDLError, map_key, const
import graphics
import sys
import os
import time

cdef extern from "SDL.h":
    cdef char* SDL_AndroidGetExternalStoragePath()
    cdef char* SDL_AndroidGetInternalStoragePath()

def get_external_storage():
    cdef char* path = SDL_AndroidGetExternalStoragePath()
    if path == NULL:
        raise SDLError()
    return path

def get_internal_storage():
    cdef char* path = SDL_AndroidGetInternalStoragePath()
    if path == NULL:
        raise SDLError()
    return path

cdef extern from "android/log.h":
    cdef int __android_log_write(int prio, char *tag, char *text)
    ctypedef enum:
        ANDROID_LOG_UNKNOWN
        ANDROID_LOG_DEFAULT
        ANDROID_LOG_VERBOSE
        ANDROID_LOG_DEBUG
        ANDROID_LOG_INFO
        ANDROID_LOG_WARN
        ANDROID_LOG_ERROR
        ANDROID_LOG_FATAL
        ANDROID_LOG_SILENT

cdef extern:
    cdef void unpack_res()

def err(line):
    __android_log_write(ANDROID_LOG_ERROR, "freeciv", line)

def info(line):
    __android_log_write(ANDROID_LOG_INFO, "freeciv", line)

def main():
    _keep_from_gc.extend([sys.stdout, sys.stderr])
    sys.argv = ['android']
    sys.stderr = LineStream(err)
    sys.stdout = LineStream(info)
    init_encoding()
    init_screen()
    started = time.time()
    unpack_res()
    print 'unpack_res took', time.time() - started
    display_splash('data/user/presplash.png', (255, 255, 255))
    os.chdir(get_internal_storage() + '/package')
    from freeciv import main
    main.main()

def init_screen():
    graphics.init()
    wnd = graphics.create_window(graphics.get_screen_size())
    wnd.fill((0, 128, 0))
    graphics.flip()
    display_splash('data/user/portedby.png', (0, 0, 0))

def display_splash(name, background):
    wnd = graphics.get_window()
    splash = graphics.load_image(name)
    splash_size = (splash.get_width() * wnd.get_height() / splash.get_height(), wnd.get_height())
    wnd.fill(background)
    wnd.blit(splash,
             dest=((wnd.get_width() - splash_size[0]) / 2, 0) + splash_size)
    graphics.flip()

def init_encoding():
    import encodings.ascii
    import encodings.utf_8

_keep_from_gc = []

KEYCODE_BACK = const.K_AC_BACK
KEYCODE_MENU = None

class LineStream:
    def __init__(self, callback):
        self.callback = callback
        self.buff = ''

    def write(self, text):
        self.buff += text
        while '\n' in self.buff:
            line, self.buff = self.buff.split('\n', 1)
            self.callback(line)

    def flush(self):
        self.write('\n')
