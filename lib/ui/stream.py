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
    ui.layer_hooks.add(layer_hook)

def write_image(data, size):
    import Image
    mode = 'RGBA'
    image = Image.frombuffer(mode, size, data, 'raw', mode, 0, 1)
    image.load()

    output = StringIO.StringIO()
    image.save(output, format='png')
    content = output.getvalue()
    output.close()
    return content

def get_texture_data(texture):
    data = texture.read_data()
    return write_image(data, texture.get_size())

def run():
    ui.set_fill_image(None)
    start = time.time()
    data = graphics.read_window_data()
    compressed = write_image(data, graphics.get_window().get_size())
    stats = {'size': len(compressed),
             'time': int((time.time() - start) * 1000)}

    data = []
    data.append({
        'type': 'frame',
        'data': compressed.encode('base64'),
        'id': id(ui.get_screen()),
        'back': id(ui.history[0]) if ui.history else None,
        'allow_animation': ui.get_allow_animation(),
        'pos': [0, 0]})

    def proc_layer(id, surf, pos, offset, size):
        if surf.get_width() == 0 or surf.get_height() == 0:
            return
        image_data = get_texture_data(surf)
        data.append({
            'type': 'layer',
            'layerid': id,
            'data': image_data.encode('base64'),
            'pos': pos,
            'offset': offset,
            'size': size,
        })

    for layer in layers:
        proc_layer(**layer)

    os.write(features.get('stream.fd'), json.dumps(data) + '\n')

    layers[:] = []
    ui.draw_hooks.add(run)

layers = []

def layer_hook(**kwargs):
    layers.append(kwargs)
