/*
 * objects.c
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
#include "selection.h"
#include "debug.h"
#include "key_cursor.h"
#include "spacings.h"
#include "staff.h"

gint object_get_spacing(gint type)
{
	gint retval = 0;

	switch(type) {

	case DOUBLEWHOLE:
		retval = Spacings.NotesRests.sa_doublewhole;
		break;
	case WHOLE:
		retval = Spacings.NotesRests.sa_whole;
		break;
	case HALF:
		retval = Spacings.NotesRests.sa_half;
		break;
	case QUARTER:
		retval = Spacings.NotesRests.sa_quarter;
		break;
	case EIGHTH:
		retval = Spacings.NotesRests.sa_eighth;
		break;
	case SIXTEENTH:
		retval = Spacings.NotesRests.sa_sixteenth;
		break;
	case THIRTYSECOND:
		retval = Spacings.NotesRests.sa_thirtysecond;
		break;
	case SIXTYFOURTH:
		retval = Spacings.NotesRests.sa_sixtyfourth;
		break;
	case DOUBLEWHOLEREST:
		retval = Spacings.NotesRests.sa_doublewholerest;
		break;
	case WHOLEREST:
		retval = Spacings.NotesRests.sa_wholerest;
		break;
	case HALFREST:
		retval = Spacings.NotesRests.sa_halfrest;
		break;
	case QUARTERREST:
		retval = Spacings.NotesRests.sa_quarterrest;
		break;
	case EIGHTHREST:
		retval = Spacings.NotesRests.sa_eighthrest;
		break;
	case SIXTEENTHREST:
		retval = Spacings.NotesRests.sa_sixteenthrest;
		break;
	case THIRTYSECONDREST:
		retval = Spacings.NotesRests.sa_thirtysecondrest;
		break;
	case SIXTYFOURTHREST:
		retval = Spacings.NotesRests.sa_sixtyfourthrest;
		break;
	case BARLINE_SINGLE:
	case BARLINE_DOUBLE:
	case BARLINE_OPENREPEAT:
	case BARLINE_CLOSEREPEAT:
	case BARLINE_OPENCLOSEREPEAT:
		retval = Spacings.Barlines.sab;
		break;
	case DYNAMIC_PPPP:
	case DYNAMIC_PPP:
	case DYNAMIC_PP:
	case DYNAMIC_P:
	case DYNAMIC_MP:
	case DYNAMIC_MF:
	case DYNAMIC_F:
	case DYNAMIC_FF:
	case DYNAMIC_FFF:
		retval = 0;
		break;
	case TREBLE_KEY:
	case BASS_KEY:
	case ALTO_KEY:
	case TENOR_KEY:
		retval = STANDARD_KEY_SIZE;
		break;
	default:
		printf("Unknown value: %d\n", type);
		retval = 10;
		break;
	}

	return retval;
}

extern gboolean
add_object(gint staff, gint type, accidentals_e accidentals, object_e nature, gulong group_id,
           gint x, gint y, gint x2, gint y2, gint x3, gint y3, 
           gint pitch, gint tab_number, gboolean is_selected)
{
        Staff_t *staff_data;

/* 	printf("staff_selected: %d\n", staff); */

        staff_data = g_list_nth_data(Score.Staff_list, staff);


        staff_data->Object = g_malloc(sizeof(Object_t));

	if ( ! staff_data->Object ) {
		printf("Cannot add object, memory exhausted\n");
		return FALSE;
	}

        staff_data->Object->id = ++Score.object_id;
        staff_data->Object->type = type;
        staff_data->Object->nature = nature;
        staff_data->Object->accidentals = accidentals;
	staff_data->Object->group_id = group_id;
        staff_data->Object->x = x;
        staff_data->Object->y = y;
        staff_data->Object->x2 = x2;
        staff_data->Object->y2 = y2;
        staff_data->Object->x3 = x3;
        staff_data->Object->y3 = y3;
        staff_data->Object->pitch = pitch;
        staff_data->Object->tab_number = tab_number;
        staff_data->Object->is_selected = is_selected;

        staff_data->Object_list =
                g_list_append(staff_data->Object_list, staff_data->Object);

        staff_set_current_x(staff, staff_get_current_x(staff) + object_get_spacing(type));

	switch (type) {
	case DOUBLEWHOLE:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_doublewhole;
		break;
	case DOUBLEWHOLEREST:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_doublewholerest;
		break;
	case WHOLE:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_whole;
		break;
	case WHOLEREST:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_wholerest;
		break;
	case HALF:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_half;
		break;
	case HALFREST:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_halfrest;
		break;
	case QUARTER:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_quarter;
		break;
	case QUARTERREST:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_quarterrest;
		break;
	case EIGHTH:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_eighth;
		break;
	case EIGHTHREST:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_eighthrest;
		break;
	case SIXTEENTH:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_sixteenth;
		break;
	case SIXTEENTHREST:
		Score.staff_extremity_end_x += Spacings.NotesRests.sa_sixteenthrest;
		break;
	case BARLINE_SINGLE:
	case BARLINE_DOUBLE:
	case BARLINE_OPENREPEAT:
	case BARLINE_CLOSEREPEAT:
	case BARLINE_OPENCLOSEREPEAT:
		Score.staff_extremity_end_x += Spacings.Barlines.sab;
		break;
	case TREBLE_KEY:
	case BASS_KEY:
	case ALTO_KEY:
	case TENOR_KEY:
		Score.staff_extremity_end_x += STANDARD_KEY_SIZE;
		break;
	default:
		printf("(add_objects) Unknown object %d\n", type);
		break;
	}

	return TRUE;
}

