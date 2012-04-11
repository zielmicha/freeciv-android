import save
import client

def start():
    def callback():
        client.client.chat('/novice')
        found_nations = [ (name, style, id) for name, style, id in client.get_nations() if name == 'Poles' ]
        if found_nations:
            name, style, id = found_nations[0]
            print 'change nation to', name, style, id
            client.freeciv.func.set_nation_settings(id, 'Player', style, 2)
        return True
    
    save.load_game('data/tutorial.sav', before_callback=callback)
