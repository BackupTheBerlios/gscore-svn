/*
 * realize_area.c
 * gscore - a musical score editor
 *
 * (C) Copyright 2001-2004 Sebastien Tricaud
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
 *
 */

/** 
 * @file
 * 
 *  The Score area widget has its callback here
 */

#include <gtk/gtk.h>
#include <string.h>

#include "gscore.h"
#include "constants.h"
#include "file.h"
#include "error.h"
#include "draw.h"
#include "draw_barline.h"
#include "position.h"
#include "selection.h"
#include "staff.h"
#include "common.h"
#include "objects.h"
#include "debug.h"
#include "articulation.h"
#include "beam.h"
#include "key_cursor.h"
#include "macros.h"
#include "text.h"
#include "spacings.h"


guint timesignature_x = 0;
guint object_x = 0;
guint measure_number = 1;

static void 
realize_key(Staff_t *staff)
{
	switch ( staff->key )
		{
		case TREBLE_KEY:
			draw_pixmap(Score.area->window, CLEF_G,
				    staff->extremity_begin_x + Spacings.Clefs.sb,
				    staff->extremity_begin_y - 8);
			break;
		case BASS_KEY:
			draw_pixmap(Score.area->window, CLEF_F,
				    staff->extremity_begin_x + Spacings.Clefs.sb,
				    staff->extremity_begin_y + 1);
			break;
		case ALTO_KEY:
			draw_pixmap(Score.area->window, CLEF_C,
				    staff->extremity_begin_x + Spacings.Clefs.sb,
				    staff->extremity_begin_y + 5);
			break;
		case TAB_KEY:
			draw_pixmap(Score.area->window, CLEF_TAB,
				    staff->extremity_begin_x + Spacings.Clefs.sb,
				    staff->extremity_begin_y + 7);
			break;
		}
}

/** Returns the position where the time signatures/or objects should be  */
static gdouble 
realize_key_signature(Staff_t *staff)
{
	guint keysignature_x = staff->extremity_begin_x + Spacings.Clefs.sb + STANDARD_KEY_SIZE + Spacings.Clefs.sa;

	/* Key Signature */
	/* There're a few issues here. Actualy, the hard coded numbers, like: */
	/* staff->extremity_begin_y + 4 is really bad! it only works for TREBLE_KEY and with the pixmaps */
	switch (staff->key_signature) {

	case KEY_SIGNATURE_TREBLE_EMPTY:
		timesignature_x = keysignature_x;
		break;
	case KEY_SIGNATURE_TREBLE_A_SHARP:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x,
			    staff->extremity_begin_y - 10);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y + 4);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 2 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y - 13);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 3 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y - 1);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 4 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y + 13);
		
		timesignature_x = 
			keysignature_x + 
			4 * Spacings.KeySignatures.sbksa + 
/* 			5 * STANDARD_ACCIDENTAL_SIZE + */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_A_FLAT:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x,
			    staff->extremity_begin_y + 5);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y - 9);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 2 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y + 9);
		
		timesignature_x = 
			keysignature_x + 
			2 * Spacings.KeySignatures.sbksa + 
/* 			3 * STANDARD_ACCIDENTAL_SIZE +  */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_B_SHARP:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x,
			    staff->extremity_begin_y - 10);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y + 4);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 2 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y - 13);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 3 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y - 1);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 4 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y + 13);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 5 * Spacings.KeySignatures.sbksa),
			    staff->extremity_begin_y - 5);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 6 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y + Spacings.KeySignatures.sbksa); /* Weird!!! ? but it works! I did that ? I dunno! */
		
		timesignature_x = 
			keysignature_x + 
			6 * Spacings.KeySignatures.sbksa + 
/* 			7 * STANDARD_ACCIDENTAL_SIZE +  */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_B_FLAT:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x,
			    staff->extremity_begin_y + 5);

		timesignature_x = 
			keysignature_x + 
/* 			STANDARD_ACCIDENTAL_SIZE +  */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_C_SHARP:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x,
			    staff->extremity_begin_y - 10);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y + 4);
		
		timesignature_x = 
			keysignature_x + 
			4 * Spacings.KeySignatures.sbksa + 
/* 			5 * STANDARD_ACCIDENTAL_SIZE + */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_C_FLAT:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x,
			    staff->extremity_begin_y + 5);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y - 9);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 2 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y + 9);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 3 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y - 4);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 4 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y + 14);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 5 * Spacings.KeySignatures.sbksa),
			    staff->extremity_begin_y);
		
		timesignature_x = 
			keysignature_x + 
			5 * Spacings.KeySignatures.sbksa + 
