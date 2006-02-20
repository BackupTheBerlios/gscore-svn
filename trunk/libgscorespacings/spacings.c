/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorespacings/spacings.c
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
#include <libgscore/gscoreerrors.h>
#include <libgscore/constants.h>

#include <libgscorebase/score.h>
#include <libgscorebase/staff.h>

#include "spacings.h"

extern gdouble
spacings_key_signature_get(Score *score, Staff *staff)
{
        gdouble retval = 0;


        switch(staff->key_signature)
                {
                case KEY_SIGNATURE_EMPTY:
                case KEY_SIGNATURE_TREBLE_EMPTY:
                case KEY_SIGNATURE_BASS_EMPTY:
                        retval = 0;
                        break;
                case KEY_SIGNATURE_TREBLE_A_SHARP:
                case KEY_SIGNATURE_BASS_A_SHARP:
                        retval = 5 * Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_B_SHARP:
                case KEY_SIGNATURE_BASS_B_SHARP:
                        retval = 7 * Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_C_SHARP:
                case KEY_SIGNATURE_BASS_C_SHARP:
                        retval = 2 * Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_D_SHARP:
                case KEY_SIGNATURE_BASS_D_SHARP:
                        retval = 4 * Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_E_SHARP:
                case KEY_SIGNATURE_BASS_E_SHARP:
                        retval = 6 * Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_F_SHARP:
                case KEY_SIGNATURE_BASS_F_SHARP:
                        retval = Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_G_SHARP:
                case KEY_SIGNATURE_BASS_G_SHARP:
                        retval = 3 * Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_A_FLAT:
                case KEY_SIGNATURE_BASS_A_FLAT:
                        retval = 3 * Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_B_FLAT:
                case KEY_SIGNATURE_BASS_B_FLAT:
                        retval = Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_C_FLAT:
                case KEY_SIGNATURE_BASS_C_FLAT:
                        retval = 6 * Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_D_FLAT:
                case KEY_SIGNATURE_BASS_D_FLAT:
                        retval = 4 * Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_E_FLAT:
                case KEY_SIGNATURE_BASS_E_FLAT:
                        retval = 2 * Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_F_FLAT:
                case KEY_SIGNATURE_BASS_F_FLAT:
                        retval = 7 * Spacings.KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_G_FLAT:
                case KEY_SIGNATURE_BASS_G_FLAT:
                        retval = 5 * Spacings.KeySignatures.sbksa;
                        break;
                default:
                        g_critical("Cannot guess the spacing of the key signature!");
                }

        return retval;
}

extern 
void spacings_init(void)
{
	/* The values are set in pixels, then converted in inches/cm/whatever if requested */
        /* Full description in include/spacings.h */

	/* Augmentation Dots */
	Spacings.AugmentationDots.sbdan = 4;
	Spacings.AugmentationDots.sbd = 1;
	Spacings.AugmentationDots.vaod = 1;

	/* Barlines */
	Spacings.Barlines.hlt     = 4;
	Spacings.Barlines.tlt     = 1;
	Spacings.Barlines.sbhatl  = 3;
	Spacings.Barlines.swdb    = 3;
	Spacings.Barlines.sblad   = 4;
	Spacings.Barlines.sbd     = 3;
	Spacings.Barlines.sab     = 35;

	/* Beams */
	Spacings.Beams.bt = 3;

	/* Clefs */
	Spacings.Clefs.sb = 5;
	Spacings.Clefs.sa = 10;

	/* Key Signatures */
	Spacings.KeySignatures.sbksa = 10;
	Spacings.KeySignatures.saks = 20;

        /* Measures */
        Spacings.Measures.xpsfm = 35;
        Spacings.Measures.ypsfm = 70;
        Spacings.Measures.slbm = 50;

	/* Notes and Rests */
	Spacings.NotesRests.sa_doublewhole      = 100;
	Spacings.NotesRests.sa_doublewholerest  = 100;
	Spacings.NotesRests.sa_whole            = 80;
	Spacings.NotesRests.sa_wholerest        = 80;
	Spacings.NotesRests.sa_half             = 50;
	Spacings.NotesRests.sa_halfrest         = 50;
	Spacings.NotesRests.sa_quarter          = 35;
	Spacings.NotesRests.sa_quarterrest      = 35;
	Spacings.NotesRests.sa_eighth           = 25;
	Spacings.NotesRests.sa_eighthrest       = 25;
	Spacings.NotesRests.sa_sixteenth        = 25;
	Spacings.NotesRests.sa_sixteenthrest    = 25;
	Spacings.NotesRests.sa_thirtysecond     = 25;
	Spacings.NotesRests.sa_thirtysecondrest = 25;
	Spacings.NotesRests.sa_sixtyfourth      = 25;
	Spacings.NotesRests.sa_sixtyfourthrest  = 25;

        /* Tempo */
        Spacings.Tempo.xpfm = 5;
        Spacings.Tempo.ypfm = 40;

	/* Time Signatures */
        Spacings.TimeSignatures.width = 10;
	Spacings.TimeSignatures.sats = 15;
}
