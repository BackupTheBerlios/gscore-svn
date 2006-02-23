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

#include <libgscorespacings/spacings.h>

Spacings *spacings = NULL;


extern gdouble
spacings_key_signature_get(Score *score, Staff *staff)
{
        gdouble retval = 0;


        if ( ! spacings ) return 0;


        switch(staff->key_signature)
                {
                case KEY_SIGNATURE_EMPTY:
                case KEY_SIGNATURE_TREBLE_EMPTY:
                case KEY_SIGNATURE_BASS_EMPTY:
                        retval = 0;
                        break;
                case KEY_SIGNATURE_TREBLE_A_SHARP:
                case KEY_SIGNATURE_BASS_A_SHARP:
                        retval = 5 * spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_B_SHARP:
                case KEY_SIGNATURE_BASS_B_SHARP:
                        retval = 7 * spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_C_SHARP:
                case KEY_SIGNATURE_BASS_C_SHARP:
                        retval = 2 * spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_D_SHARP:
                case KEY_SIGNATURE_BASS_D_SHARP:
                        retval = 4 * spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_E_SHARP:
                case KEY_SIGNATURE_BASS_E_SHARP:
                        retval = 6 * spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_F_SHARP:
                case KEY_SIGNATURE_BASS_F_SHARP:
                        retval = spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_G_SHARP:
                case KEY_SIGNATURE_BASS_G_SHARP:
                        retval = 3 * spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_A_FLAT:
                case KEY_SIGNATURE_BASS_A_FLAT:
                        retval = 3 * spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_B_FLAT:
                case KEY_SIGNATURE_BASS_B_FLAT:
                        retval = spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_C_FLAT:
                case KEY_SIGNATURE_BASS_C_FLAT:
                        retval = 6 * spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_D_FLAT:
                case KEY_SIGNATURE_BASS_D_FLAT:
                        retval = 4 * spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_E_FLAT:
                case KEY_SIGNATURE_BASS_E_FLAT:
                        retval = 2 * spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_F_FLAT:
                case KEY_SIGNATURE_BASS_F_FLAT:
                        retval = 7 * spacings->KeySignatures.sbksa;
                        break;
                case KEY_SIGNATURE_TREBLE_G_FLAT:
                case KEY_SIGNATURE_BASS_G_FLAT:
                        retval = 5 * spacings->KeySignatures.sbksa;
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
	spacings->AugmentationDots.sbdan = 4;
	spacings->AugmentationDots.sbd = 1;
	spacings->AugmentationDots.vaod = 1;

	/* Barlines */
	spacings->Barlines.hlt     = 4;
	spacings->Barlines.tlt     = 1;
	spacings->Barlines.sbhatl  = 3;
	spacings->Barlines.swdb    = 3;
	spacings->Barlines.sblad   = 4;
	spacings->Barlines.sbd     = 3;
	spacings->Barlines.sab     = 35;

	/* Beams */
	spacings->Beams.bt = 3;

	/* Clefs */
	spacings->Clefs.sb = 5;
	spacings->Clefs.sa = 10;

	/* Key Signatures */
	spacings->KeySignatures.sbksa = 10;
	spacings->KeySignatures.saks = 20;

        /* Measures */
        spacings->Measures.xpsfm = 35;
        spacings->Measures.ypsfm = 70;
        spacings->Measures.slbm = 50;

	/* Notes and Rests */
	spacings->NotesRests.sa_doublewhole      = 100;
	spacings->NotesRests.sa_doublewholerest  = 100;
	spacings->NotesRests.sa_whole            = 80;
	spacings->NotesRests.sa_wholerest        = 80;
	spacings->NotesRests.sa_half             = 50;
	spacings->NotesRests.sa_halfrest         = 50;
	spacings->NotesRests.sa_quarter          = 35;
	spacings->NotesRests.sa_quarterrest      = 35;
	spacings->NotesRests.sa_eighth           = 25;
	spacings->NotesRests.sa_eighthrest       = 25;
	spacings->NotesRests.sa_sixteenth        = 25;
	spacings->NotesRests.sa_sixteenthrest    = 25;
	spacings->NotesRests.sa_thirtysecond     = 25;
	spacings->NotesRests.sa_thirtysecondrest = 25;
	spacings->NotesRests.sa_sixtyfourth      = 25;
	spacings->NotesRests.sa_sixtyfourthrest  = 25;

        /* Tempo */
        spacings->Tempo.xpfm = 5;
        spacings->Tempo.ypfm = 40;

	/* Time Signatures */
        spacings->TimeSignatures.width = 10;
	spacings->TimeSignatures.sats = 15;
}
