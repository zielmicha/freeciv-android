# Copyright (C) 2011 Michal Zielinski (michal@zielinscy.org.pl)
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

import ui
import time

last_draw = 0
timeout = 0.3

def draw_frame(title, name, perc):
    global last_draw
    if time.time() < last_draw + timeout:
        return

    print '\r', '%.1f' % (perc * 100), name, title

    last_draw = time.time()
