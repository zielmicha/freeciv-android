import ui
import graphics
import time
from client import freeciv

SELECT_POPUP = 0

class MapWidget(ui.Widget):
    def __init__(self, client):
        self.client = client

        self.drawer = MapDrawer(client)

        self.size = (0, 0)
        self.last_size = None
        self.start_drag = None
        self.last_drag_pos = None
        self.was_dragged = False

        def nothing(*args):
            return

        freeciv.register('global_update_tile')(nothing)
        freeciv.register('global_set_mapview_center')(nothing)
        freeciv.register('global_update_everything')(nothing)

    def tick(self):
        pass

    def back(self):
        self.client.escape()

    def event(self, ev):
        if ev.type == graphics.const.MOUSEMOTION:
            if self.start_drag:
                if not self.was_dragged:
                    x, y = ev.pos
                    ox, oy = self.start_drag
                    dist = ((x - ox)**2 + (y - oy)**2) ** 0.5
                    if dist > 30:
                        self.was_dragged = True
                        #print 'was_dragged', dist
                if self.was_dragged:
                    self.drag(ev.pos)
                    return

            self.client.mouse_motion(self.drawer.coord_ui_to_map(ev.pos))
            return ui.LOCK_MOUSE_EVENT

        elif ev.type == graphics.const.MOUSEBUTTONDOWN:
            x, y = ev.pos
            self.start_drag = ev.pos
            self.drawer.start_scrolling()
            return ui.LOCK_MOUSE_EVENT

        elif ev.type == graphics.const.MOUSEBUTTONUP:
            if self.was_dragged:
                self.drag(ev.pos)
                self.was_dragged = False
            else:
                x, y = self.drawer.coord_ui_to_map(ev.pos)
                print ev.pos, x, y
                freeciv.func.action_button_pressed(x, y, SELECT_POPUP)
                self.client.draw_patrol_lines = False
            self.drawer.end_scrolling()
            self.start_drag = None
            self.last_drag_pos = None

        elif ev.type in (graphics.const.KEYDOWN, graphics.const.KEYUP):
            self.client.key_event(ev.type, ev.key)

    def draw(self, surf, pos):
        if self.size != self.last_size:
            self.drawer.set_size(self.size)
            self.last_size = self.size
        self.drawer.draw(surf, pos)

    def drag(self, pos):
        if not self.last_drag_pos:
            self.last_drag_pos = self.start_drag
        delta = ui.layout._subpoints(self.last_drag_pos, pos)
        self.last_drag_pos = pos

        self.drawer.move_map(delta)

    def change_zoom(self, zoom):
        self.drawer.change_zoom(zoom)

class MapDrawer(object):
    def __init__(self, client):
        self.client = client

        self.valid_for_origin = None # if get_map_view_origin() returns something else, redraw map
        self.user_corner = (0.0, 0.0) # this point should be painted in top-left corner

        self.map_cache = graphics.create_surface(1, 1)
        self.last_map_size = None
        self.widget_size = (0, 0)
        self.scrolling = False
        self.zoom = 1
        self.canvas_next_update = 0

        self.MAP_CACHE_SIZE = 0.

    def start_scrolling(self):
        self.scrolling = True
        self.reload()

    def end_scrolling(self):
        self.scrolling = False
        self.update_origin()
        self.reload()

    def set_size(self, size):
        self.widget_size = size
        self.reload()

    def change_zoom(self, zoom):
        self.zoom = zoom
        self.reload()

    def draw(self, surf, clip_pos):
        pos = (0, 0)
        cliptex = graphics.create_surface(*self.widget_size)
        if not self.scrolling:
            target = (pos[0] - self.user_corner[0], pos[1] - self.user_corner[1])
            self.maybe_update_whole_canvas()
            if self.zoom == 1:
                self.client.draw_map(cliptex, target)
            else:
                self.client.draw_map(self.map_cache, (0, 0))
                rect = self.user_corner + (self.map_cache.get_width() - self.user_corner[0],
                                           self.map_cache.get_height() - self.user_corner[1])
                #cliptex.blit(scale_by(self.map_cache.suburface(rect), self.zoom), (pos[0], pos[1]))
                cliptex.blit(self.map_cache, src=rect,
                             dest=(pos[0], pos[1], rect[2] * self.zoom, rect[3] * self.zoom))
        else:
            if freeciv.func.get_map_view_origin() != self.valid_for_origin:
                self.reload()
            else:
                if self.does_exceed():
                    self.update_origin()
                    self.reload()
            if self.zoom == 1:
                cliptex.blit(self.map_cache, (pos[0] - self.user_corner[0], pos[1] - self.user_corner[1]))
            else:
                cliptex.blit(self.scaled_map_cache, (int(pos[0] - self.user_corner[0] * self.zoom),
                                                  int(pos[1] - self.user_corner[1] * self.zoom)))
        surf.blit(cliptex, clip_pos)

    def maybe_update_whole_canvas(self):
        # need to throttle update, to make animations smooth
        current_time = time.time()
        if current_time >= self.canvas_next_update:
            freeciv.func.update_map_canvas_whole()
            update_time = time.time() - current_time
            # Before redrawing again, wait 10 times the time it took to redraw
            self.canvas_next_update = time.time() + 10 * update_time

    def reload(self):
        self.prepare_map_cache()
        #self.map_cache._pg.fill((100, 0, 100))
        self.client.draw_map(self.map_cache, (0, 0))
        if self.zoom != 1:
            self.scaled_map_cache.blit(self.map_cache, dest=(0, 0,
                                                             self.map_cache.get_width() * self.zoom,
                                                             self.map_cache.get_height() * self.zoom))

    def does_exceed(self):
        corner = (self.user_corner[0] * self.zoom, self.user_corner[1] * self.zoom)
        if corner[0] < 0 or corner[1] < 0:
            return True
        if corner[0] > self.MAP_CACHE_SIZE * 2 * self.widget_size[0] \
        or corner[1] > self.MAP_CACHE_SIZE * 2 * self.widget_size[1]:
            return True
        return False

    def update_origin(self):
        w, h = self.widget_size
        zero_corner = (int(self.MAP_CACHE_SIZE * w), int(self.MAP_CACHE_SIZE * h))
        delta = self.user_corner[0] - zero_corner[0], self.user_corner[1] - zero_corner[1]
        ox, oy = freeciv.func.get_map_view_origin()
        freeciv.func.base_set_mapview_origin(ox + delta[0], oy + delta[1])

    def prepare_map_cache(self):
        w, h = self.widget_size
        size_mul = self.MAP_CACHE_SIZE * 2 + 1
        size = (size_mul * w / self.zoom, size_mul * h / self.zoom)
        if size[0] > 2048: size = (2048, size[1] * 2048 / size[0])
        if size[1] > 2048: size = (size[0] * 2048 / size[1], 2048)
        size = (int(size[0]), int(size[1]))
        if size != self.map_cache.get_size():
            self.client.set_map_size(size)
            self.map_cache = graphics.create_surface(size[0], size[1], alpha=False)
            if self.zoom != 1:
                self.scaled_map_cache = graphics.create_surface(int(size_mul * w), int(size_mul * h))
        self.user_corner = (int(self.MAP_CACHE_SIZE * w), int(self.MAP_CACHE_SIZE * h))
        self.valid_for_origin = freeciv.func.get_map_view_origin()

    def move_map(self, delta):
        dx, dy = delta
        tx, ty = self.user_corner
        self.user_corner = tx + dx, ty + dy

    def coord_ui_to_map(self, pos):
        return int(pos[0] / self.zoom + self.user_corner[0]), int(pos[1] / self.zoom + self.user_corner[1])
