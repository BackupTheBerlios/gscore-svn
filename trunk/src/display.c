/*
 * display.c
 * gscore - a musical score editor
 *
 * (C) Copyright 2001-2004 Sebastien Tricaud
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

#include "gscore.h"
#include "display.h"

void
barnotes (gpointer callback_data, guint callback_action, GtkWidget *widget)
{

}

void display_new_page(gint measure)
{

}

void display_measure_line_return(gint measure)
{
          GdkGC *gc;
          gint j = 0;

          gc = gdk_gc_new(Score.area->window);

          gdk_draw_line(Score.area->window, gc,
                        20,j, 20, j+20);

}