/* 			6 * STANDARD_ACCIDENTAL_SIZE +  */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_D_SHARP:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x,
			    staff->extremity_begin_y - 10);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y + 4);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 2 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y - 13);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 3 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y - 1);
		
		timesignature_x = 
			keysignature_x + 
			3 * Spacings.KeySignatures.sbksa + 
/* 			4 * STANDARD_ACCIDENTAL_SIZE + */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_D_FLAT:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x,
			    staff->extremity_begin_y + 5);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y - 9);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 2 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y + 9);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 3 * Spacings.KeySignatures.sbksa),
			    staff->extremity_begin_y - 4);

		timesignature_x = 
			keysignature_x + 
			3 * Spacings.KeySignatures.sbksa + 
/* 			4 * STANDARD_ACCIDENTAL_SIZE +  */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_E_SHARP:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x,
			    staff->extremity_begin_y - 10);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y + 4);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 2 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y - 13);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 3 * Spacings.KeySignatures.sbksa),
			    staff->extremity_begin_y - 1);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 4 * Spacings.KeySignatures.sbksa),
			    staff->extremity_begin_y + 13);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 5 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y - 5);
		
		timesignature_x = 
			keysignature_x + 
			5 * Spacings.KeySignatures.sbksa + 
/* 			6 * STANDARD_ACCIDENTAL_SIZE + */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_E_FLAT:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x,
			    staff->extremity_begin_y + 5);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y - 9);
		
		timesignature_x = 
			keysignature_x + 
			Spacings.KeySignatures.sbksa +
/* 			2 * STANDARD_ACCIDENTAL_SIZE +  */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_F_SHARP:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x,
			    staff->extremity_begin_y - 10);

		timesignature_x = 
			keysignature_x +
/* 			STANDARD_ACCIDENTAL_SIZE + */
			Spacings.KeySignatures.saks;
		
		break;
	case KEY_SIGNATURE_TREBLE_F_FLAT:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x,
			    staff->extremity_begin_y + 5);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y - 9);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 2 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y + 9);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 3 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y - 4);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 4 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y + 14);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 5 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 6 * Spacings.KeySignatures.sbksa),
			    staff->extremity_begin_y + 18);
		
		timesignature_x = 
			keysignature_x + 
			6 * Spacings.KeySignatures.sbksa +
/* 			7 * STANDARD_ACCIDENTAL_SIZE + */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_G_SHARP:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x,
			    staff->extremity_begin_y - 10);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y + 4);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_SHARP,
			    keysignature_x + ( 2 * Spacings.KeySignatures.sbksa),
			    staff->extremity_begin_y - 13);
		
		timesignature_x = 
			keysignature_x + 
			2 * Spacings.KeySignatures.sbksa +
/* 			3 * STANDARD_ACCIDENTAL_SIZE + */
			Spacings.KeySignatures.saks;

		break;
	case KEY_SIGNATURE_TREBLE_G_FLAT:
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x,
			    staff->extremity_begin_y + 5);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + Spacings.KeySignatures.sbksa,
			    staff->extremity_begin_y - 9);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 2 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y + 9);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 3 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y - 4);
		draw_pixmap(Score.area->window,
			    ACCIDENTAL_FLAT,
			    keysignature_x + ( 4 * Spacings.KeySignatures.sbksa ),
			    staff->extremity_begin_y + 14);
		
		timesignature_x = 
			keysignature_x + 
			4 * Spacings.KeySignatures.sbksa +
/* 			5 * STANDARD_ACCIDENTAL_SIZE + */
			Spacings.KeySignatures.saks;

		break;

	}

	/* I do *NOT* like that: what will happen if you decide not to see the keysignature ?!!! */
	staff_set_start_x(get_staff_selected(),
			  timesignature_x);

	return 0;
}

static gdouble 
realize_timesignature(Staff_t *staff)
{

	switch (staff->time_signature[0])
		{
		case TIME_SIGNATURE_COMMON_TIME:
			draw_pixmap(Score.area->window, TIME_SIG_CT,
				    timesignature_x,
				    staff->extremity_begin_y + 9);


			break;
		case TIME_SIGNATURE_ALLA_BREVE:
			draw_pixmap(Score.area->window, TIME_SIG_AB,
				    timesignature_x,
				    staff->extremity_begin_y + 6);

			break;
		default:
			break;
		}

	return 0;
}

