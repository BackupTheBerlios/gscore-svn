/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorebase/object.h
 * gscore - a musical score editor
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

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <libgscore/gscoretypes.h>

G_BEGIN_DECLS

typedef enum accidentals_e
{

	A_NONE        = 1 << 0,
	A_SHARP       = 1 << 1,
	A_DOUBLESHARP = 1 << 2,
	A_FLAT        = 1 << 3,
	A_DOUBLEFLAT  = 1 << 4,
	A_NATURAL     = 1 << 5,
	A_PARENTHESIS = 1 << 6,

} accidentals_e;

typedef enum object_e
{

	O_NONE            = 1 << 0,
	O_BEAMED          = 1 << 1,
        O_LAST_BEAMED     = 1 << 2,
	O_TIE_START       = 1 << 3, 
	O_TIE_STOP        = 1 << 4,
	O_AUTOSTEM        = 1 << 5,
	O_STEMUP          = 1 << 6,
	O_STEMDOWN        = 1 << 7,
	O_DURATION        = 1 << 8,
	O_STACCATO        = 1 << 9,
	O_GRACE           = 1 << 10,
	O_MARCATOUP       = 1 << 11,
	O_MARCATODOWN     = 1 << 12,
	O_ACCENT          = 1 << 13,
	O_STACCATISSIMO   = 1 << 14,
	O_TENUTO          = 1 << 15,


} object_e;

struct _Object
{
        /** Unique ID */
        gulong         id;      

        /** key_signature, note (quarter, rest, ...), tab */
        gint           type;
        /** Stem Up/Down, Staccato, Grace... ? */ 
        object_e       nature;  
	accidentals_e  accidentals;

	gulong         group_id; /* the id where the object is grouped (ie.: a chord) */

        gdouble           x;
        gdouble           y;
        gdouble           x2; /* we need supplementary coordinates for */
        gdouble           y2; /* crescendo etc..     */
        gdouble           x3; /* and this is used for slurs, tied notes */
        gdouble           y3; /* BTW: and YES, I don't like that! */

        gint           pitch;	/* You know, the pitch stands for a note, to know where it is accordingly to the key */

        gint           tab_number;

        /** Is the object selected ? if so, change its color */
        gboolean       is_selected;  

} _Object;


G_END_DECLS

#endif /* __OBJECT_H__ */
