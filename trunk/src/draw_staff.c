/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * draw_staff.c
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
#include <cairo.h>

#include "gscore.h"

/**
 * draw_staff:
 * @sw: #ScoreWidget object
 * @cr: cairo_t pointer
 * @nb_lines: number of lines you want the staff to have
 * @space_btwn_lines:
 * @x1:
 * @y1:
 * @x2:
 * @selected: If we should draw the selected staff
 *
 * Draws a staff on the score widget and fills the cairo structure
 * 
 * Returns: TRUE if success, FALSE if failed.
 */
extern gboolean
draw_staff(Score_t *score, cairo_t *cr, 
           guint16 nb_lines, gdouble space_btwn_lines,
           gdouble x1, gdouble y1, gdouble x2,
           gboolean selected)
{

        const gdouble cairo_padding = 0.5;
        gdouble offset = 0;
	gint16 i = 0;

        if ( ! selected ) {
                cairo_set_rgb_color (cr, 
                                     score->ColorObject->staves->red, score->ColorObject->staves->green, score->ColorObject->staves->blue);
        } else {                /* The following just checks you didn't choose to have a blue colored staff */
                if (( score->ColorObject->staves->red == 0 ) && 
                    ( score->ColorObject->staves->green == 0 ) && 
                    ( score->ColorObject->staves->blue == 1 )) {
                        cairo_set_rgb_color (cr, 1, 0, 0);
                } else {
                        cairo_set_rgb_color (cr, 0, 0, 1);
                }
        }

        while ( i < nb_lines ) {
                cairo_move_to(cr, x1, y1 + offset + cairo_padding);
                cairo_rel_line_to(cr, x2, 0);

                offset += space_btwn_lines;

                i++;
        }

        cairo_set_line_width(cr, 1);
        cairo_stroke(cr);

        return TRUE;
}
