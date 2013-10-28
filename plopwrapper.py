import plop.collector
collector = plop.collector.Collector()
collector.start(duration=3600)

import os
import sys
os.environ["LD_LIBRARY_PATH"] = "/usr/local/lib:/usr/local/sdllib"
sys.path += ['lib', 'src']

import atexit

def stop():
    collector.stop()
    collector.filter(50)
    with open('/tmp/plop.out', 'w') as f:
        f.write(repr(dict(collector.stack_counts)))

atexit.register(stop)

import freeciv.main
freeciv.main.main()
