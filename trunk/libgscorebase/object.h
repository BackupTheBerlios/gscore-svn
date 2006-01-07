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

};

Object * gscore_object_new_default(Score *score, Staff *staff, gint type);


/* Constants related to the object type */

#define OBJECT_NULL 0

/* CURSORS */
/* I changed CURSOR to MOUSE_CURSOR */
#define MOUSE_CURSOR 1 /* Mouse cursor */
#define PITCH_CURSOR 2

/* KEYS */
#define NO_KEY         10
#define TREBLE_KEY     11
#define ALTO_KEY       12
#define TENOR_KEY      13
#define BASS_KEY       14
#define PERCUSSION_KEY 15
#define TREBLE_8VB_KEY 16
#define BASS_8VB_KEY   17
#define BARITONE_KEY   18
#define TAB_KEY        19

/* NOTES */
#define DOUBLEWHOLE  100
#define WHOLE        101
#define HALF         102
#define QUARTER      103
#define EIGHTH       104
#define SIXTEENTH    105
#define THIRTYSECOND 106
#define SIXTYFOURTH  107

/* ACCIDENTALS  */
#define NATURAL     200
#define SHARP       201
#define FLAT        202
#define DOUBLEFLAT  203
#define DOUBLESHARP 204
#define COURTESY    205

/* RESTS */
#define DOUBLEWHOLEREST  300
#define WHOLEREST        301
#define HALFREST         302
#define QUARTERREST      303
#define EIGHTHREST       304
#define SIXTEENTHREST    305
#define THIRTYSECONDREST 306
#define SIXTYFOURTHREST  307

#define DECRESCENDO 400
#define CRESCENDO   401

/* BARLINES */
#define BARLINE                 500
#define BARLINE_SINGLE          501
#define BARLINE_DOUBLE          502
#define BARLINE_OPENREPEAT      503
#define BARLINE_CLOSEREPEAT     504
#define BARLINE_OPENCLOSEREPEAT 505
#define BARLINE_OPEN            506
#define BARLINE_CLOSE           507

/* TIME SIGNATURES */
#define TIME_SIGNATURE_NORMAL      600
#define TIME_SIGNATURE_COMMON_TIME 601
#define TIME_SIGNATURE_ALLA_BREVE  602

/* KEY SIGNATURES */
#define KEY_SIGNATURE_EMPTY          700

#define KEY_SIGNATURE_TREBLE_EMPTY   701
#define KEY_SIGNATURE_TREBLE_A_SHARP 702
#define KEY_SIGNATURE_TREBLE_B_SHARP 703
#define KEY_SIGNATURE_TREBLE_C_SHARP 704
#define KEY_SIGNATURE_TREBLE_D_SHARP 705
#define KEY_SIGNATURE_TREBLE_E_SHARP 706
#define KEY_SIGNATURE_TREBLE_F_SHARP 707
#define KEY_SIGNATURE_TREBLE_G_SHARP 708
#define KEY_SIGNATURE_TREBLE_A_FLAT  709
#define KEY_SIGNATURE_TREBLE_B_FLAT  710
#define KEY_SIGNATURE_TREBLE_C_FLAT  711
#define KEY_SIGNATURE_TREBLE_D_FLAT  712
#define KEY_SIGNATURE_TREBLE_E_FLAT  713
#define KEY_SIGNATURE_TREBLE_F_FLAT  714
#define KEY_SIGNATURE_TREBLE_G_FLAT  715

#define KEY_SIGNATURE_ALTO_EMPTY     716
#define KEY_SIGNATURE_ALTO_A_SHARP   717
#define KEY_SIGNATURE_ALTO_B_SHARP   718
#define KEY_SIGNATURE_ALTO_C_SHARP   719
#define KEY_SIGNATURE_ALTO_D_SHARP   720
#define KEY_SIGNATURE_ALTO_E_SHARP   721
#define KEY_SIGNATURE_ALTO_F_SHARP   722
#define KEY_SIGNATURE_ALTO_G_SHARP   723
#define KEY_SIGNATURE_ALTO_A_FLAT    724
#define KEY_SIGNATURE_ALTO_B_FLAT    725
#define KEY_SIGNATURE_ALTO_C_FLAT    726
#define KEY_SIGNATURE_ALTO_D_FLAT    727
#define KEY_SIGNATURE_ALTO_E_FLAT    728
#define KEY_SIGNATURE_ALTO_F_FLAT    729
#define KEY_SIGNATURE_ALTO_G_FLAT    730

#define KEY_SIGNATURE_TENOR_EMPTY    731
#define KEY_SIGNATURE_TENOR_A_SHARP  732
#define KEY_SIGNATURE_TENOR_B_SHARP  733
#define KEY_SIGNATURE_TENOR_C_SHARP  734
#define KEY_SIGNATURE_TENOR_D_SHARP  735
#define KEY_SIGNATURE_TENOR_E_SHARP  736
#define KEY_SIGNATURE_TENOR_F_SHARP  737
#define KEY_SIGNATURE_TENOR_G_SHARP  738
#define KEY_SIGNATURE_TENOR_A_FLAT   739
#define KEY_SIGNATURE_TENOR_B_FLAT   740
#define KEY_SIGNATURE_TENOR_C_FLAT   741
#define KEY_SIGNATURE_TENOR_D_FLAT   742
#define KEY_SIGNATURE_TENOR_E_FLAT   743
#define KEY_SIGNATURE_TENOR_F_FLAT   744
#define KEY_SIGNATURE_TENOR_G_FLAT   745

