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
#include "draw_staff.h"

#include "constants.h"

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
                cairo_set_source_rgb (cr, 
                                     score->ColorObject->staves->red, score->ColorObject->staves->green, score->ColorObject->staves->blue);
        } else {                /* The following just checks you didn't choose to have a blue colored staff */
                if (( score->ColorObject->staves->red == 0 ) && 
                    ( score->ColorObject->staves->green == 0 ) && 
                    ( score->ColorObject->staves->blue == 1 )) {
                        cairo_set_source_rgb (cr, 1, 0, 0);
                } else {
                        cairo_set_source_rgb (cr, 0, 0, 1);
                }
        }

        while ( i < nb_lines ) {
                cairo_move_to(cr, x1, y1 + offset + cairo_padding);
                cairo_rel_line_to(cr, x2, 0);

                offset += space_btwn_lines + 1.0;

                i++;
        }

        cairo_set_line_width(cr, 1);
        cairo_stroke(cr);

        return TRUE;
}

/* That will draw the extension needed for notes on staff */
/* It's usefull when you need to see where the note is placed out from the staff */
extern void 
draw_staff_extension(Score_t *score, Staff_t *staff, cairo_t *cr, gint pitch, gdouble x)
{
        const gdouble cairo_padding = 0.5;
	gint draw_dash_helper = 0;
	gint i = 0;

        gdouble extremity_end_y = 0;

        extremity_end_y += staff->extremity_begin_y;
        extremity_end_y += (staff->nb_lines - 1) * staff->space_btw_lines + staff->nb_lines;

/* 	gdouble extremity_end_y = staff_from_object_get_extremity_end_y(score, staff); */

	switch(staff->key) {
	case NO_KEY:
	case TREBLE_KEY:
		if (pitch > 7) {
			draw_dash_helper = pitch - 6;

			for ( i = 1; i <= draw_dash_helper / 2; i ++ ) {
                                cairo_move_to(cr, 
                                              x - 4, 
                                              cairo_padding + staff->extremity_begin_y - (i * staff->space_btw_lines) - i);
                                cairo_line_to(cr, 
                                              x + 13, 
                                              cairo_padding + staff->extremity_begin_y - (i * staff->space_btw_lines) - i);
			}
		}

		if (pitch < -3) {

			draw_dash_helper = pitch + 2;

			draw_dash_helper = -draw_dash_helper;

			for ( i = 1; i <= draw_dash_helper / 2; i++ ) {
                                cairo_move_to(cr,
                                              x - 4,
                                              -1 + cairo_padding + extremity_end_y + (i * staff->space_btw_lines) + i);
                                cairo_line_to(cr,
                                              x + 13,
                                              -1 + cairo_padding + extremity_end_y + (i * staff->space_btw_lines) + i);
			}
		}

                cairo_stroke(cr);

		break;
	}
}
