import ui
import uidialog
import features
import functools

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
    ui.set(options)

def change_ruleset():
    def set_ruleset(name):
        features.set_perm('app.ruleset', name)
        ui.back()
    
    rulesets = ['default', 'civ1', 'civ2']
    panel = ui.LinearLayoutWidget()
    
    for ruleset in rulesets:
        panel.add(ui.Button(ruleset, functools.partial(set_ruleset, ruleset)))
    
    ui.set_dialog(panel)