#define KEY_SIGNATURE_BASS_EMPTY     746
#define KEY_SIGNATURE_BASS_A_SHARP   747
#define KEY_SIGNATURE_BASS_B_SHARP   748
#define KEY_SIGNATURE_BASS_C_SHARP   749
#define KEY_SIGNATURE_BASS_D_SHARP   750
#define KEY_SIGNATURE_BASS_E_SHARP   751
#define KEY_SIGNATURE_BASS_F_SHARP   752
#define KEY_SIGNATURE_BASS_G_SHARP   753
#define KEY_SIGNATURE_BASS_A_FLAT    754
#define KEY_SIGNATURE_BASS_B_FLAT    755
#define KEY_SIGNATURE_BASS_C_FLAT    756
#define KEY_SIGNATURE_BASS_D_FLAT    757
#define KEY_SIGNATURE_BASS_E_FLAT    758
#define KEY_SIGNATURE_BASS_F_FLAT    759
#define KEY_SIGNATURE_BASS_G_FLAT    760

#define KEY_SIGNATURE_TREBLE_8VB_EMPTY   761
#define KEY_SIGNATURE_TREBLE_8VB_A_SHARP 762
#define KEY_SIGNATURE_TREBLE_8VB_B_SHARP 763
#define KEY_SIGNATURE_TREBLE_8VB_C_SHARP 764
#define KEY_SIGNATURE_TREBLE_8VB_D_SHARP 765
#define KEY_SIGNATURE_TREBLE_8VB_E_SHARP 766
#define KEY_SIGNATURE_TREBLE_8VB_F_SHARP 767
#define KEY_SIGNATURE_TREBLE_8VB_G_SHARP 768
#define KEY_SIGNATURE_TREBLE_8VB_A_FLAT  769
#define KEY_SIGNATURE_TREBLE_8VB_B_FLAT  770
#define KEY_SIGNATURE_TREBLE_8VB_C_FLAT  771
#define KEY_SIGNATURE_TREBLE_8VB_D_FLAT  772
#define KEY_SIGNATURE_TREBLE_8VB_E_FLAT  773
#define KEY_SIGNATURE_TREBLE_8VB_F_FLAT  774
#define KEY_SIGNATURE_TREBLE_8VB_G_FLAT  775

#define KEY_SIGNATURE_BASS_8VB_EMPTY     776
#define KEY_SIGNATURE_BASS_8VB_A_SHARP   777
#define KEY_SIGNATURE_BASS_8VB_B_SHARP   778
#define KEY_SIGNATURE_BASS_8VB_C_SHARP   779
#define KEY_SIGNATURE_BASS_8VB_D_SHARP   780
#define KEY_SIGNATURE_BASS_8VB_E_SHARP   781
#define KEY_SIGNATURE_BASS_8VB_F_SHARP   782
#define KEY_SIGNATURE_BASS_8VB_G_SHARP   783
#define KEY_SIGNATURE_BASS_8VB_A_FLAT    784
#define KEY_SIGNATURE_BASS_8VB_B_FLAT    785
#define KEY_SIGNATURE_BASS_8VB_C_FLAT    786
#define KEY_SIGNATURE_BASS_8VB_D_FLAT    787
#define KEY_SIGNATURE_BASS_8VB_E_FLAT    788
#define KEY_SIGNATURE_BASS_8VB_F_FLAT    789
#define KEY_SIGNATURE_BASS_8VB_G_FLAT    790

/* DYNAMICS */
#define DYNAMIC_PPPP 900
#define DYNAMIC_PPP  901
#define DYNAMIC_PP   902
#define DYNAMIC_P    903
#define DYNAMIC_MP   904
#define DYNAMIC_MF   905
#define DYNAMIC_F    906
#define DYNAMIC_FF   907
#define DYNAMIC_FFF  908

/* Clipboard */
/* When you select quarters and you want to change them into half, this is called */
#define ACTION_CHANGE_OBJECT 1000
#define ACTION_CHANGE_STAFF  1001	      /* Change Key Signature, etc. */
#define ACTION_ADD_OBJECT    1002         /* When you add an object */
#define ACTION_ADD_STAFF     1003          /* When you add a staff */
#define ACTION_DEL_OBJECT    1004
#define ACTION_DEL_STAFF     1005


/* MIDI */
#define MIDI_GRAND_PIANO 5000


/* SPECIAL */
#define NO_ACCIDENTAL -1


/* SPACINGS */
/* The user cannot change that so that all notes start at the same point in the staff */
/* Cleaner for the eyes, not for the code ;) but nobody cares about it and it works! */
#define STANDARD_KEY_SIZE 15    
#define STANDARD_TIME_SIGNATURE_SIZE 15
#define STANDARD_ACCIDENTAL_SIZE 8


G_END_DECLS

#endif /* __OBJECT_H__ */
