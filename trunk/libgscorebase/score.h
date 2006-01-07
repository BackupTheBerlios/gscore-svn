/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorebase/score.h
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

#ifndef __SCORE_H__
#define __SCORE_H__

#include <glib.h>
#include <libgscore/gscoretypes.h>
#include <libgscore/gscoreerrors.h>

G_BEGIN_DECLS

struct _Score
{

	/** Window's title: <Untitled score> by default */
	gchar       * window_title;
	/** Score tempo */
        gint          tempo;             
	/** The note refered by the tempo: 0->doublewhole, 1->whole, 2->half, 4->quarter, 8->eighth ... */
        gint          tempo_note; 
	/** Optional Text for the tempo */
        GString     * tempo_text; 
	/** Every object in the score has a *unique* ID */
        gulong        object_id;    
	/** Has the score been modified since we saved ? useful for save/save as and quit */
        gboolean      is_modified;  
	/** How many staves in the score */
        gint          count_staves; 
        /** Zoom applied to score */
        gdouble       zoom;
	/** How wide is the drawing area (score) widget ? */     
        gdouble       width;     
	/** How high is the drawing area (score) widget ? */
        gdouble       height;       
	/** Current selected staff number */
        gint          staff_selected; 
	/** Position X where the staff ends */
        gdouble       staff_extremity_end_x;

        Identity      * identity; /* Useful informations */
        ObjectColor   * objectcolor;
        Display       * display;

        /* Staves: *FIXME* One of the two is useless */
        GList              * staves;
/*         GList         * staff_list; */
/*         struct Staff  * staff; */

        /* Selection Area */
        SelectionArea      * selection_area;

};

Score        * gscore_score_new(void);
GSCORE_ERROR   gscore_score_set_window_title(Score *score, gchar *title);
gchar        * gscore_score_get_window_title(Score *score);
GSCORE_ERROR   gscore_score_set_tempo(Score *score, gint tempo);
gint           gscore_score_get_tempo(Score *score);
GSCORE_ERROR   gscore_score_set_tempo_note(Score *score, gint tempo_note);
gint           gscore_score_get_tempo_note(Score *score) ;
GSCORE_ERROR   gscore_score_set_tempo_text(Score *score, gchar *tempo_text);
gchar        * gscore_score_get_tempo_text(Score *score) ;
GSCORE_ERROR   gscore_score_set_modified(Score *score, gboolean modified);
gboolean       gscore_score_get_modified(Score *score);
GSCORE_ERROR   gscore_score_set_zoom(Score *score, gdouble zoom);
gdouble        gscore_score_get_zoom(Score *score);
GSCORE_ERROR   gscore_score_set_width(Score *score, gdouble width);
gdouble        gscore_score_get_width(Score *score);
GSCORE_ERROR   gscore_score_set_height(Score *score, gdouble height);
gdouble        gscore_score_get_height(Score *score);
GSCORE_ERROR   gscore_score_set_staff_selected(Score *score, gint staff_selected);
gint           gscore_score_get_staff_selected(Score *score);
GSCORE_ERROR   gscore_score_set_staves_extremity_end_x(Score *score, gdouble staves_extremity_end_x);
gdouble        gscore_score_get_staves_extremity_end_x(Score *score);

G_END_DECLS

#endif /* __SCORE_H__ */
