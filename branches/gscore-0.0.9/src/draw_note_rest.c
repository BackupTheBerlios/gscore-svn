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
#include "staff.h"
#include "gscore-cairo.h"


extern guint
draw_note_rest(Score_t *score, Staff_t *staff, Object_t *object, cairo_t *cr, gdouble x)
{
        gboolean stemup;
        gdouble average;

        gdouble y = 0;
        gdouble yline = 0;

        cairo_text_extents_t *extents = NULL;


        /* *FIXME*: '-5' is here for the height of the note, this is dirty */
        average = (staff_get_y_for_line(staff, staff->nb_lines) - staff->extremity_begin_y) / 2 - 5;

        cairo_select_font_face (cr, "gscore", CAIRO_FONT_SLANT_NORMAL,
                                CAIRO_FONT_WEIGHT_BOLD);

        gscore_cairo_object_colorize(score, object, cr);

	y = get_y_from_position_no_key(8, 4, staff->extremity_begin_y, 8, object->pitch); 

        /* BEGIN: Get the stem direction */
        if ( (y < staff->extremity_begin_y + average) || object->nature & O_STEMDOWN )
                stemup = FALSE;
        else
                stemup = TRUE;
        
        if ( object->nature & O_STEMUP )
                stemup = TRUE;
        /* END: Get the stem direction */

        switch (object->type) {
        case DOUBLEWHOLE:
                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, DOUBLEWHOLE_GLYPH);

                x += Spacings.NotesRests.sa_doublewhole;
        break;
        case DOUBLEWHOLEREST:
                yline = staff_get_y_for_line(staff, 2);
                yline -= staff->space_btw_lines / 4;

                cairo_move_to(cr, x, yline);
                cairo_set_font_size (cr, score->zoom);
                /* *FIXME*: According to Gardner Read, the glyph is not correct */
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
                yline = staff_get_y_for_line(staff, 2);
                yline -= staff->space_btw_lines;

                cairo_move_to(cr, x, yline);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, WHOLE_REST_GLYPH);

                x += Spacings.NotesRests.sa_whole;
        break;
        case HALF:
/*                 cairo_text_extents(cr, HALF_GLYPH, extents); */

                if (stemup) {
                        cairo_move_to(cr, x + 10.5, y + 4);
                        cairo_line_to(cr, x + 10.5, y - 25);
                        cairo_stroke(cr);
                } else {
                        cairo_move_to(cr, x + 0.5, y + 4);
                        cairo_line_to(cr, x + 0.5, y + 29);
                        cairo_stroke(cr);
                }

                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, HALF_GLYPH);

                x += Spacings.NotesRests.sa_half;
        break;
        case HALFREST:
                yline = staff_get_y_for_line(staff, 2);

                cairo_move_to(cr, x, yline);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, HALF_REST_GLYPH);

                x += Spacings.NotesRests.sa_half;
        break;
        case QUARTER:
                if (stemup) {
                        cairo_move_to(cr, x + 9.5, y + 4);
                        cairo_line_to(cr, x + 9.5, y - 25);
                        cairo_stroke(cr);
                } else {
                        cairo_move_to(cr, x + 0.5, y + 4);
                        cairo_line_to(cr, x + 0.5, y + 29);
                        cairo_stroke(cr);
                }

                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, QUARTER_GLYPH);

                x += Spacings.NotesRests.sa_quarter;
        break;
        case QUARTERREST:
                yline = staff_get_y_for_line(staff, 2);

                cairo_move_to(cr, x, yline);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, QUARTER_REST_GLYPH);

                x += Spacings.NotesRests.sa_quarter;
        break;
        case EIGHTH:
                if (stemup) {
                        cairo_move_to(cr, x + 9.5, y + 4);
                        cairo_line_to(cr, x + 9.5, y - 25);
                        cairo_stroke(cr);
                        cairo_move_to(cr, x + 9.5, y - 25);
                        cairo_set_font_size (cr, score->zoom);
                        cairo_show_text (cr, EIGHT_STEM_UP_GLYPH);
                } else {
                        cairo_move_to(cr, x + 0.5, y + 4);
                        cairo_line_to(cr, x + 0.5, y + 29);
                        cairo_stroke(cr);
                        cairo_move_to(cr, x + 0.5, y + 29);
                        cairo_set_font_size (cr, score->zoom);
                        cairo_show_text (cr, EIGHT_STEM_DOWN_GLYPH);
                }

                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, QUARTER_GLYPH);

                x += Spacings.NotesRests.sa_eighth;
        break;
        case EIGHTHREST:
                yline = staff_get_y_for_line(staff, 2);

                cairo_move_to(cr, x, yline);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, EIGHTH_REST_GLYPH);

                x += Spacings.NotesRests.sa_eighth;
        break;
        case SIXTEENTH:
                if (stemup) {
                        cairo_move_to(cr, x + 9.5, y + 4);
                        cairo_line_to(cr, x + 9.5, y - 25);
                        cairo_stroke(cr);
                        cairo_move_to(cr, x + 9.5, y - 25);
                        cairo_set_font_size (cr, score->zoom);
                        cairo_show_text (cr, SIXTEENTH_STEM_UP_GLYPH);
                } else {
                        cairo_move_to(cr, x + 0.5, y + 4);
                        cairo_line_to(cr, x + 0.5, y + 29);
                        cairo_stroke(cr);
                        cairo_move_to(cr, x + 0.5, y + 29);
                        cairo_set_font_size (cr, score->zoom);
                        cairo_show_text (cr, SIXTEENTH_STEM_DOWN_GLYPH);
                }

                cairo_move_to(cr, x, y + 4);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, QUARTER_GLYPH);

                x += Spacings.NotesRests.sa_sixteenth;
        break;
        case SIXTEENTHREST:
                yline = staff_get_y_for_line(staff, 2);

                cairo_move_to(cr, x, yline);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, SIXTEENTH_REST_GLYPH);

                x += Spacings.NotesRests.sa_sixteenth;
        break;
        }


        return x;
}
