/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * pitch_cursor.c
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

#include "gscore.h"
#include "pitch_cursor.h"

#include "constants.h"
#include "spacings.h"

extern 
void pitch_cursor_move_after(Score_t *score, Staff_t *staff, Object_t *object)
{
/*         GList *listrunner_object = NULL; */
/*         Object_t *object_tmp = NULL; */
/*         gdouble pcu_id; */
/*         gint index; */

/*         listrunner_object = g_list_first(staff->Object_list); */
/*         while ( listrunner_object ) { */
/*                 Object_t *object_data = NULL; */
/*                 object_data = (Object_t *)listrunner_object->data; */

/*                 if ( (object_data) && (object_data->type == PITCH_CURSOR) ) { */
/*                         pcu_id = object_data->id; */
/*                         listrunner_object = g_list_remove(listrunner_object, object_data); */
/*                 } */

/*                 listrunner_object = g_list_next(listrunner_object); */
/*         } */

/*         object_tmp = malloc(sizeof(struct Object_t)); */

/*         object_tmp->id = pcu_id; */
/*         object_tmp->type = PITCH_CURSOR; */
/*         object_tmp->nature = 0; */
/*         object_tmp->accidentals = 0; */
/*         object_tmp->group_id = 0; */
/*         object_tmp->x = 0; */
/*         object_tmp->y = 0; */
/*         object_tmp->x2 = 0; */
/*         object_tmp->y2 = 0; */
/*         object_tmp->x3 = 0; */
/*         object_tmp->y3 = 0; */
/*         object_tmp->pitch = 0; */
/*         object_tmp->tab_number = 0; */
/*         object_tmp->is_selected = FALSE; */

/*         index = g_list_index(listrunner_object, object); */

/*         g_print("Index object = %d\n", index); */
                        
/*         listrunner_object = g_list_insert(listrunner_object, object_tmp, index); */

/*         g_free(object_tmp); */

}
