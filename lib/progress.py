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

def draw_frame(title, name, perc):
    frame = pygame.display.get_surface()
    w, h = frame.get_size()
    frame.fill((255, 255, 255))
    text = ui.mediumfont.render(name, 1, (0, 0, 0))
    titletext = ui.mediumfont.render(title, 1, (0, 0, 0))
    frame.blit(text, ((w - text.get_width())/2, h - 60))
    frame.blit(titletext, ((w - titletext.get_width())/2, h - 120))
    barheight = 20
    barpos = (0, h - barheight)
    pygame.draw.rect(frame, (200, 255, 200), barpos + (w, barheight))
    pygame.draw.rect(frame, (0, 255, 0), barpos + (int(w * perc), barheight))
    pygame.display.flip()
    