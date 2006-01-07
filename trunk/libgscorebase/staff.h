/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorebase/staff.h
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

#ifndef __STAFF_H__
#define __STAFF_H__

#include <libgscore/gscoretypes.h>

G_BEGIN_DECLS

struct _Staff
{

        /** How many lines for the staff (usually 5) */
        guint8     nb_lines;    
        /** How far are the lines with each other */
        guint8     space_btw_lines; 

        /** TRUE if the staff is selected */
        gboolean   is_selected; 

        /** Current cursor pitch (this avoid parsing the objects list to know this) */
        gint8      cursor_pitch;

        /** The key for the staff */
        gint       key;        
        /** The key signature for the staff */ 
        gint       key_signature; 

        /** The time signature for the staff 
         * time_signature[0] = TIME_SIGNATURE_NORMAL | TIME_SIGNATURE_COMMON_TIME | TIME_SIGNATURE_ALLA_BREVE 
         * time_signature[1] = Number of beats 
         * time_signature[2] = Beat duration */
        guint     time_signature[2]; 

        /** The number of the measure on which we are working */
        gint       measure_number; 
        /** How many measures in total */
        gint       total_measures; 

        /** Useful positions */
        /** Position X where the staff begins */
        gdouble    extremity_begin_x;
        /** Position Y where the staff begins */ 
        gdouble    extremity_begin_y; 
        /** The current position */
	/** It is where the next object should be drawn */
        gdouble    current_x;   

        /** The Instrument for the staff (MIDI) */
        gint       midi_instrument; 

        GList    * objects;

};


Staff * gscore_staff_new(Score *score, guint8 nb_lines, guint8 space_btw_lines, gdouble extremity_begin_x, gdouble extremity_begin_y);
Staff * gscore_staff_new_default(Score *score, gdouble extremity_begin_x, gdouble extremity_begin_y);


G_END_DECLS

#endif /* __STAFF_H__ */
