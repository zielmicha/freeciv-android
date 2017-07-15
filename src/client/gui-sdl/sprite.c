/********************************************************************** 
 Freeciv - Copyright (C) 2005 The Freeciv Team
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

/* utility */
#include "shared.h"
#include "mem.h"

#include "SDL.h"
#include "SDL_image.h"

struct color {
  SDL_Color *color;
};

/* client/gui-sdl */


struct sprite {
  struct SDL_Surface *psurface;
};


static struct sprite * ctor_sprite(SDL_Surface *pSurface)
{
  struct sprite *result = fc_malloc(sizeof(struct sprite));

  result->psurface = pSurface;

  return result;
}

#define SDL_PublicSurface	(current_video->visible)

#define SDL_HWSURFACE	0x00000001	/**< Surface is in video memory */
#define SDL_SRCALPHA	0x00010000	/**< Blit uses source alpha blending */
#define SDL_RLEACCELOK	0x00002000	/**< Private flag */

/*
 * Convert a surface into a format that's suitable for blitting to
 * the screen, but including an alpha channel.
 */
SDL_Surface *SDL_DisplayFormatAlpha(SDL_Surface *surface)
{
	SDL_PixelFormat *vf;
	SDL_PixelFormat *format;
	SDL_Surface *converted;
	Uint32 flags;
	/* default to ARGB8888 */
	Uint32 amask = 0xff000000;
	Uint32 rmask = 0x00ff0000;
	Uint32 gmask = 0x0000ff00;
	Uint32 bmask = 0x000000ff;

/*	if ( ! SDL_PublicSurface ) {
		SDL_SetError("No video mode has been set");
		return(NULL);
	}
	vf = SDL_PublicSurface->format;

	switch(vf->BytesPerPixel) {
	    case 2:*/
		/* For XGY5[56]5, use, AXGY8888, where {X, Y} = {R, B}.
		   For anything else (like ARGB4444) it doesn't matter
		   since we have no special code for it anyway */
/*		if ( (vf->Rmask == 0x1f) &&
		     (vf->Bmask == 0xf800 || vf->Bmask == 0x7c00)) {
			rmask = 0xff;
			bmask = 0xff0000;
		}
		break;

	    case 3:
	    case 4:*/
		/* Keep the video format, as long as the high 8 bits are
		   unused or alpha */
		if ( (vf->Rmask == 0xff) && (vf->Bmask == 0xff0000) ) {
			rmask = 0xff;
			bmask = 0xff0000;
		} else if ( vf->Rmask == 0xFF00 && (vf->Bmask == 0xFF000000) ) {
			amask = 0x000000FF;
			rmask = 0x0000FF00;
			gmask = 0x00FF0000;
			bmask = 0xFF000000;
		}
/*		break;

	    default:*/
		/* We have no other optimised formats right now. When/if a new
		   optimised alpha format is written, add the converter here */
/*		break;
	}*/
	format = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
	flags = /*SDL_PublicSurface->flags & */SDL_HWSURFACE;
	flags |= surface->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
flags=0;
	converted = SDL_ConvertSurface(surface, format, flags);
	SDL_FreeFormat(format);
	return(converted);
}

/****************************************************************************
  Create a sprite with the given height, width and color.
****************************************************************************/
struct sprite *create_sprite(int width, int height, struct color *pcolor)
{
  SDL_Surface *mypixbuf = NULL;
  SDL_Surface *pmask = NULL;

  fc_assert_ret_val(width > 0, NULL);
  fc_assert_ret_val(height > 0, NULL);
  fc_assert_ret_val(pcolor != NULL, NULL);

  mypixbuf = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32,
                                  0x00ff0000, 0x0000ff00, 0x000000ff,
                                  0xff000000);
real_output_window_append("create_sprite: code desactive", 0,0);
  pmask = SDL_DisplayFormatAlpha(mypixbuf);
SDL_FillRect(mypixbuf, NULL, 0xff000000);
//  SDL_FillRect(mypixbuf, NULL, map_rgba(pmask->format, *pcolor->color));

  return ctor_sprite(mypixbuf);
}

