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
        guchar *text;
/*         PangoGlyphString *glyph; */
/*         PangoContext *context; */
/*         PangoFontDescription *font_desc; */
/*         PangoLayout  *layout; */

/*         PangoRectangle physical_rectangle; */
/*         PangoRectangle logical_rectangle; */

/*         font_desc = pango_font_description_new(); */
/*         pango_font_description_set_family(font_desc, "gscore"); */
/*         pango_font_description_set_size(font_desc, 12); */

/*         context = pango_context_new(); */
/*         pango_context_set_font_description(context, font_desc); */

/*         layout = pango_layout_new(context); */
/* /\*         pango_layout_set_font_description(layout, font_desc); *\/ */
/*         pango_layout_set_text(layout, "a", -1); */
/* /\*         pango_context_set_font_map(context, font_map); *\/ */

/*         pango_layout_get_pixel_extents(layout,  */
/*                                        &physical_rectangle, */
/*                                        &logical_rectangle); */

/*         g_print("===== physical_rectangle.width = %d\n", physical_rectangle.width); */
/*         g_print("===== logical_rectangle.width = %d\n", logical_rectangle.width); */

        key_signature_start_x = staff->extremity_begin_x + Spacings.Clefs.sb + (score->zoom * TREBLE_CLEF_WIDTH_FACTOR) + Spacings.Clefs.sa;

        cairo_select_font_face (cr, "gscore", CAIRO_FONT_SLANT_NORMAL,
                                CAIRO_FONT_WEIGHT_BOLD);

        cairo_set_source_rgb (cr, 
                              score->ColorObject->clefs->red, score->ColorObject->clefs->green, score->ColorObject->clefs->blue);

        switch ( staff->time_signature[0] ) {
        case TIME_SIGNATURE_NORMAL:
                cairo_move_to(cr, key_signature_start_x + get_key_signature_spacing(score, staff) + Spacings.KeySignatures.saks,
                              staff->extremity_begin_y + 18);
                cairo_set_font_size (cr, 18);
                text  = (guchar *)g_strdup_printf("%d", staff->time_signature[1]);
                cairo_show_text (cr, text);
                g_free(text);
                cairo_move_to(cr, key_signature_start_x + get_key_signature_spacing(score, staff) + Spacings.KeySignatures.saks,
                              staff->extremity_begin_y + 36);
                text = g_strdup_printf("%d", staff->time_signature[2]);
                cairo_show_text (cr, text);
                g_free(text);
                break;
        case TIME_SIGNATURE_COMMON_TIME:
                cairo_move_to(cr, key_signature_start_x + get_key_signature_spacing(score, staff) + Spacings.KeySignatures.saks,
                              staff->extremity_begin_y + 18);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, COMMON_TIME_GLYPH);


/*                 pango_shape */
/*                         (const gchar *text, */
/*                          gint length, */
/*                          PangoAnalysis *analysis, */
/*                          &glyph); */
/*                 pango_glyph_string_get_logical_widths */
/*                         (PangoGlyphString *glyphs, */
/*                          const char *text, */
/*                          int length, */
/*                          int embedding_level, */
/*                          int *logical_widths); */

                break;
        case TIME_SIGNATURE_ALLA_BREVE:
                cairo_move_to(cr, key_signature_start_x + get_key_signature_spacing(score, staff) + Spacings.KeySignatures.saks,
                              staff->extremity_begin_y + 18);
                cairo_set_font_size (cr, score->zoom);
                cairo_show_text (cr, ALLA_BREVE_GLYPH);
                break;
        }

        return TRUE;
}
