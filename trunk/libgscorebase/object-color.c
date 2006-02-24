/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorebase/object_color.c
 * gscore - a musical notation software
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


#include <glib.h>

#include <libgscore/gscoretypes.h>
#include <libgscorebase/object-color.h>


extern ObjectColor * gscore_object_color_new(void);
/* extern gint            gscore_object_color_set(SelectionArea *selectionarea, gboolean active); */

extern ObjectColor *
gscore_object_color_new(void)
{

        ObjectColor *objectcolor;

        objectcolor = g_malloc(sizeof(objectcolor));
        if ( ! objectcolor ) {
                g_print("Memory exhausted!\n");
                return NULL;
        }

        objectcolor->staves = g_malloc(sizeof(objectcolor->staves));
        if ( ! objectcolor->staves ) {
                g_print("Memory exhausted!\n");
                return NULL;
        }

        objectcolor->clefs = g_malloc(sizeof(objectcolor->clefs));
        if ( ! objectcolor->clefs ) {
                g_print("Memory exhausted!\n");
                return NULL;
        }

        objectcolor->objects = g_malloc(sizeof(objectcolor->objects));
        if ( ! objectcolor->objects ) {
                g_print("Memory exhausted!\n");
                return NULL;
        }

        /* By default, everything is black */
        objectcolor->staves->red = 0;
        objectcolor->staves->green = 0;
        objectcolor->staves->blue = 0;
        objectcolor->clefs->red = 0;
        objectcolor->clefs->green = 0;
        objectcolor->clefs->blue = 0;
        objectcolor->objects->red = 0;
        objectcolor->objects->green = 0;
        objectcolor->objects->blue = 0;

        return objectcolor;

}