static gboolean
realize_object(Staff_t *staff, Object_t *object, gboolean display_barlines, gboolean display_measure_number)
{

        Object_t *object_next;
/* 	Object_t *object_previous; */
	gint y = 0;
	gint ynext = 0;
	gdouble extremity_end_y = 0;
	gboolean is_selected = FALSE;

	gint average = 0;

	is_selected = object->is_selected;
	y = get_y_from_position(staff->key, staff->extremity_begin_y, object->pitch);


	object_next = object_get_next(object);
	if (object_next) {
		ynext = get_y_from_position(staff->key, staff->extremity_begin_y, object_next->pitch);
	}

/* 	object_previous = object_get_previous(object); */
/* 	if (object_previous) { */
/* 	} */

	extremity_end_y =  staff->extremity_begin_y +(staff->nb_lines - 1) * staff->space_btw_lines + staff->nb_lines - 1;
	average = (extremity_end_y - staff->extremity_begin_y) / 2;

	if (object->group_id != 0) {	/* it means it's a chord */
		if (object_get_previous(object)->group_id == object->group_id)
			printf("We are having a chord!\n");
	}


	switch(object->type) {

		/* NOTES */
	case DOUBLEWHOLE:
		debug_msg("DOUBLEWHOLE REALIZE CALLBACK\n");

		draw_staff_extension(staff, object->pitch, staff->start_x + object_x);

		if ( object->accidentals & A_SHARP )
			draw_note(SHARP_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0, 0, 0, 0);

		if (object->accidentals & A_FLAT)
			draw_note(FLAT_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 10, 0,0, 0,0);
		
		if (object->accidentals & A_NATURAL)
			draw_note(NATURAL_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0,0, 0,0);

		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 12, y);

		draw_note(DOUBLEWHOLE_HEAD,
			  is_selected,
			  staff->start_x + object_x,
			  y,
			  0,0,
			  0,0);

		object_x += Spacings.NotesRests.sa_doublewhole;

		break;
	case WHOLE:
		debug_msg("WHOLE REALIZE CALLBACK\n");

		draw_staff_extension(staff, object->pitch, staff->start_x + object_x);

		if ( object->accidentals & A_SHARP )
			draw_note(SHARP_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0, 0, 0, 0);

		if (object->accidentals & A_FLAT)
			draw_note(FLAT_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 10, 0,0, 0,0);
		
		if (object->accidentals & A_NATURAL)
			draw_note(NATURAL_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0,0, 0,0);

		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 12, y);

		draw_note(WHOLE_HEAD,
			  is_selected,
			  staff->start_x + object_x,
			  y,
			  0,0,
			  0,0);

		object_x += Spacings.NotesRests.sa_whole;

		break;
	case HALF:
		debug_msg("HALF REALIZE CALLBACK\n");

		draw_staff_extension(staff, object->pitch, staff->start_x + object_x);

		if ( object->accidentals & A_SHARP )
			draw_note(SHARP_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0, 0, 0, 0);

		if (object->accidentals & A_FLAT)
			draw_note(FLAT_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 10, 0,0, 0,0);
		
		if (object->accidentals & A_NATURAL)
			draw_note(NATURAL_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0,0, 0,0);

		/* 12 means the width of a half note. It's not really nice (* FIXME *) */
		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 12, y);


		if ( y < staff->extremity_begin_y + average ) {
			/* The note has the stem down */
			if ( object->nature & O_STACCATO )
				draw_point(staff->start_x + object_x + 4, y - 8);

			if ( object->nature & O_TENUTO )
				draw_line(0,0,0, staff->start_x + object_x, y - 8, staff->start_x + object_x + 8, y -8);

			draw_note(HALF_HEAD,
				  is_selected,
				  staff->start_x + object_x,
				  y,
				  staff->start_x + object_x,
				  y + 25,
				  staff->start_x + object_x,
				  y + 3);
		} else {
			/* The note has the stem up */
			if ( object->nature & O_STACCATO )
				draw_point(staff->start_x + object_x + 3, y + 13);

			if ( object->nature & O_TENUTO )
				draw_line(0,0,0, staff->start_x + object_x, y + 13, staff->start_x + object_x + 8, y + 13);

			draw_note(HALF_HEAD,
				  is_selected,
				  staff->start_x + object_x,
				  y,
				  staff->start_x + object_x + 9,
				  y,
				  staff->start_x + object_x + 9,
				  y - 21);
		}


		object_x += Spacings.NotesRests.sa_half;

		break;
	case QUARTER:
		debug_msg("QUARTER REALIZE CALLBACK\n");

                printf("RA: s + ox = %d\n", staff->start_x + object_x);
                printf("start_x = %d\n", staff->start_x);

		draw_staff_extension(staff, object->pitch, staff->start_x + object_x);

		if ( object->accidentals & A_SHARP )
			draw_note(SHARP_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0, 0, 0, 0);

		if (object->accidentals & A_FLAT)
			draw_note(FLAT_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 10, 0,0, 0,0);
		
		if (object->accidentals & A_NATURAL)
			draw_note(NATURAL_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0,0, 0,0);

