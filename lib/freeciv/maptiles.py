import ui
import graphics
import time
import contextlib
from ui import stream
from ui import ctrl

from client import freeciv

SELECT_POPUP = 0

class MapWidget(ui.Widget):
    def __init__(self, client):
        self.client = client
        self.size = (0, 0)
        self.drawer = TileDrawer(client)
        self.tile_size = 64
        self.tile_storage = {} # corresponds to client's one
        self.screen_pos = (0, 0)
        self.screen_tiles = 20

        ctrl.bind_event('tile', self.process_message)

    def back(self):
        self.client.escape()

    def event(self, ev):
        if ev.type in (graphics.const.KEYDOWN, graphics.const.KEYUP):
            self.client.key_event(ev.type, ev.key)

    def draw(self, surf, pos):
        surf.draw_rect((255, 255, 255, 0), pos + self.size, blend=graphics.MODE_NONE)
        stream.add_message({'type': 'tile', 'draw_at': pos + self.size})
        tile_pos = self.screen_pos[0] // self.tile_size, self.screen_pos[1] // self.tile_size
        for i in range_around(tile_pos[0], self.screen_tiles):
            for j in range_around(tile_pos[1], self.screen_tiles):
                self.update_tile(i * self.tile_size, j * self.tile_size)

    def update_tile(self, x, y):
        img = self.drawer.draw_fragment((x, y,
                                              self.tile_size,
                                              self.tile_size))

        new_data = stream.get_texture_data(img)
        if new_data != self.tile_storage.get((x, y)):
            self.tile_storage[x, y] = new_data

            stream.add_message({'type': 'tile', 'id': '%d,%d' % (x, y), 'data': new_data})

    def process_message(self, message):
        print 'tile message', message

def range_around(x, phi):
    return range(x - phi/2, x - phi/2 + phi)

class TileDrawer(object):
    def __init__(self, client):
        self.map_size = (100, 100)
        self.client = client

    def draw_fragment(self, rect):
        with self.save_state():
            self.set_map_size((rect[2], rect[3]))
            self.set_map_origin(rect[0], rect[1])
            surf = graphics.create_surface(rect[2], rect[3])
            self.client.draw_map(surf, (0, 0))
            return surf

    def set_map_size(self, size):
        self.map_size = size
        self.client.set_map_size(size)

    def set_map_origin(self, x, y):
        freeciv.func.base_set_mapview_origin(x, y)

    @contextlib.contextmanager
    def save_state(self):
        origin = freeciv.func.get_map_view_origin()
        size = self.map_size
        try:
            yield
        finally:
            self.map_size = size
            freeciv.func.base_set_mapview_origin(origin[0], origin[1])
