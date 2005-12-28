/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * score.c
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
#include <libgscorebase/score.h>
#include <libgscorebase/selection.h>
#include <libgscorebase/object_color.h>


extern Score   * gscore_score_new(void);
extern gint      gscore_score_set_window_title(Score *score, gchar *title);
extern gchar   * gscore_score_get_window_title(Score *score);
extern gint      gscore_score_set_tempo(Score *score, gint tempo);
extern gint      gscore_score_get_tempo(Score *score);
extern gint      gscore_score_set_tempo_note(Score *score, gint tempo_note);
extern gint      gscore_score_get_tempo_note(Score *score) ;
extern gint      gscore_score_set_tempo_text(Score *score, gchar *tempo_text);
extern gchar   * gscore_score_get_tempo_text(Score *score) ;
extern gint      gscore_score_set_modified(Score *score, gboolean modified);
extern gboolean  gscore_score_get_modified(Score *score);
extern gint      gscore_score_set_zoom(Score *score, gdouble zoom);
extern gdouble   gscore_score_get_zoom(Score *score);
extern gint      gscore_score_set_width(Score *score, gdouble width);
extern gdouble   gscore_score_get_width(Score *score);
extern gint      gscore_score_set_height(Score *score, gdouble height);
extern gdouble   gscore_score_get_height(Score *score);
extern gint      gscore_score_set_staff_selected(Score *score, gint staff_selected);
extern gint      gscore_score_get_staff_selected(Score *score);
extern gint      gscore_score_set_staff_extremity_end_x(Score *score, gdouble staff_extremity_end_x);
extern gdouble   gscore_score_get_staff_extremity_end_x(Score *score);

/**
 * score_new:
 * 
 * Creates a new score object
 *
 * Returns: the score object
 */ 
extern Score *
gscore_score_new(void)
{

        Score *score;


        score = g_malloc(sizeof(score));
        if ( ! score ) {
                g_print("Memory exhausted: cannot allocate new score\n");
                return NULL;
        }

        score->object_id = 0;
        gscore_score_set_window_title(score, "<Untitled Score>");
        gscore_score_set_tempo(score, 60);
        gscore_score_set_tempo_text(score, "");
        gscore_score_set_zoom(score, 30);

        score->selection_area = gscore_selection_area_new();

        score->objectcolor = gscore_object_color_new();

/*         score->Staff_list = NULL; */
                

/*         score->Identity = g_malloc(sizeof(Identity_t)); */
/*         if ( ! score->Identity ) { */
/*                 printf("Memory exhausted!\n"); */
/*                 return NULL; */
/*         } */

/*         score->Identity->title    = g_string_new(_("My Score")); */
/*         score->Identity->subtitle = g_string_new(_("made with gscore")); */
/*         score->Identity->composer = g_string_new(_("gscore's user")); */

/*         score->staff_extremity_end_x = 300; /\* Just a value to start, nothing really important *\/ */
/*         score->staff_startx = Spacings.Clefs.sb + STANDARD_KEY_SIZE + Spacings.Clefs.sa + Spacings.KeySignatures.saks + */
/*                 STANDARD_TIME_SIGNATURE_SIZE + Spacings.TimeSignatures.sats; */


/*         /\* Create a Staff, to have something when we start the software *\/ */
/*         /\* Should be removed and put in staff_new *\/ */

/*         if( ! create_staff(score, 5, 8, Spacings.Measures.xpsfm, Spacings.Measures.ypsfm) ) */
/*                 printf("ERROR CREATING STAFF"); */

/*         set_staff_selected(score, 0); */

/*         staff_set_key(score, get_staff_selected(score), TREBLE_KEY); */

/*         staff_set_key_signature(score, get_staff_selected(score), KEY_SIGNATURE_EMPTY); */

        return score;
}

extern gint
gscore_score_set_window_title(Score *score, gchar *title)
{
        score->window_title = title;

        return 0;
}

extern gchar * 
gscore_score_get_window_title(Score *score) 
{
        return score->window_title;
}

extern gint
gscore_score_set_tempo(Score *score, gint tempo)
{
        score->tempo = tempo;

        return 0;
}

extern gint 
gscore_score_get_tempo(Score *score) 
{
        return score->tempo;
}

extern gint
gscore_score_set_tempo_note(Score *score, gint tempo_note)
{
        score->tempo_note = tempo_note;

        return 0;
}

extern gint 
gscore_score_get_tempo_note(Score *score) 
{
        return score->tempo_note;
}

extern gint
gscore_score_set_tempo_text(Score *score, gchar *tempo_text)
{
        score->tempo_text = g_string_new(tempo_text);

        return 0;
}

extern gchar *
gscore_score_get_tempo_text(Score *score) 
{
        return score->tempo_text->str;
}

extern gint 
gscore_score_set_modified(Score *score, gboolean modified)
{
        score->is_modified = modified;

        return 0;
}

extern gboolean
gscore_score_get_modified(Score *score)
{
        return score->is_modified;
}

extern gint
gscore_score_set_zoom(Score *score, gdouble zoom)
{
        score->zoom = zoom;

        return 0;
}

extern gdouble
gscore_score_get_zoom(Score *score)
{
        return score->zoom;
}

extern gint
gscore_score_set_width(Score *score, gdouble width)
{
        score->width = width;

        return 0;
}

extern gdouble
gscore_score_get_width(Score *score)
{
        return score->width;
}

extern gint
gscore_score_set_height(Score *score, gdouble height)
{
        score->height = height;

        return 0;
}

extern gdouble
gscore_score_get_height(Score *score)
{
        return score->height;
}

extern gint
gscore_score_set_staff_selected(Score *score, gint staff_selected)
{
        score->staff_selected = staff_selected;

        return 0;
}

extern gint
gscore_score_get_staff_selected(Score *score)
{
        return score->staff_selected;
}

extern gint
gscore_score_set_staff_extremity_end_x(Score *score, gdouble staff_extremity_end_x)
{
        score->staff_extremity_end_x = staff_extremity_end_x;

        return 0;
}

extern gdouble
gscore_score_get_staff_extremity_end_x(Score *score)
{
        return score->staff_extremity_end_x;
}