/* 		if ( object->nature & O_TIE_START ) { */
/* 			tie_draw_tie(staff, object, object_x, y, ynext); */
/* 		} */

		/* 8 means the width of a quarter note. It's not really nice (* FIXME *) */
		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 8 + Spacings.AugmentationDots.sbdan, y);
		
		if ( y < staff->extremity_begin_y + average ) {
			/* The note has the stem down */
			if ( object->nature & O_STACCATO )
				draw_point(staff->start_x + object_x + 4, y - 8);

			if ( object->nature & O_TENUTO )
				draw_line(0,0,0, staff->start_x + object_x, y - 8, staff->start_x + object_x + 8, y -8);


			draw_note(QUARTER_HEAD,
				  is_selected,
				  staff->start_x + object_x,
				  y,
				  staff->start_x + object_x,
				  y + 25,
				  staff->start_x + object_x,
				  y + 3);
		} else {
			/* The note has the stem up */
			if ( object->nature & O_STACCATO )
				draw_point(staff->start_x + object_x + 3, y + 13);

			if ( object->nature & O_TENUTO )
				draw_line(0,0,0, staff->start_x + object_x, y + 13, staff->start_x + object_x + 8, y + 13);

			draw_note(QUARTER_HEAD,
				  is_selected,
				  staff->start_x + object_x,
				  y,
				  staff->start_x + object_x + 8,
				  y,
				  staff->start_x + object_x + 8,
				  y - 21);
		}


		object_x += Spacings.NotesRests.sa_quarter;

		break;
	case EIGHTH:
		debug_msg("EIGHTH REALIZE CALLBACK\n");

		draw_staff_extension(staff, object->pitch, staff->start_x + object_x);

		if ( object->accidentals & A_SHARP )
			draw_note(SHARP_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0, 0, 0, 0);

		if (object->accidentals & A_FLAT)
			draw_note(FLAT_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 10, 0,0, 0,0);
		
		if (object->accidentals & A_NATURAL)
			draw_note(NATURAL_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0,0, 0,0);

		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 12, y);


		if ( object->nature & O_BEAMED ) {
			if ( object->nature & O_LAST_BEAMED ) {
				if ( y < staff->extremity_begin_y + average ) {
					if ( object->nature & O_STACCATO )
						draw_point(staff->start_x + object_x + 4, y - 8);
				
					if ( object->nature & O_TENUTO )
						draw_line(0,0,0, staff->start_x + object_x, y - 8, staff->start_x + object_x + 8, y -8);

					draw_note(QUARTER_HEAD,
						  is_selected,
						  staff->start_x + object_x,
						  y,
						  staff->start_x + object_x,
						  y + 25,
						  staff->start_x + object_x,
						  y + 3);
				} else {
					if ( object->nature & O_STACCATO )
						draw_point(staff->start_x + object_x + 3, y + 13);
				
					if ( object->nature & O_TENUTO )
						draw_line(0,0,0, staff->start_x + object_x, y + 13, staff->start_x + object_x + 8, y + 13);

					draw_note(QUARTER_HEAD,
						  is_selected,
						  staff->start_x + object_x,
						  y,
						  staff->start_x + object_x + 8,
						  y,
						  staff->start_x + object_x + 8,
						  y - 21);
				}
			} else {
				if ( y < staff->extremity_begin_y + average ) {
					if ( object->nature & O_STACCATO )
						draw_point(staff->start_x + object_x + 4, y - 8);
				
					if ( object->nature & O_TENUTO )
						draw_line(0,0,0, staff->start_x + object_x, y - 8, staff->start_x + object_x + 8, y -8);

					draw_note(QUARTER_HEAD,
						  is_selected,
						  staff->start_x + object_x,
						  y,
						  staff->start_x + object_x,
						  y + 25,
						  staff->start_x + object_x,
						  y + 3);

					beam_draw_beam(staff, object, object_x - 8, y + 25, ynext + 25);
				} else {
					if ( object->nature & O_STACCATO )
						draw_point(staff->start_x + object_x + 3, y + 13);
				
					if ( object->nature & O_TENUTO )
						draw_line(0,0,0, staff->start_x + object_x, y + 13, staff->start_x + object_x + 8, y + 13);

					draw_note(QUARTER_HEAD,
						  is_selected,
						  staff->start_x + object_x,
						  y,
						  staff->start_x + object_x + 8,
						  y,
						  staff->start_x + object_x + 8,
						  y - 21);
					
					beam_draw_beam(staff, object, object_x, y - 21, ynext - 21);
				}
			}
		} else {

			if ( y < staff->extremity_begin_y + average ) {
				/* The note has the stem down */
				if ( object->nature & O_STACCATO )
					draw_point(staff->start_x + object_x + 4, y - 8);
				
				if ( object->nature & O_TENUTO )
					draw_line(0,0,0, staff->start_x + object_x, y - 8, staff->start_x + object_x + 8, y -8);
				
				draw_eighth_down(is_selected, staff->start_x + object_x, y - 21);
			} else {
				/* The note has the stem up */
				if ( object->nature & O_STACCATO )
					draw_point(staff->start_x + object_x + 3, y + 13);
				
				if ( object->nature & O_TENUTO )
					draw_line(0,0,0, staff->start_x + object_x, y + 13, staff->start_x + object_x + 8, y + 13);

				draw_eighth_up(is_selected, staff->start_x + object_x, y - 21);
			}

		}

		object_x += Spacings.NotesRests.sa_eighth;

		break;
	case SIXTEENTH:
		debug_msg("SIXTEENTH REALIZE CALLBACK\n");

		draw_staff_extension(staff, object->pitch, staff->start_x + object_x);

		if ( object->accidentals & A_SHARP )
			draw_note(SHARP_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0, 0, 0, 0);

		if (object->accidentals & A_FLAT)
			draw_note(FLAT_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 10, 0,0, 0,0);
		
		if (object->accidentals & A_NATURAL)
			draw_note(NATURAL_ACCIDENTAL, FALSE,
				  staff->start_x + object_x - 10,
				  y - 6, 0,0, 0,0);

		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 12, y);


		if ( object->nature & O_BEAMED ) {
			if ( object->nature & O_LAST_BEAMED ) {
				if ( y < staff->extremity_begin_y + average ) {
					if ( object->nature & O_STACCATO )
						draw_point(staff->start_x + object_x + 4, y - 8);
				
					if ( object->nature & O_TENUTO )
						draw_line(0,0,0, staff->start_x + object_x, y - 8, staff->start_x + object_x + 8, y -8);

					draw_note(QUARTER_HEAD,
						  is_selected,
						  staff->start_x + object_x,
						  y,
						  staff->start_x + object_x,
						  y + 25,
						  staff->start_x + object_x,
						  y + 3);
				} else {
					if ( object->nature & O_STACCATO )
						draw_point(staff->start_x + object_x + 3, y + 13);

					if ( object->nature & O_TENUTO )
						draw_line(0,0,0, staff->start_x + object_x, y + 13, staff->start_x + object_x + 8, y + 13);

					draw_note(QUARTER_HEAD,
						  is_selected,
						  staff->start_x + object_x,
						  y,
						  staff->start_x + object_x + 8,
						  y,
						  staff->start_x + object_x + 8,
						  y - 21);
				}
			} else {
				if ( y < staff->extremity_begin_y + average ) {
					if ( object->nature & O_STACCATO )
						draw_point(staff->start_x + object_x + 4, y - 8);
				
					if ( object->nature & O_TENUTO )
						draw_line(0,0,0, staff->start_x + object_x, y - 8, staff->start_x + object_x + 8, y -8);

					draw_note(QUARTER_HEAD,
						  is_selected,
						  staff->start_x + object_x,
						  y,
						  staff->start_x + object_x,
						  y + 25,
						  staff->start_x + object_x,
						  y + 3);

					beam_draw_beam(staff, object, object_x - 8, y + 46, ynext + 46);

				} else {
					if ( object->nature & O_STACCATO )
						draw_point(staff->start_x + object_x + 3, y + 13);

					if ( object->nature & O_TENUTO )
						draw_line(0,0,0, staff->start_x + object_x, y + 13, staff->start_x + object_x + 8, y + 13);

					draw_note(QUARTER_HEAD,
						  is_selected,
						  staff->start_x + object_x,
						  y,
						  staff->start_x + object_x + 8,
						  y,
						  staff->start_x + object_x + 8,
						  y - 21);

					beam_draw_beam(staff, object, object_x, y, ynext);
				}
				
			}
		} else {

			if ( y < staff->extremity_begin_y + average ) {
				/* The note has the stem down */
				if ( object->nature & O_STACCATO )
					draw_point(staff->start_x + object_x + 4, y - 8);
				
				if ( object->nature & O_TENUTO )
					draw_line(0,0,0, staff->start_x + object_x, y - 8, staff->start_x + object_x + 8, y -8);

				draw_sixteenth_down(is_selected, staff->start_x + object_x, y - 21);
			} else {
				/* The note has the stem up */
				if ( object->nature & O_STACCATO )
					draw_point(staff->start_x + object_x + 3, y + 13);

				if ( object->nature & O_TENUTO )
					draw_line(0,0,0, staff->start_x + object_x, y + 13, staff->start_x + object_x + 8, y + 13);

				draw_sixteenth_up(is_selected, staff->start_x + object_x, y - 21);
			}

		}

		object_x += Spacings.NotesRests.sa_sixteenth;

		break;

		/* RESTS */
	case DOUBLEWHOLEREST:
		debug_msg("DOUBLEWHOLEREST REALIZE CALLBACK\n");

		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 12, y);

		draw_pixmap(Score.area->window, DOUBLEWHOLE_REST,
			    staff->start_x + object_x, y); 

		object_x += Spacings.NotesRests.sa_doublewholerest;
		
		break;
	case WHOLEREST:
		debug_msg("WHOLEREST REALIZE CALLBACK\n");

		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 12, y);

		draw_pixmap(Score.area->window, WHOLE_REST,
			    staff->start_x + object_x, y); 

		object_x += Spacings.NotesRests.sa_wholerest;

		break;
	case HALFREST:
		debug_msg("HALFREST REALIZE CALLBACK\n");

		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 12, y);

		draw_pixmap(Score.area->window, HALF_REST,
			    staff->start_x + object_x, y); 

		object_x += Spacings.NotesRests.sa_halfrest;

		break;
	case QUARTERREST:
		debug_msg("QUARTERREST REALIZE CALLBACK\n");

		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 12, y);

		draw_pixmap(Score.area->window, QUARTER_REST,
			    staff->start_x + object_x, staff->extremity_begin_y + 8); 

		object_x += Spacings.NotesRests.sa_quarterrest;

		break;
	case EIGHTHREST:
		debug_msg("EIGHTHREST REALIZE CALLBACK\n");

		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 12, y);

		draw_pixmap(Score.area->window, EIGHTH_REST,
			    staff->start_x + object_x, y); 

		object_x += Spacings.NotesRests.sa_eighthrest;

		break;
	case SIXTEENTHREST:
		debug_msg("SIXTEENTHREST REALIZE CALLBACK\n");

		if ( object->nature & O_DURATION )
			draw_point(staff->start_x + object_x + 12, y);

		draw_pixmap(Score.area->window, SIXTEENTH_REST,
			    staff->start_x + object_x, y); 

		object_x += Spacings.NotesRests.sa_sixteenthrest;

		break;

		/* BARLINES */
	case BARLINE_SINGLE:
		debug_msg("BARLINE_SINGLE REALIZE CALLBACK\n");

		measure_number++;

		if (display_barlines) {
			draw_barline_single(staff, staff->start_x + object_x);

			if (display_measure_number) {
				set_text(g_strdup_printf("%d", measure_number), 
					 staff->start_x + object_x,
					 staff->extremity_begin_y - 17);
			}
		}
		object_x += Spacings.Barlines.sab;

		break;
	case BARLINE_DOUBLE:
		debug_msg("BARLINE_DOUBLE REALIZE CALLBACK\n");

		measure_number++;

		if (display_barlines) {
			draw_barline_double(staff, staff->start_x + object_x);

			if (display_measure_number) {
				set_text(g_strdup_printf("%d", measure_number), 
					 staff->start_x + object_x,
					 staff->extremity_begin_y - 17);
			}
		}
		object_x += Spacings.Barlines.sab;

		break;
	case BARLINE_OPENREPEAT:
		debug_msg("BARLINE_OPENREPEAT REALIZE CALLBACK\n");

		measure_number++;

		if (display_barlines) {
			draw_barline_openrepeat(staff, staff->start_x + object_x);

			if (display_measure_number) {
				set_text(g_strdup_printf("%d", measure_number), 
					 staff->start_x + object_x,
					 staff->extremity_begin_y - 17);
			}
		}
		object_x += Spacings.Barlines.sab;

		break;
	case BARLINE_CLOSEREPEAT:
		debug_msg("BARLINE_CLOSEREPEAT REALIZE CALLBACK\n");

		measure_number++;

		if (display_barlines) {
			draw_barline_closerepeat(staff, staff->start_x + object_x);

			if (display_measure_number) {
				set_text(g_strdup_printf("%d", measure_number), 
					 staff->start_x + object_x,
					 staff->extremity_begin_y - 17);
			}
		}

		object_x += Spacings.Barlines.sab;

		break;
	case BARLINE_OPENCLOSEREPEAT:
		debug_msg("BARLINE_OPENCLOSEREPEAT REALIZE CALLBACK\n");

		measure_number++;

		if (display_barlines) {
			draw_barline_opencloserepeat(staff, staff->start_x + object_x);

			if (display_measure_number) {
				set_text(g_strdup_printf("%d", measure_number), 
					 staff->start_x + object_x,
					 staff->extremity_begin_y - 17);
			}
		}
		object_x += Spacings.Barlines.sab;

		break;

		/* DYNAMICS */
	case DYNAMIC_PPPP:
		set_dynamic_text("pppp", object->x, extremity_end_y + 10);
		break;
	case DYNAMIC_PPP:
		set_dynamic_text("ppp", object->x, extremity_end_y + 10);
		break;
	case DYNAMIC_PP:
		set_dynamic_text("pp", object->x, extremity_end_y + 10);
		break;
	case DYNAMIC_P:
		set_dynamic_text("p", object->x, extremity_end_y + 10);
		break;
	case DYNAMIC_MP:
		set_dynamic_text("mp", object->x, extremity_end_y + 10);
		break;
	case DYNAMIC_MF:
		set_dynamic_text("mf", object->x, extremity_end_y + 10);
		break;
	case DYNAMIC_F:
		set_dynamic_text("f", object->x, extremity_end_y + 10);
		break;
	case DYNAMIC_FF:
		set_dynamic_text("ff", object->x, extremity_end_y + 10);
		break;
	case DYNAMIC_FFF:
		set_dynamic_text("fff", object->x, extremity_end_y + 10);
		break;

		/* CHANGE KEY */
	case TREBLE_KEY:
		draw_pixmap(Score.area->window, CLEF_G,
			    staff->start_x + object_x,
			    staff->extremity_begin_y - 8);

		object_x += STANDARD_KEY_SIZE + Spacings.Clefs.sa;

		break;
	case BASS_KEY:
		draw_pixmap(Score.area->window, CLEF_F,
			    staff->start_x + object_x,
			    staff->extremity_begin_y + 1);

		object_x += STANDARD_KEY_SIZE + Spacings.Clefs.sa;

		break;
	case ALTO_KEY:
		draw_pixmap(Score.area->window, CLEF_C,
			    staff->start_x + object_x,
			    staff->extremity_begin_y + 5);

		object_x += STANDARD_KEY_SIZE + Spacings.Clefs.sa;

		break;
	case TAB_KEY:
		draw_pixmap(Score.area->window, CLEF_TAB,
			    staff->start_x + object_x,
			    staff->extremity_begin_y + 7);

		object_x += STANDARD_KEY_SIZE + Spacings.Clefs.sa;

		break;
		
	}

	return FALSE;

}

