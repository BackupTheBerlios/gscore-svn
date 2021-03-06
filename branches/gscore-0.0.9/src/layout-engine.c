/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * layout_engine.c
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
#include <libgscore.h>
#include <cairo.h>

#include "gscore.h"
#include "layout-engine.h"

#include "constants.h"
#include "display.h"
#include "common.h"
#include "macros.h"
#include "draw_barline.h"
#include "draw_staff.h"
#include "draw_key.h"
#include "draw_key_signature.h"
#include "draw_note_rest.h"
#include "draw_pitch_cursor.h"
#include "draw_time_signature.h"
#include "gscore-font-constants.h"
#include "spacings.h"
#include "selection.h"

static guint object_x = 0;
static guint measure_number = 1;

/*
void layout_paint(GtkWidget *widget,
                  cairo_t   *cr,
                  GtkRange  *range)
*/
extern gboolean 
layout_expose(GtkWidget *widget,
              GdkEventExpose *event,
              Score_t *score)
{
        cairo_t *cr = gdk_cairo_create(widget->window);

        GList * listrunner_staff = NULL;
        GList * listrunner_object = NULL;

        gint width, height;
        gint i;


        g_assert( score );

        width  = widget->allocation.width;
        height = widget->allocation.height;

        /*
	 * enclosing the painting function in a save/restore pair is a
         * good idea since we'll return to a sane state then
         */

        cairo_save (cr);

        /* clear background */

        cairo_rectangle (cr, 0, 0, width, height);
        cairo_set_source_rgb (cr, 1,1,1);
        cairo_fill (cr);


        /* enclosing in a save/restore pair since we alter the
         * font size
         */
        cairo_save (cr);


        /***************
         * Draw Staves *
         ***************/
        /* We walk through staves */
        listrunner_staff = g_list_first(score->Staff_list);
        while ( listrunner_staff ) {
                measure_number = 1;

                Staff_t *staff;
                staff = (Staff_t *)listrunner_staff->data;

                object_x = staff->extremity_begin_x + Spacings.Clefs.sb + (score->zoom * TREBLE_CLEF_WIDTH_FACTOR) + Spacings.Clefs.sa + get_key_signature_spacing(score, staff) + Spacings.KeySignatures.saks + Spacings.TimeSignatures.width + Spacings.TimeSignatures.sats;

                draw_staff(score, cr, 
                           staff->nb_lines, staff->space_btw_lines,
                           staff->extremity_begin_x, staff->extremity_begin_y,
                           score->staff_extremity_end_x, staff->is_selected);
                
/*                 if ( display->clefs ) */
                        draw_key(score, staff, cr, FALSE);

/*                 if ( display->key_signature ) */
                        draw_key_signature(score, staff, cr, FALSE);

/*                 if ( display->time_signature ) */
                        draw_time_signature(score, staff, cr, FALSE);

		listrunner_object = g_list_first(staff->Object_list);
 		while ( listrunner_object ) { 
 			Object_t *object = NULL;
 			object = (Object_t *)listrunner_object->data;

/*                         g_print("object->pitch = %d \n", object->pitch); */
/*                         g_print("%s:%d: x = %f\n", __FILE__, __LINE__, object_x); */
			
			if (object) {

                                draw_staff_extension(score, staff, cr, object->pitch, object_x);
/*                                 g_print("layout engine, object_type = %d\n", object->type); */

				switch(object->type) {

				case PITCH_CURSOR:
					object_x = draw_pitch_cursor(score, staff, cr, object_x, object->pitch);
				        break;
                                case BARLINE_SINGLE:
                                        object_x = draw_barline_single(score, staff, object, cr, object_x);
                                        break;
				case DOUBLEWHOLE:
                                case DOUBLEWHOLEREST:
				case WHOLE:
                                case WHOLEREST:
				case HALF:
                                case HALFREST:
				case QUARTER:
                                case QUARTERREST:
				case EIGHTH:
                                case EIGHTHREST:
				case SIXTEENTH:
                                case SIXTEENTHREST:
                                        object_x = draw_note_rest(score, staff, object, cr, object_x);
					break;
                                default:
                                        g_print("Unknown object type: %d\n", object->type);

				}
			}
			
			listrunner_object = g_list_next(listrunner_object);
		}
		
                listrunner_staff = g_list_next(listrunner_staff);
        } /* while ( listrunner_staff ) */


        cairo_set_source_rgb (cr, 0, 0, 0);

        /* Show the quarter note head */
/*         cairo_select_font (cr, "gscore", CAIRO_FONT_SLANT_NORMAL, */
/*                            CAIRO_FONT_WEIGHT_BOLD); */
/*         cairo_save (cr); */
/*         cairo_scale_font (cr, 30); */
/*         cairo_move_to (cr, 100.5, 54); */
/*         cairo_set_rgb_color (cr, 0,0,0); */
/*         cairo_show_text (cr, QUARTER_GLYPH); */

        /* Show the stem */
        /* Line */
/*         cairo_move_to(cr, 100.5, 54); */
/*         cairo_rel_line_to(cr, 0, 30.5); */
/*         cairo_stroke(cr); */
/*         /\* Sixteenth *\/ */
/*         cairo_move_to (cr, 101, 84.5); */
/*         cairo_show_text (cr, SIXTEENTH_STEM_DOWN_GLYPH); */


/*         /\* Add a sharp to the note *\/ */
/*         cairo_move_to (cr, 90, 54); */
/*         cairo_scale_font (cr, 1); */
/*         cairo_set_rgb_color (cr, 0,0,0); */
/*         cairo_show_text (cr, SHARP_GLYPH); */
/*         cairo_stroke(cr); */

/*         /\* Show the key *\/ */
/*         cairo_move_to (cr, 15.5, 75); */
/*         cairo_scale_font (cr, 1); */
/*         cairo_set_rgb_color (cr, 0,0,0); */
/*         cairo_show_text (cr, TREBLE_GLYPH); */
/*         cairo_stroke(cr); */

/*         /\* Add 2/4 *\/ */
/*         cairo_move_to (cr, 40, 66.5); */
/*         cairo_scale_font (cr, 0.5); */
/*         cairo_show_text (cr, "2"); */

/*         cairo_move_to (cr, 40, 82.5); */
/*         cairo_show_text (cr, "4"); */


/*         cairo_restore (cr); */

/*         cairo_set_rgb_color (cr, 1,0,0); */
/*         cairo_scale_font (cr, 15); */
/*         cairo_move_to (cr, 50, 100); */


        cairo_stroke (cr);

        cairo_restore (cr);

        selection_paint(cr, score);
}