extern gboolean 
remove_object(gulong id)
{
	GList *listrunner_staff;
	GList *listrunner_object;


	Staff_t *staff;

	listrunner_staff = g_list_first(Score.Staff_list);

	while ( listrunner_staff ) {
		staff = (Staff_t *)listrunner_staff->data;

		listrunner_object = g_list_first(staff->Object_list);
		while ( listrunner_object ) {
			Object_t *object;
			object = (Object_t *)listrunner_object->data;

			if ( object->id == id ) {
				staff->Object_list = g_list_remove(staff->Object_list, object);
				return TRUE;
			}

			listrunner_object = g_list_next(listrunner_object);
		}

		listrunner_staff = g_list_next(listrunner_staff);
	}

	return FALSE;
}

extern gboolean 
remove_object_selected(void)
{
	GList *listrunner_staff;
	GList *listrunner_object;

	Staff_t *staff;
	Object_t *object;

/* 	g_return_if_fail( object != NULL ); */

	listrunner_staff = g_list_first(Score.Staff_list);

	while ( listrunner_staff ) {
		staff = (Staff_t *)listrunner_staff->data;

		listrunner_object = g_list_first(staff->Object_list);
		while ( listrunner_object ) {
			object = (Object_t *)listrunner_object->data;

			if (object->is_selected) {
				staff->current_x -= object_get_spacing(object->type);
				listrunner_object = g_list_remove(listrunner_object, object);
			} else {
				listrunner_object = g_list_next(listrunner_object);
			}

		}

		listrunner_staff = g_list_next(listrunner_staff);
	}

	return TRUE;
}

Object_t *object_get_next(Object_t *object)
{
	GList *listrunner_staff;
	GList *listrunner_object;
	GList *list_object_next;

	Staff_t *staff_data;
	Object_t *object_data;

	listrunner_staff = g_list_first(Score.Staff_list);

	while ( listrunner_staff ) {
		staff_data = (Staff_t *)listrunner_staff->data;

		listrunner_object = g_list_first(staff_data->Object_list);
		while ( listrunner_object ) {
			object_data = (Object_t *)listrunner_object->data;

			if (object_data->id == object->id) {
			  list_object_next = g_list_next(listrunner_object);
			  if (list_object_next)
			    return (Object_t *) list_object_next->data;
			}

			listrunner_object = g_list_next(listrunner_object);
		}

		listrunner_staff = g_list_next(listrunner_staff);
	}

	return NULL;
}

/* Returns the object before the one provided as parameter */
Object_t *object_get_previous(Object_t *object)
{
	GList *listrunner_staff;
	GList *listrunner_object;
	GList *list_object_previous;

	Staff_t *staff_data;
	Object_t *object_data;

	listrunner_staff = g_list_first(Score.Staff_list);

	while ( listrunner_staff ) {
		staff_data = (Staff_t *)listrunner_staff->data;

		listrunner_object = g_list_first(staff_data->Object_list);
		while ( listrunner_object ) {
			object_data = (Object_t *)listrunner_object->data;

			if (object_data->id == object->id) {
			  list_object_previous  = g_list_previous(listrunner_object);
			  if (list_object_previous)
				  return (Object_t *) list_object_previous->data;
			}

			listrunner_object = g_list_next(listrunner_object);
		}

		listrunner_staff = g_list_next(listrunner_staff);
	}

	return NULL;
}

