import ui
import uidialog
import features
import functools
import traceback

class OptionsButton(ui.Button):
    def __init__(self, label, key):
        self.feature_label = label
        self.feature_key = key
        
        ui.Button.__init__(self, '', self._callback)
        
        self.make_button()
    
    def make_button(self):
        text = self.feature_label % features.get(self.feature_key)
        self.set_text(text)
    
    def _callback(self):
        val = uidialog.inputbox('Value for %s' % self.feature_key)
        try:
            features.set_perm(self.feature_key, val)
        except ValueError as e:
            ui.message(str(e), type='error')
        self.make_button()

class OptionsPanel(ui.LinearLayoutWidget):
    def add_feature(self, label, key):
        self.add(OptionsButton(label, key))

def show_options():
    options = OptionsPanel()
    options.add(ui.Label('Touch an option to change'))
    options.add_feature('Shutdown game after %d seconds of pause', 'app.shutdown')
    options.add(ui.Button('Change ruleset for new games', change_ruleset))
    if features.get('app.debug'):
        options.add(ui.Button('Debug', debug_menu))
    ui.set(options)

def debug_menu():
    def fake_screen_size(size):
        import main
        main.main(size, init=False)
    
    def fake_screen_size_menu():
        menu = ui.Menu(center=False)
        for size in [(320, 240), (480, 320), (640, 480)]:
            menu.add(str(size), functools.partial(fake_screen_size, size))
        ui.set_dialog(menu, scroll=True)
    
    def change_feature():
        arg = uidialog.inputbox('name=key')
        try:
            features._parse_arg(arg)
        except Exception as e:
            traceback.print_exc()
            ui.message(str(e))
    
    def pernament_feature():
        arg = uidialog.inputbox('name=key')
        try:
            k, v = arg.split('=', 1)
            features.set_perm(k, v)
        except Exception as e:
            traceback.print_exc()
            ui.message(str(e))
    
    def show_features():
        s = '\n'.join( '%s=%s' % (k,v) for k, v in sorted(features.features.items()) )
        ui.set_dialog(ui.Label(s), scroll=True)
    
    menu = ui.Menu()
    
    menu.add('Fake screen size', fake_screen_size_menu)
    menu.add('Get screen size', lambda: ui.set_dialog(ui.Label(str(ui.screen_size))))
    menu.add('Change feature', change_feature)
    menu.add('Pernament feature', pernament_feature)
    menu.add('Show features', show_features)
    
    ui.set(ui.ScrollWrapper(menu))


def change_ruleset():
    def set_ruleset(name):
        features.set_perm('app.ruleset', name)
        ui.back()
    
    rulesets = ['default', 'civ1', 'civ2']
    panel = ui.LinearLayoutWidget()
    
    for ruleset in rulesets:
        panel.add(ui.Button(ruleset, functools.partial(set_ruleset, ruleset)))
    
    ui.set_dialog(panel)

