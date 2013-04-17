import graphics
import ui
import osutil

def split(text):
    '''
    split text on spaces, don't split inside " quotes
    and strip quotes
    '''
    fragments = []
    n_quotes = 0
    for fragment in text.split(' '):
        if n_quotes % 2:
            fragments[-1] += ' ' + fragment
        else:
            fragments.append(fragment)
        n_quotes += fragment.count('"')
    return [ frag.strip('"') for frag in fragments if frag ]

def load_techtree(fn):
    edges = []
    nodes = []
    size = None
    for line in osutil.open_res(fn):
        tpl = split(line.strip())
        if tpl[0] == 'graph':
            size = map(float, tpl[2:4])
        elif tpl[0] == 'node':
            name = tpl[1]
            rect = map(float, tpl[2:6])
            nodes.append((name, rect))
        elif tpl[0] == 'edge':
            coord = map(float, tpl[4:-2])
            assert len(coord) % 2 == 0
            points = zip(coord[::2], coord[1::2])
            edges.append(points)
    return size, edges, nodes

DPI = 55
colors = [
    (0, 0, 0),
    (128, 0, 0),
    (0, 128, 0),
    (0, 0, 128),
]

class TechTreeWidget(ui.Widget):
    '''
    As tech tree is too big to fit in single texture
    redraw it each frame. (caching text renders)
    '''
    def __init__(self, size, edges, nodes):
        self._size = size
        self._edges = edges
        self._nodes = nodes
        self._renders_cache = {}
        self.size = self._size[0] * DPI, self._size[1] * DPI

    def draw(self, surf, surf_pos):
        def s2r(pos):
            'Compute real position.'
            return surf_pos[0] + pos[0] * DPI, \
                surf_pos[1] + pos[1] * DPI

        def _draw_text(text, pos):
            txt = ui.consolefont.render(text)
            surf.blit(txt, pos)

        for text, rect in self._nodes:
            rect = [rect[0] - rect[2] / 2, rect[1] - rect[3] / 2] + rect[2:]
            rrect = s2r(rect) + (rect[2] * DPI, rect[3] * DPI)
            _draw_text(text, rrect)
            color = colors[hash(text) % len(colors)]
            surf.draw_rect(color,
                           rrect,
                           width=1)

        for points in self._edges:
            color = colors[hash(tuple(points)) % len(colors)]
            for a, b in zip(points[::], points[1::]):
                surf.draw_line(color, s2r(a), s2r(b))

if __name__ == '__main__':
    tree = load_techtree('data/techtree.index')

    graphics.init()
    ui.init()
    wnd = graphics.create_window((800, 600))
    ui.screen_width, ui.screen_height = ui.screen_size = wnd.get_size()
    widget = TechTreeWidget(*tree)
    widget = ui.ScrollWrapper(widget, ways=ui.SCROLL_WIDTH | ui.SCROLL_HEIGHT)
    ui.replace(widget)
    ui.main()