/* Returns the object closest to the left from the x position */
Object_t *object_get_left(gdouble x)
{
	GList *listrunner_staff;
	GList *listrunner_object;

	Staff_t *staff_data;
	Object_t *object_data;
	Object_t *ret_object;	/* The object to return */

	guint staff_counter = 0;

	guint object_x = 0;

	listrunner_staff = g_list_first(Score.Staff_list);

	printf("Running\n");

	while ( listrunner_staff ) {
		staff_data = (Staff_t *)listrunner_staff->data;

		printf("In staff\n");

		listrunner_object = g_list_first(staff_data->Object_list);
		while ( listrunner_object ) {
			object_data = (Object_t *)listrunner_object->data;

			printf("In object\n");

			switch(object_data->type) {
			case DOUBLEWHOLE:
				object_x += Spacings.NotesRests.sa_doublewhole;
			case DOUBLEWHOLEREST:
				object_x += Spacings.NotesRests.sa_doublewholerest;
			case WHOLE:
				object_x += Spacings.NotesRests.sa_whole;
			case WHOLEREST:
				object_x += Spacings.NotesRests.sa_wholerest;
			case HALF:
				object_x += Spacings.NotesRests.sa_half;
			case HALFREST:
				object_x += Spacings.NotesRests.sa_halfrest;
			case QUARTER:
				object_x += Spacings.NotesRests.sa_quarter;
			case QUARTERREST:
				object_x += Spacings.NotesRests.sa_quarterrest;
			case EIGHTH:
				object_x += Spacings.NotesRests.sa_eighth;
			case EIGHTHREST:
				object_x += Spacings.NotesRests.sa_eighthrest;
			case SIXTEENTH:
				object_x += Spacings.NotesRests.sa_sixteenth;
			case SIXTEENTHREST:
				object_x += Spacings.NotesRests.sa_sixteenthrest;
			case BARLINE_SINGLE:
			case BARLINE_DOUBLE:
			case BARLINE_OPENREPEAT:
			case BARLINE_CLOSEREPEAT:
			case BARLINE_OPENCLOSEREPEAT:
				object_x += Spacings.Barlines.sab;
			}
			

			printf("start_x + object_x = %d\n", staff_data->start_x + object_x);
			printf("Chosen x = %d\n", staff_data->start_x);
			
			if ((staff_data->start_x + object_x) < x) {

				printf("object type before: %d\n", object_data->type);
/* 				if (staff_counter == get_staff_selected()) */
/* 					ret_object = (Object_t *)object_data; */

			}

			listrunner_object = g_list_next(listrunner_object);
		}

		listrunner_staff = g_list_next(listrunner_staff);
		staff_counter++;
	}

	if ((staff_counter - 1) == get_staff_selected())
		return ret_object;

	return NULL;
}

static gint 
compare_object_x(Object_t *data1, Object_t *data2)
{
        /***
         *** To be used with g_list_insert_sorted(list, object, (GCompareFunc)compare)
         ***/
        
        return data1->x - data2->x;
}

extern gint 
get_object_properties (GtkWidget      *event_box,  
                       GdkEventButton *event,
                       gpointer        data)
{
    g_print ("Event box clicked at coordinates %f,%f\n",
             event->x, event->y);

    /* Returning TRUE means we handled the event, so the signal
     * emission should be stopped (don't call any further
     * callbacks that may be connected). Return FALSE
     * to continue invoking callbacks.
     */
    return FALSE;
}

extern gboolean
object_selected_change_type(gint newtype)
{
	gboolean something_selected = FALSE;
	Staff_t *staff_data;

	GList *listrunner;

	staff_data = (Staff_t *) g_list_nth_data(Score.Staff_list, get_staff_selected());

	listrunner = g_list_first(staff_data->Object_list);

	while (listrunner) {
		Object_t *object;

		object = (Object_t *)listrunner->data;

		if (object->is_selected) {
			object->type = newtype;
			something_selected = TRUE;
		}
                                  
		listrunner = g_list_next(listrunner);
	}

	g_list_free(listrunner);

	return something_selected;
}
