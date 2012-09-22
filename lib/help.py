import ui
import functools
import pygame

def show():
    global help_topics, help_data
    help_topics, help_data = load_help()
    
    ui.set(HelpPanel())

class HelpPanel(ui.HorizontalLayoutWidget):
    def __init__(self):
        def format_name(name):
            space_count = len(name) - len(name.lstrip(' '))
            return ('   ' * space_count) + name
        
        super(HelpPanel, self).__init__()
        topics_width = 150
        list = ui.LinearLayoutWidget()
        self.labels = {}
        for name in help_topics:
            label = ui.Label(format_name(name), functools.partial(self.open_topic, name), font=ui.consolefont)
            self.labels[name] = label
            list.add(label)
        self.add(ui.ScrollWrapper(list, width=topics_width))
        self.text = LongTextWidget('', ui.screen_width - topics_width, ui.consolefont)
        self.text_scroll = ui.ScrollWrapper(self.text)
        self.add(self.text_scroll)
        self.last_open = None
    
    def open_topic(self, name):
        if self.last_open:
            self.labels[self.last_open].color = (0, 0, 0)
            self.labels[self.last_open].redraw()
        self.last_open = name
        self.labels[name].color = (255, 0, 0)
        self.labels[name].redraw()
        self.text_scroll.y = 0
        self.text.set_text(help_data[name])

def load_help():
    d = list(_load_help())
    return [ k for k, v in d ], dict(d)

def _load_help():
    acum = []
    title = None
    lines = open('data/android-help.txt').read().splitlines()
    for line in lines:
        if line.startswith('=== '):
            if acum: yield title, '\n'.join(acum)
            acum = []
            title = line[4:]
        else:
            acum.append(line)
    if acum: yield title, '\n'.join(acum)

class LongTextWidget(ui.LinearLayoutWidget):
    def __init__(self, text, width, font):
        super(LongTextWidget, self).__init__()
        self.width = width
        self.font = font
        self.color = (0, 0, 0)
        self.set_text(text)
    
    def set_text(self, text):
        self.items[:] = []
        lines = text.split('\n')
        line_imgs = map(self.draw_text, lines)
        
        for img in line_imgs:
            self.add(ui.Image(img))
        
        self.update_layout()
    
    def draw_text(self, text):
        spacing = self.font.render('l', 1, (0,0,0)).get_width()
        width = self.width
        words = []
        lines = [words]
        current_width = 0
        for word in text.split():
            img = self.font.render(word, 1, self.color)
            if current_width != 0 and img.get_width() + current_width > self.width:
                words = []
                lines.append(words)
                current_width = 0
            words.append(img)
            current_width += img.get_width() + spacing
        
        height = sum( max([ word.get_height() for word in line ] + [0]) for line in lines )
        
        surf = pygame.Surface((width, height), pygame.SRCALPHA)
        
        y = 0
        for line in lines:
            if not line: continue
            x = 0
            for word in line:
                surf.blit(word, (x, y))
                x += word.get_width() + spacing
            y += max( word.get_height() for word in line )
        
        return surf

if __name__ == '__main__':
    import os; os.chdir('..')
    pygame.display.set_mode((800, 480))
    ui.init()
    w = LongTextWidget(open('data/android-help.txt').read(), 800, ui.consolefont)
    ui.set(w)
    ui.main()