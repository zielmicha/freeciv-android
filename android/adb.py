#!/usr/bin/env python
import subprocess

inf = subprocess.Popen(['adb', 'logcat'], stdout=subprocess.PIPE)

watch_for = 0

for line in iter(inf.stdout.readline, b''):
    line = line.strip()
    pid = line.partition('(')[2].split(')')[0].strip()
    try:
        pid = int(pid)
    except ValueError:
        continue
    if line.startswith('I/freeciv ('):
        watch_for = pid
    if pid == watch_for:
        print line
