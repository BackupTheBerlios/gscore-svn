/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorebase/display.c
 * gscore - a musical score editor
 *
 * (C) Copyright 2001-2006 Sebastien Tricaud
 * e-mail : toady@gscore.org
 * URL    : http://www.gscore.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <libgscore/gscoretypes.h>
#include <libgscorebase/display.h>


extern Display *gscore_display_new(void);


extern Display *
gscore_display_new(void)
{

        Display *display;

        display = g_malloc(sizeof(Display));

        if ( ! display ) {
		g_print("Memory exhausted: cannot allocate new display\n");
		return NULL;
	}

        display->measure_number = TRUE;
        display->instruments = FALSE;
        display->clefs = TRUE;
        display->score_expressions = TRUE;
        display->barlines = TRUE;
        display->ending_bar = TRUE;
        display->key_signature = TRUE;
        display->time_signature = TRUE;
        display->tempo = TRUE;

        return display;

}
