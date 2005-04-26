/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * draw_key_signature.c
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
#include "draw_key_signature.h"
#include "spacings.h"
#include "constants.h"
#include "gscore-font-constants.h"

extern gboolean
draw_key_signature(Score_t *score, Staff_t *staff, cairo_t *cr, gboolean selected)
{

        gdouble key_signature_start_x;

        key_signature_start_x = staff->extremity_begin_x + Spacings.Clefs.sb + (score->zoom * TREBLE_CLEF_WIDTH_FACTOR) + Spacings.Clefs.sa;


        cairo_select_font (cr, "gscore", CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_BOLD);

        cairo_set_rgb_color (cr,
                             score->ColorObject->objects->red, score->ColorObject->objects->green, score->ColorObject->objects->blue);

        switch ( staff->key_signature ) {
	case KEY_SIGNATURE_EMPTY:
	case KEY_SIGNATURE_TREBLE_EMPTY:
        case KEY_SIGNATURE_ALTO_EMPTY:
        case KEY_SIGNATURE_TENOR_EMPTY:
        case KEY_SIGNATURE_BASS_EMPTY:
        case KEY_SIGNATURE_TREBLE_8VB_EMPTY:
        case KEY_SIGNATURE_BASS_8VB_EMPTY:
		break;
        case KEY_SIGNATURE_TREBLE_F_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_C_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_G_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y - 5);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_D_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y - 5);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 8);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_A_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y - 5);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 8);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 19);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_E_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y - 5);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 8);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 19);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (5 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_B_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y - 5);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 8);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 19);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (5 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (6 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 16);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_B_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 17);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_E_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 17);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_A_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 17);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 20);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_D_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 17);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 20);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 9);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_G_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 17);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 20);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 9);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 25);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_C_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 17);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 20);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 9);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 25);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (5 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 13);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_TREBLE_F_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 17);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 20);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 9);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 25);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (5 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 13);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (6 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 29);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_F_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 8);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_C_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 8);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 19);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_G_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 8);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 19);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_D_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 8);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 19);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 16);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_A_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 8);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 19);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 16);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 29);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_E_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 8);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 19);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 16);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 29);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (5 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_B_SHARP:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 8);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 19);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 5);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 16);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 29);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (5 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, SHARP_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (6 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 25);
                cairo_show_text (cr, SHARP_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_B_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 25);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_E_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 25);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_A_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 25);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 29);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_D_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 25);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 29);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 17);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_G_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 25);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 29);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 17);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 25);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_C_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 25);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 29);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 17);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 25);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (5 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 13);
                cairo_show_text (cr, FLAT_GLYPH);
                break;
        case KEY_SIGNATURE_BASS_F_FLAT:
                cairo_move_to(cr, key_signature_start_x,
                              staff->extremity_begin_y + 25);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + Spacings.KeySignatures.sbksa,
                              staff->extremity_begin_y + 12);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (2 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 29);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (3 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 17);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (4 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 33);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (5 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 20);
                cairo_show_text (cr, FLAT_GLYPH);
                cairo_move_to(cr, key_signature_start_x + (6 * Spacings.KeySignatures.sbksa),
                              staff->extremity_begin_y + 37);
                cairo_show_text (cr, FLAT_GLYPH);
                break;

        }

        return TRUE;
}
         
