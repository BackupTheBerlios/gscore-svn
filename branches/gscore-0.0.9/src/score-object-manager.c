/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * score-object-manager.c: manages all actions between everything.
 * When you enter a note, you can set up a plugin or script to do something with it,
 * the SOM allows this, since everything is passed throught SOM functions.
 *
 *                  +--------+-----------+
 *                  | Action | Scripting |
 *                  | Plugin | Manager   |
 *                  +--------------------+
 *   ----- foo -->  |  Score Object Mgr  | ------ bar ----->
 *                  +--------------------+
 *
 * gscore - a musical score editor
 *
 * (C) Copyright 2001-2005 Sebastien Tricaud
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

#include <gtk/gtk.h>
#include <stdio.h>

#include "score-object-manager.h"

extern void 
score_object_manager(SOMType type, GdkEvent *event, gpointer data, gpointer user_data)
{
        switch(type) {
        case MOUSE:
                printf("MOUSE\n");
                break;
        case KEYBOARD:
                printf("KEYBOARD\n");
                break;
        case DATASTRUCTURE_TO_CAIRO:
                printf("DATASTRUCTURE TO CAIRO\n");
                break;
        case CAIRO_TO_DATASTRUCTURE:
                printf("CAIRO TO DATASTRUCTURE\n");
                break;
        case FILTER_TO_DATASTRUCTURE:
                printf("FILTER TO DATASTRUCTURE\n");
                break;
        case DATASTRUCTURE_TO_FILTER:
                printf("DATASTRUCTURE TO FILTER\n");
                break;
        case CAIRO_TO_LAYOUT:
                printf("CAIRO TO LAYOUT\n");
                break;
        case CAIRO_TO_PRINTER:
                printf("CAIRO TO PRINTER\n");
                break;
        }
}
