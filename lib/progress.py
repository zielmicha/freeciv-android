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

import pygame
import ui
import time

last_draw = 0
timeout = 0.3

def draw_frame(title, name, perc):
    global last_draw
    if time.time() < last_draw + timeout:
        return
    
    frame = pygame.display.get_surface()
    w, h = frame.get_size()
    ui.fill(frame, (0, 0))
    text = ui.mediumfont.render(name, 1, (0, 0, 0))
    titletext = ui.mediumfont.render(title, 1, (0, 0, 0))
    frame.blit(text, ((w - text.get_width())/2, h - 60))
    frame.blit(titletext, ((w - titletext.get_width())/2, h - 120))
    
    barheight = 20
    barwidth = w * 0.6
    barpos = (w * 0.2, 100)
    round = 8
    ui.round_rect(frame, (200, 255, 200, 200), (0,0,0,0), barpos + (barwidth, barheight), round)
    if perc > 0:
        ui.round_rect(frame, (0, 255, 0, 200), (0,0,0,0), barpos + (int(barwidth * perc), barheight), round)
    #pygame.draw.rect(frame, (200, 255, 200), barpos + (barwidth, barheight))
    #pygame.draw.rect(frame, (0, 255, 0), barpos + (int(barwidth * perc), barheight))
    
    pygame.display.flip()
    
    last_draw = time.time()
