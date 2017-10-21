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
            src_name = tpl[1]
            dst_name = tpl[2]
            edges.append((src_name, dst_name, points))
    return size, edges, nodes

DPI = 70
colors = [
    tuple(reversed((k & 0xFF, (k >> 8) & 0xFF, (k >> 16) & 0xFF)))
    for k in
    [0xFFB300, 0x803E75, 0xFF6800, 0xA6BDD7, 0xC10020, 0xCEA262, 0x817066]
]

class TechTreeWidget(ui.Widget):
    '''
    As tech tree is too big to fit in single texture
    redraw it each frame. (caching text renders)
    '''
    def __init__(self, model, size, edges, nodes):
        self._size = size
        self._edges = edges
        self._nodes = nodes
        self._renders_cache = {}
        self.model = model
        self.size = self._size[0] * DPI, self._size[1] * DPI

    def draw(self, surf, surf_pos):
        def s2r(pos):
            'Compute real position.'
            return surf_pos[0] + pos[0] * DPI, \
                surf_pos[1] + pos[1] * DPI

        def _draw_text(text, pos):
            txt = ui.consolefont.render(text)
            surf.blit(txt, pos)

        for src_name, dst_name, points in self._edges:
            bgcolor, color = self.tech_color(dst_name)
            for a, b in zip(points[::], points[1::]):
                surf.draw_line(color, s2r(a), s2r(b))

        for text, rect in self._nodes:
            rect = [rect[0] - rect[2] / 2, rect[1] - rect[3] / 2] + rect[2:]
            rrect = s2r(rect) + (rect[2] * DPI, rect[3] * DPI)
            bgcolor, color = self.tech_color(text)
            surf.draw_rect(bgcolor,
                           rrect,
                           width=0)
            _draw_text(text, rrect)
            surf.draw_rect(color,
                           rrect,
                           width=1)

    def tech_color(self, name):
        researched = self.model.is_researched(name)
        if researched:
            return (210, 255, 210), (65, 255, 65)
        elif self.model.is_available(name):
            return (235, 255, 255), (160, 255, 255)
        else:
            return (255, 255, 255), (0, 0, 0)

class TechtreeClientModel(object):
    def __init__(self, client):
        self.client = client
        self.state = {}
        techs = self.client.get_all_techs()
        # FIXME: tech tree is broken and needs to be re-developped from "scratch" (using reqtree.c)
        #for tech in techs:
        #    self.state[tech.name] = tech.get_research_state()

    def is_researched(self, name):
        return self.state.get(name) == 2

    def is_available(self, name):
        return self.state.get(name) != 0

def show(client):
    tree = load_techtree('data/techtree.index')

    model = TechtreeClientModel(client)
    widget = TechTreeWidget(model, *tree)
    widget = ui.ScrollWrapper(widget, ways=ui.SCROLL_WIDTH | ui.SCROLL_HEIGHT)
    ui.set(widget)

if __name__ == '__main__':
    tree = load_techtree('data/techtree.index')

    class ExampleModel:
        def is_researched(self, name):
            name = name.strip("'")
            return name in ['Alphabet', 'Masonry', 'Currency', 'Bronze Working', 'Mathematics']

        def is_available(self, name):
            return False


    model = ExampleModel()

    graphics.init()
    ui.init()
    wnd = graphics.create_window((800, 600))
    ui.screen_width, ui.screen_height = ui.screen_size = wnd.get_size()
    widget = TechTreeWidget(model, *tree)
    widget = ui.ScrollWrapper(widget, ways=ui.SCROLL_WIDTH | ui.SCROLL_HEIGHT)
    ui.replace(widget)
    ui.main()
