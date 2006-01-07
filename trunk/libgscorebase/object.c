/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorebase/object.c
 * gscore - a musical notation software
 *
 * (C) Copyright 2001-2006 Sebastien Tricaud
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


#include <glib.h>

#include <libgscore/gscoretypes.h>
#include <libgscorebase/score.h>
#include <libgscorebase/staff.h>
#include <libgscorebase/object.h>

extern Object * gscore_object_new_default(Score *score, Staff *staff, gint type);


extern Object *
gscore_object_new_default(Score *score, Staff *staff, gint type)
{

        Object *object;

        staff->objects = NULL;

	object = g_malloc(sizeof(object));
        if ( ! object ) {
                g_print("Memory exhausted!\n");
                return NULL;
        }

	object->id          = ++score->object_id;
        object->type        = type;
        object->nature      = 0;
        object->accidentals = 0;
        object->group_id    = 0;
        object->x           = 0;
        object->y           = 0;
        object->x2          = 0;
        object->y2          = 0;
        object->x3          = 0;
        object->y3          = 0;
        object->pitch       = 0;
        object->tab_number  = 0;
        object->is_selected = FALSE;

        staff->objects =
                g_list_append(staff->objects, object);

        return object;

}

