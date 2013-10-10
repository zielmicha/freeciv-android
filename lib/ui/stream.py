import ui
import features
import graphics
import time
import zlib
import os
import json
import time
import StringIO

features.add_feature('stream.fd', type=int, default=2)

def init():
    print 'stream enabled (FD=%d)' % features.get('stream.fd')
    ui.draw_hooks.add(run)

def write_image(data):
    import Image
    mode = 'RGBA'
    image = Image.frombuffer(mode, graphics.get_window().get_size(), data, 'raw', mode, 0, 1)

    output = StringIO.StringIO()
    image.save(output, format='png')
    content = output.getvalue()
    output.close()
    return content

def run():
    ui.set_fill_image(None)
    start = time.time()
    data = graphics.read_window_data()
    compressed = write_image(data)
    stats = {'size': len(compressed),
             'time': int((time.time() - start) * 1000)}

    data = []
    data.append({
        'type': 'frame',
        'data': compressed.encode('base64'),
        'id': id(ui.get_screen()),
        'back': id(ui.history[0]) if ui.history else None,
        'allow_animation': ui.get_allow_animation()})

    for frame in data:
        os.write(features.get('stream.fd'), json.dumps(frame) + '\n')
    ui.draw_hooks.add(run)
