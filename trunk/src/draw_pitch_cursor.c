/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * key_cursor.c
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
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#include <gtk/gtk.h>
#include <cairo.h>

#include "gscore.h"
#include "draw_pitch_cursor.h"
#include "spacings.h"
#include "constants.h"
#include "position.h"

extern gdouble
draw_pitch_cursor(Score_t *score, Staff_t *staff, cairo_t *cr, gdouble x, gint pitch)
{
	gdouble y = 0;
	
	
	x += staff->extremity_begin_x + Spacings.Clefs.sb + (score->zoom * TREBLE_CLEF_WIDTH_FACTOR) + Spacings.Clefs.sa + get_key_signature_spacing(score, staff) + Spacings.KeySignatures.saks + 20;
	
	cairo_set_source_rgb(cr, 0, 0.5, 0);


	y = get_y_from_position_no_key(8, 4, staff->extremity_begin_y, 8, pitch) + 1; 

	cairo_rectangle(cr, x, y, 10, 6);
	cairo_fill(cr);
	
	return x;
}
