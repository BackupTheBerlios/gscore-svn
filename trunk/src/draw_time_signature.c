/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * draw_time_signature.c
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
#include "draw_time_signature.h"
#include "spacings.h"
#include "constants.h"
#include "gscore-font-constants.h"

extern gboolean
draw_time_signature(Score_t *score, Staff_t *staff, cairo_t *cr, gboolean selected)
{

        gdouble key_signature_start_x;
        gchar *tmp;


        key_signature_start_x = staff->extremity_begin_x + Spacings.Clefs.sb + (score->zoom * TREBLE_CLEF_WIDTH_FACTOR) + Spacings.Clefs.sa;

        cairo_select_font (cr, "gscore", CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_BOLD);

        cairo_set_rgb_color (cr, 
                             score->ColorObject->clefs->red, score->ColorObject->clefs->green, score->ColorObject->clefs->blue);

        switch ( staff->time_signature[0] ) {
        case TIME_SIGNATURE_NORMAL:
                cairo_move_to(cr, key_signature_start_x + get_key_signature_spacing(score, staff) + Spacings.KeySignatures.saks,
                              staff->extremity_begin_y + 16);
                cairo_scale_font (cr, 16);
                tmp  = g_strdup_printf("%d", staff->time_signature[1]);
                cairo_show_text (cr, tmp);
                g_free(tmp);
                cairo_move_to(cr, key_signature_start_x + get_key_signature_spacing(score, staff) + Spacings.KeySignatures.saks,
                              staff->extremity_begin_y + 32);
                cairo_show_text (cr, g_strdup_printf("%d", staff->time_signature[2]));
                break;
        case TIME_SIGNATURE_COMMON_TIME:
                cairo_move_to(cr, key_signature_start_x + get_key_signature_spacing(score, staff) + Spacings.KeySignatures.saks,
                              staff->extremity_begin_y + 16);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, COMMON_TIME_GLYPH);
                break;
        case TIME_SIGNATURE_ALLA_BREVE:
                cairo_move_to(cr, key_signature_start_x + get_key_signature_spacing(score, staff) + Spacings.KeySignatures.saks,
                              staff->extremity_begin_y + 16);
                cairo_scale_font (cr, score->zoom);
                cairo_show_text (cr, ALLA_BREVE_GLYPH);
                break;
        }

        return TRUE;
}
