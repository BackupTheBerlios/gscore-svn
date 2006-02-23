/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * score-window.c
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

#include <gtk/gtk.h>

#include <libgscore/gscoretypes.h>
#include <libgscore/macros.h>
#include <libgscorebase/score.h>
#include <libgscorebase/selection-area.h>
#include <libgscorebase/display.h>

extern gboolean score_window_new(Score *score);


extern gboolean
score_window_new(Score *score)
{
	SelectionArea *selection;
        Display       *display;


	selection = gscore_selection_area_new();

	if ( ! score )
		score = gscore_score_new();

	display = gscore_display_new();

}
