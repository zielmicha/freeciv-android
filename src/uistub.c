/**********************************************************************
 Freeciv - Copyright (C) 1996 - A Kjeldberg, L Gregersen, P Unold
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
***********************************************************************/

#ifdef HAVE_CONFIG_H
#include <fc_config.h>
#endif

#ifdef AUDIO_SDL
#include "SDL.h"
#endif

#include <stdio.h>

/* utility */
#include "fciconv.h"
#include "log.h"

/* client */
#include "client_main.h"
#include "editgui_g.h"
#include "ggz_g.h"
#include "options.h"


const char *client_string = "gui-sdl";

const char * const gui_character_encoding = "UTF-8";
const bool gui_use_transliteration = FALSE;


/**************************************************************************
  Entry point for whole freeciv client program.
**************************************************************************/
int uistub_main(int argc, char **argv)
{
  return client_main(argc, argv);
}

/****************************************************************************
  Extra initializers for client options.
****************************************************************************/
void gui_options_extra_init(void)
{
  /* Nothing to do. */
}

/**************************************************************************
  Return our GUI type
**************************************************************************/
enum gui_type get_gui_type(void)
{
  return GUI_SDL;
}


/****************************************************************************
  Stub for editor function
****************************************************************************/
void editgui_tileset_changed(void)
{}

/****************************************************************************
  Stub for editor function
****************************************************************************/
void editgui_refresh(void)
{}

/****************************************************************************
  Stub for editor function
****************************************************************************/
void editgui_popup_properties(const struct tile_list *tiles, int objtype)
{}

/****************************************************************************
  Stub for editor function
****************************************************************************/
void editgui_popdown_all(void)
{}

/****************************************************************************
  Stub for editor function
****************************************************************************/
void editgui_notify_object_changed(int objtype, int object_id, bool remove)
{}

/****************************************************************************
  Stub for editor function
****************************************************************************/
void editgui_notify_object_created(int tag, int id)
{}

/****************************************************************************
  Stub for ggz function
****************************************************************************/
void gui_ggz_embed_leave_table(void)
{}

/****************************************************************************
  Stub for ggz function
****************************************************************************/
void gui_ggz_embed_ensure_server(void)
{}

/****************************************************************************
  Frees the introductory sprites.
****************************************************************************/
void free_intro_radar_sprites(void)
{
}
