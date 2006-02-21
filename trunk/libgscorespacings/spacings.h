/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorespacings/spacings.h
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

#ifndef __SPACINGS_H__
#define __SPACINGS_H__

/* Structure for spacing settings */

#include <glib.h>
#include <libgscore/gscoretypes.h>
#include <libgscore/gscoreerrors.h>

G_BEGIN_DECLS

struct _Accidentals
{

	gint sbaan; 		/* Space between accidental and note */
	gint sbaon; 		/* Space between accidentals on note */

} _Accidentals;

struct _AugmentationDots
{

	gint sbdan;		/* Space between dot and note */
	gint sbd;		/* Space between dots */
	gint vaod;		/* Vertical adjustment of dot */

} _AugmentationDots;

struct _Barlines
{

	gint hlt;		/* Heavy line thickness */
	gint tlt;		/* Thin line thickness */
	gint sbhatl;		/* Space between heavy and thin line */
	gint swdb;		/* Space within double barlines */
	gint sblad;		/* Space between line and dot */
	gint sbd;		/* Space between dots */
	gint sab;		/* Space after barline */

} _Barlines;

struct _Beams
{

	gint bt;		/* Beam thickness */

} _Beams;

struct _Clefs
{

	gint sb;		/* Space before */
	gint sa;		/* Space after */

} _Clefs;

struct _KeySignatures
{

	gint sbksa;		/* Space between key signature accidentals */
	gint saks;		/* Space after key signature */

} _KeySignatures;

struct _Measures
{

        gdouble xpsfm;             /* X position start for the first measure */
        gdouble ypsfm;             /* Y position start for the first measure */
        gint slbm;              /* Space left between measures */

} _Measures;

struct _NotesRests
{

	gint sa_doublewhole;	/* Space after doublewhole */
	gint sa_doublewholerest;
	gint sa_whole;
	gint sa_wholerest;
	gint sa_half;
	gint sa_halfrest;
	gint sa_quarter;
	gint sa_quarterrest;
	gint sa_eighth;
	gint sa_eighthrest;
	gint sa_sixteenth;
	gint sa_sixteenthrest;
	gint sa_thirtysecond;
	gint sa_thirtysecondrest;
	gint sa_sixtyfourth;
	gint sa_sixtyfourthrest;

} _NotesRests;

struct _Tempo
{

        gdouble xpfm;              /* X position from measure */
        gdouble ypfm;              /* Y position from measure */

} _Tempo;

struct _TimeSignatures
{

        gdouble width;
	gdouble sats;		/* Space after time signature */

} _TimeSignatures;

struct _Spacings
{

	struct _Accidentals      Accidentals;
	struct _AugmentationDots AugmentationDots;
	struct _Barlines         Barlines;
	struct _Beams            Beams;
	struct _Clefs            Clefs;
	struct _KeySignatures    KeySignatures;
        struct _Measures         Measures;
	struct _NotesRests       NotesRests;
        struct _Tempo            Tempo;
	struct _TimeSignatures   TimeSignatures;

} _Spacings;


void spacings_init(void);

G_END_DECLS

#endif /* __SPACINGS_H__ */
