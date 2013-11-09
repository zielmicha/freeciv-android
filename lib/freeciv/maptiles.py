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
        self.tile_size = 512
        self.tile_storage = {}
        self.tile_client_cache = {} # corresponds to client's one
        self.tile_map_pos = {}
        self.tile_draw_time = {}
        self.screen_pos = (0, 0)
        self.screen_tiles = (2500 // self.tile_size + 1, 1800 // self.tile_size + 1)
        self.redraw_queue = set()

        ctrl.bind_event('tile_posnotify', self.pos_notify)
        ctrl.bind_event('tile_init', self.client_init)
        ctrl.bind_event('tile_getconfig', self.send_config)
        freeciv.register(self.global_update_tile)
        freeciv.register(self.global_set_mapview_center)
        freeciv.register(self.global_update_everything)

    def send_config(self, m):
        stream.add_message({'type': 'tile_config',
                            'tile_size': self.tile_size})

    def back(self):
        self.client.escape()

    def event(self, ev):
        if ev.type in (graphics.const.KEYDOWN, graphics.const.KEYUP):
            self.client.key_event(ev.type, ev.key)
        elif ev.type == graphics.const.MOUSEBUTTONDOWN:
            try:
                pos = ev.data['tile_pos']
            except (AttributeError, KeyError):
                pass
            else:
                self.click(pos)

    def click(self, pos):
        x, y = pos
        self.drawer.click(x, y)

    def draw(self, surf, pos):
        surf.draw_rect((255, 255, 255, 0), pos + self.size, blend=graphics.MODE_NONE)
        stream.add_message({'type': 'tile', 'draw_at': pos + self.size})

        self.tick()

        ui.layer_hooks.execute(id='map',
                               surf=None,
                               pos=pos,
                               offset=(0, 0),
                               size=self.size)


    def tick(self):
        need_redraw = self.redraw_queue & set(self.get_screen_tiles())
        can_redraw = 5

        if self.redraw_queue:
            print 'queue', len(self.redraw_queue), 'need', len(need_redraw)
        for tile in list(need_redraw)[:can_redraw]:
            self.update_tile(*tile)

        can_redraw -= len(need_redraw)
        for tile in list(self.redraw_queue)[:can_redraw]:
            self.update_tile(*tile)

        for i, j in self.get_screen_tiles():
            self.push_tile(i, j)

    def get_screen_tiles(self):
        tile_pos = self.screen_pos[0] // self.tile_size, \
                   self.screen_pos[1] // self.tile_size
        return [ (i  * self.tile_size, j * self.tile_size)
                 for i in range_around(tile_pos[0], self.screen_tiles[0])
                 for j in range_around(tile_pos[1], self.screen_tiles[1]) ]

    def global_update_tile(self, x, y):
        # find nearest tiles
        by_dist = sorted(self.tile_map_pos.items(),
                         key=lambda (k, v): abs(v[0] - x) + abs(v[1] - y) if v else 100000)
        by_dist = by_dist[:5]
        print 'update', by_dist
        # and queue update
        for k, v in by_dist:
            self.redraw_queue.add(k)

    def global_update_everything(self):
        print 'update everything'
        self.redraw_queue |= set(self.tile_storage.keys())

    def global_set_mapview_center(self, x, y):
        stream.add_message({'type': 'tiles_center_at', 'pos': (x, y)})

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
        start = time.time()
        img, tile_pos = self.drawer.draw_fragment((x, y,
                                                   self.tile_size,
                                                   self.tile_size))
        print 'updated %s in %d ms' % ((x, y), (time.time() - start) * 1000)
        new_data = stream.get_texture_data(img)
        self.tile_storage[x, y] = new_data
        self.tile_map_pos[x, y] = tile_pos
        self.tile_draw_time[x, y] = time.time()
        self.redraw_queue -= {(x, y)}

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

    def click(self, x, y):
        with self.save_state():
            self.set_map_origin(x, y)
            freeciv.func.action_button_pressed(0, 0, SELECT_POPUP)

    @contextlib.contextmanager
    def save_state(self):
        origin = freeciv.func.get_map_view_origin()
        size = self.map_size
        try:
            yield
        finally:
            self.map_size = size
            freeciv.func.base_set_mapview_origin(origin[0], origin[1])
