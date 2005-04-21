/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * draw_key.c
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
#include "spacings.h"
#include "constants.h"
#include "gscore-font-constants.h"

extern gboolean
draw_key(Score_t *score, Staff_t *staff, cairo_t *cr, gboolean selected)
{

        cairo_select_font (cr, "gscore", CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_BOLD);

        cairo_set_rgb_color (cr, 
                             score->ColorObject->clefs->red, score->ColorObject->clefs->green, score->ColorObject->clefs->blue);

        switch ( staff->key ) {
        case TREBLE_KEY:
                cairo_move_to(cr, staff->extremity_begin_x + Spacings.Clefs.sb,
                              staff->extremity_begin_y + 25);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, TREBLE_GLYPH);
                cairo_stroke(cr);
                break;
        case ALTO_KEY:
/*                 cairo_move_to(cr, staff->extremity_begin_x + Spacings.Clefs.sb, */
/*                               staff->extremity_begin_y + 9); */
/*                 cairo_scale_font (cr, 30); */
/*                 cairo_show_text (cr, ALTO_GLYPH); */
/*                 cairo_stroke(cr); */
                break;
        case TENOR_KEY:
                cairo_move_to(cr, staff->extremity_begin_x + Spacings.Clefs.sb,
                              staff->extremity_begin_y + 9);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, TENOR_GLYPH);
                cairo_stroke(cr);
                break;
        case BASS_KEY:
                cairo_move_to(cr, staff->extremity_begin_x + Spacings.Clefs.sb,
                              staff->extremity_begin_y + 9);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, BASS_GLYPH);
                cairo_stroke(cr);
                break;
        case PERCUSSION_KEY:
/*                 cairo_move_to(cr, staff->extremity_begin_x + Spacings.Clefs.sb, */
/*                               staff->extremity_begin_y + 9); */
/*                 cairo_scale_font (cr, 30); */
/*                 cairo_show_text (cr, BASS_GLYPH); */
/*                 cairo_stroke(cr); */
                break;
        case TREBLE_8VB_KEY:
/*                 cairo_move_to(cr, staff->extremity_begin_x + Spacings.Clefs.sb, */
/*                               staff->extremity_begin_y + 9); */
/*                 cairo_scale_font (cr, 30); */
/*                 cairo_show_text (cr, BASS_GLYPH); */
/*                 cairo_stroke(cr); */
                break;
        case BASS_8VB_KEY:
/*                 cairo_move_to(cr, staff->extremity_begin_x + Spacings.Clefs.sb, */
/*                               staff->extremity_begin_y + 9); */
/*                 cairo_scale_font (cr, 30); */
/*                 cairo_show_text (cr, BASS_GLYPH); */
/*                 cairo_stroke(cr); */
                break;
        case BARITONE_KEY:
/*                 cairo_move_to(cr, staff->extremity_begin_x + Spacings.Clefs.sb, */
/*                               staff->extremity_begin_y + 9); */
/*                 cairo_scale_font (cr, 30); */
/*                 cairo_show_text (cr, BASS_GLYPH); */
/*                 cairo_stroke(cr); */
                break;
        case TAB_KEY:
                cairo_move_to(cr, staff->extremity_begin_x + Spacings.Clefs.sb,
                              staff->extremity_begin_y + 20);
                cairo_scale_font (cr, 30);
                cairo_show_text (cr, TAB_GLYPH);
                cairo_stroke(cr);
                break;
        }

        return TRUE;
}
         