gboolean score_area_callback(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{

	GList *listrunner_staff;
	GList *listrunner_object;


	draw_page_limit(Score.staff_extremity_end_x);

	staff_update_statusbar();


	/* BEGIN: Display the Tempo */
	if (Score.Display->tempo) {
		draw_pixmap(Score.area->window, "pixmaps/tb_quarter.xpm",
			    get_staff_extremity_begin_x(0) + Spacings.Tempo.xpfm,
			    get_staff_extremity_begin_y(0) - Spacings.Tempo.ypfm);

		if (g_str_equal(Score.tempo_text->str,""))
			set_text(g_strdup_printf("= %d", Score.tempo),
				 get_staff_extremity_begin_x(0) + Spacings.Tempo.xpfm + 20,
				 get_staff_extremity_begin_y(0) - Spacings.Tempo.ypfm + 5);
		else
			set_text(g_strdup_printf("= %d (%s)", Score.tempo, Score.tempo_text->str),
				 get_staff_extremity_begin_x(0) + Spacings.Tempo.xpfm + 20,
				 get_staff_extremity_begin_y(0) - Spacings.Tempo.ypfm + 5);
	}
	/* END: Display the Tempo */


	/* BEGIN: Walk through staves */
	listrunner_staff = g_list_first(Score.Staff_list);
	while ( listrunner_staff ) {
		/* That value is used to reinit the x position of the elements: very important */
		object_x = 0;
		measure_number = 1;

		Staff_t *staff;
		staff = (Staff_t *)listrunner_staff->data;

		/* BEGIN: Draw the staff */
		draw_staff(staff->nb_lines, staff->space_btw_lines,
			   staff->extremity_begin_x, staff->extremity_begin_y,
			   Score.staff_extremity_end_x, TRUE, staff->is_selected);
		/* END: Draw the staff */

		draw_staff_extension(staff, get_key_cursor_position(), staff->current_x);

		/* BEGIN: Draw the key cursor */
		if ( staff->is_selected )
			draw_key_cursor(get_key_cursor_position(), staff->current_x, staff->extremity_begin_y);
		/* END: Draw the key cursor */

		/* BEGIN: Draw the key */
		if ( Score.Display->clefs )
			realize_key(staff);
		/* END: Draw the key */

		/* BEGIN: Draw the ending bar */
/* 		if ( Score.Display->ending_bar ) */
/* 			draw_barline_endstaff(get_staff_selected()); */
		/* END: Draw the ending bar */

		if ( Score.Display->key_signature )
			realize_key_signature(staff);

		/* Time Signature of the staff */
		if ( Score.Display->time_signature )
			realize_timesignature(staff);

		/* Parsing Objects structure */
		listrunner_object = g_list_first(staff->Object_list);
		while ( listrunner_object ) {
			Object_t *object;
			object = (Object_t *)listrunner_object->data;

/* 			draw_staff(2, 5, 5, 5, 40, TRUE, FALSE); */
/* 			tie_draw_tie(staff, object, 20, 20, 20); */

			if (object)
				realize_object(staff, object, Score.Display->barlines, Score.Display->measure_number);

			listrunner_object = g_list_next(listrunner_object);
		}
		
		listrunner_staff = g_list_next(listrunner_staff);
	} /* while ( listrunner_staff ) */

        /* END: Walk through staves */


        return FALSE;
}



void popup_action(GtkWidget *widget, GdkEventButton *event)
{

/* 	gint staff; */

/* 	GtkWidget *menu, *menu_item; */


/* 	menu = gtk_menu_new(); */
/* 	menu_item = gtk_menu_item_new_with_label(_("Delete")); */
/* /\* 	g_signal_connect(G_OBJECT(menu_item), "activate", *\/ */
/* /\* 			 G_CALLBACK(delete_unit), note); *\/ */
/* 	gtk_menu_append(GTK_MENU(menu), menu_item); */
/* 	gtk_widget_show(menu_item); */
	
/* 	for (staff = 0; staff < Score.nb_staff; staff++) */
/* 	{ */
/* 		listrunner_note = g_list_first(Score.Staff[staff].Note_list); */
		
/* 		while (listrunner_note) */
/* 		{ */
/* 			Note_t *note; */
/* 			note = (Note_t *)listrunner_note->data; */


/* 			switch (note->type) */
/* 			{ */
/* 			case QUARTER: */
/* 				menu_item = gtk_menu_item_new_with_label(_("Properties...")); */
/* /\* 				g_signal_connect_swapped(G_OBJECT(menu_item), "activate", *\/ */
/* /\* 							 G_CALLBACK(show_ressource_setting_dialog), *\/ */
/* /\* 							 pud_unit); *\/ */
/* 				gtk_menu_append(GTK_MENU(menu), menu_item); */
/* 				gtk_widget_show(menu_item); */
				
/* 				break; */
/* 			} */
/* 			gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, ev->button, ev->time); */


/* 			listrunner_object = g_list_next(listrunner_object); */

/* 		} */
/* 	} */
}
