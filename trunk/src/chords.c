/*
 * chords.c
 * gscore - a musical score editor
 *
 * (C) Copyright 2001-2005 Sebastien Tricaud
 * e-mail : toady@gscore.og
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

#include "gscore.h"
#include "position.h"
#include "constants.h"

guint make_chord(Staff_t *staff, gulong group_id, gint note_type, guint object_x)
{

	if (note_type == DOUBLEWHOLE) object_x -= object_get_spacing(DOUBLEWHOLE);
	if (note_type == WHOLE) object_x -= object_get_spacing(WHOLE);
	if (note_type == HALF) object_x -= object_get_spacing(HALF);
	if (note_type == QUARTER) object_x -= object_get_spacing(QUARTER);
	if (note_type == EIGHTH) object_x -= object_get_spacing(EIGHTH);
	if (note_type == SIXTEENTH) object_x -= object_get_spacing(SIXTEENTH);

	return object_x;

}

