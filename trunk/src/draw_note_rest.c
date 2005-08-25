/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * draw_note_rest.c
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
#include "draw_note_rest.h"
#include "spacings.h"
#include "constants.h"
#include "position.h"
#include "gscore-font-constants.h"

extern gboolean
draw_note_rest(Score_t *score, Staff_t *staff, cairo_t *cr, gint type, gboolean selected, gdouble x, gint pitch)
{
        gdouble y = 0;

/*         g_print("%s:%d: x = %f\n", __FILE__, __LINE__, x); */

        cairo_select_font_face (cr, "gscore", CAIRO_FONT_SLANT_NORMAL,
                                CAIRO_FONT_WEIGHT_BOLD);

        cairo_set_source_rgb (cr, 
                              score->ColorObject->objects->red, score->ColorObject->objects->green, score->ColorObject->objects->blue);

	y = get_y_from_position_no_key(8, 4, staff->extremity_begin_y, 8, pitch); 

        switch (type) {
        case DOUBLEWHOLE:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, DOUBLEWHOLE_GLYPH);
                x += Spacings.NotesRests.sa_doublewhole;
        break;
        case DOUBLEWHOLEREST:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, DOUBLEWHOLE_REST_GLYPH);
                x += Spacings.NotesRests.sa_doublewhole;
        break;
        case WHOLE:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, WHOLE_GLYPH);
                x += Spacings.NotesRests.sa_whole;
        break;
        case WHOLEREST:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, WHOLE_REST_GLYPH);
                x += Spacings.NotesRests.sa_whole;
        break;
        case HALF:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, HALF_GLYPH);
                x += Spacings.NotesRests.sa_half;
        break;
        case HALFREST:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, HALF_GLYPH);
                x += Spacings.NotesRests.sa_half;
        break;
        case QUARTER:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, QUARTER_GLYPH);
                x += Spacings.NotesRests.sa_quarter;
        break;
        case QUARTERREST:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, QUARTER_REST_GLYPH);
                x += Spacings.NotesRests.sa_quarter;
        break;
        case EIGHTH:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, QUARTER_GLYPH);
                x += Spacings.NotesRests.sa_eighth;
        break;
        case EIGHTHREST:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, EIGHTH_REST_GLYPH);
                x += Spacings.NotesRests.sa_eighth;
        break;
        case SIXTEENTH:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, QUARTER_GLYPH);
                x += Spacings.NotesRests.sa_sixteenth;
        break;
        case SIXTEENTHREST:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, SIXTEENTH_REST_GLYPH);
                x += Spacings.NotesRests.sa_sixteenth;
        break;
        }


        return x;
}
