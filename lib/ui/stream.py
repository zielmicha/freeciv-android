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

last_send = 0
min_send_pause = 0.4

def init():
    print 'stream enabled (FD=%d)' % features.get('stream.fd')
    run()

def write_image(data):
    import Image
    mode = 'RGBA'
    image = Image.frombuffer(mode, graphics.get_window().get_size(), data, 'raw', mode, 0, 1)

    output = StringIO.StringIO()
    image.save(output, format='png')
    content = output.getvalue()
    output.close()
    return content

@ui.execute_later_decorator
def run():
    global last_send

    if time.time() - last_send < min_send_pause:
        run()
        return

    last_send = time.time()

    ui.set_fill_image(None)
    start = time.time()
    data = graphics.read_window_data()
    compressed = write_image(data)
    stats = {'size': len(compressed),
             'time': int((time.time() - start) * 1000)}

    frame = {
        'type': 'frame',
        'data': compressed.encode('base64'),
        'stats': stats}
    os.write(features.get('stream.fd'), json.dumps(frame) + '\n')
    run()
