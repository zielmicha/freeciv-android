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
        self.tile_size = 128
        self.tile_storage = {}
        self.tile_client_cache = {} # corresponds to client's one
        self.tile_map_pos = {}
        self.tile_draw_time = {}
        self.screen_pos = (0, 0)
        self.screen_tiles = (20, 15)

        ctrl.bind_event('tile_posnotify', self.pos_notify)
        ctrl.bind_event('tile_init', self.client_init)
        freeciv.register(self.global_update_tile)
        freeciv.register(self.global_set_mapview_center)

    def back(self):
        self.client.escape()

    def event(self, ev):
        if ev.type in (graphics.const.KEYDOWN, graphics.const.KEYUP):
            self.client.key_event(ev.type, ev.key)

    def draw(self, surf, pos):
        surf.draw_rect((255, 255, 255, 0), pos + self.size, blend=graphics.MODE_NONE)
        stream.add_message({'type': 'tile', 'draw_at': pos + self.size})

        for i, j in self.get_screen_tiles():
            self.push_tile(i * self.tile_size, j * self.tile_size)

        self.redraw_some_old()

        ui.layer_hooks.execute(id='map',
                               surf=None,
                               pos=pos,
                               offset=(0, 0),
                               size=self.size)

    def get_screen_tiles(self):
        tile_pos = self.screen_pos[0] // self.tile_size, \
                   self.screen_pos[1] // self.tile_size
        return [ (i, j)
                 for i in range_around(tile_pos[0], self.screen_tiles[0])
                 for j in range_around(tile_pos[1], self.screen_tiles[1]) ]

    def global_update_tile(self, x, y):
        # find 4 nearest tiles
        by_dist = sorted(self.tile_map_pos.items(),
                         key=lambda (k, v): abs(v[0] - x) + abs(v[1] - y) if v else 100000)
        by_dist = by_dist[:4]
        print 'update', by_dist
        # and queue update
        for k, v in by_dist:
            if k in self.tile_storage:
                del self.tile_storage[k]

    def global_set_mapview_center(self, x, y):
        stream.add_message({'type': 'tiles_center_at', 'pos': (x, y)})

    def redraw_some_old(self):
        timeout = 10
        count = 4
        for key, t in self.tile_draw_time.items():
            if not count:
                break
            if time.time() > t + timeout:
                count -= 1
                self.update_tile(*key)

    def push_tile(self, x, y):
        self.init_tile(x, y)
        new_data = self.tile_storage[x, y]
        if new_data != self.tile_client_cache.get((x, y)):
            self.tile_client_cache[x, y] = new_data
            stream.add_message({'type': 'tile', 'id': '%d,%d' % (x, y), 'data': new_data})

    def init_tile(self, x, y):
        if (x, y) not in self.tile_storage:
            self.update_tile(x, y)

    def update_tile(self, x, y):
        img, tile_pos = self.drawer.draw_fragment((x, y,
                                                   self.tile_size,
                                                   self.tile_size))

        new_data = stream.get_texture_data(img)
        self.tile_storage[x, y] = new_data
        self.tile_map_pos[x, y] = tile_pos
        self.tile_draw_time[x, y] = time.time()

    def client_init(self, message):
        self.tile_client_cache = {}

    def pos_notify(self, message):
        x, y = message['pos']
        self.screen_pos = -x, -y

def range_around(x, phi):
    return range(x - phi/2, x - phi/2 + phi)

def nround(a, r):
    return int(a // r) * r

class TileDrawer(object):
    def __init__(self, client):
        self.map_size = (100, 100)
        self.client = client

    def draw_fragment(self, rect):
        with self.save_state():
            self.set_map_size((rect[2], rect[3]))
            self.set_map_origin(rect[0], rect[1])
            surf = graphics.create_surface(rect[2], rect[3])
            surf.fill((255, 0, 255, 255), blend=graphics.MODE_NONE)
            self.client.draw_map(surf, (0, 0))
            tile_pos = freeciv.func.py_canvas_to_map(rect[2] / 2, rect[3] / 2)
            return surf, tile_pos

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
