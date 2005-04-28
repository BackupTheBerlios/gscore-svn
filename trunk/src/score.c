/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * score.c
 * gscore - a musical score editor
 *
 * (C) Copyright 2001-2005 Sebastien Tricaud
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
#include <unistd.h>
#include <gettext.h>
#include <glade/glade-xml.h>

#include <libgscore.h>

#include "gscore.h"
#include "score.h"

#include "display.h"
#include "draw.h"
#include "draw_barline.h"
#include "constants.h"
#include "staff.h"
#include "tab_transposition.h"
#include "common.h"
#include "macros.h"
#include "spacings.h"
#include "key_event.h"
#include "key_cursor.h"
#include "realize_area.h"
#include "mouse_event.h"
#include "layout-engine.h"


#define OK     "OK"
#define CANCEL "Cancel"


extern Score_t *score_new(void);
extern gboolean score_staff_add(Score_t *score, Staff_t *staff);
extern Score_t *score_get_from_widget(GtkWidget *widget);
extern gboolean score_set_to_widget(Score_t *score, GtkWidget *widget);
extern gboolean score_window_new(Score_t *score);
extern gboolean score_staff_set_extremity_end_x(Score_t *score, gdouble extremity_end_x);

static GladeXML  *score_xml;

/**
 * score_new:
 * 
 * Creates a new score object
 *
 * Returns: the score object
 */ 
extern Score_t *
score_new(void)
{

        Score_t *score;


        score = g_malloc(sizeof(Score_t));
        if ( ! score ) {
                g_print("Memory exhausted: cannot allocate new score\n");
                return NULL;
        }

        score->Staff_list = NULL;
                
        score->object_id = 0;
        score->tempo = 60;
        score->tempo_text = g_string_new("");
        score->zoom = 30;

        score->ColorObject = g_malloc(sizeof(struct GscoreColorObject_t));
        if ( ! score->ColorObject ) {
                g_print("Memory exhausted: cannot allocate new color object\n");
                return NULL;
        }
        score->ColorObject->staves = g_malloc(sizeof(struct GscoreColor_t));
        if ( ! score->ColorObject->staves ) {
                g_print("Memory exhausted: cannot allocate new staves color\n");
                return NULL;
        }
        score->ColorObject->clefs = g_malloc(sizeof(struct GscoreColor_t));
        if ( ! score->ColorObject->clefs ) {
                g_print("Memory exhausted: cannot allocate new clefs color\n");
                return NULL;
        }
        score->ColorObject->objects = g_malloc(sizeof(struct GscoreColor_t));
        if ( ! score->ColorObject->staves ) {
                g_print("Memory exhausted: cannot allocate new objects color\n");
                return NULL;
        }

        /* By default, everything is black */
        score->ColorObject->staves->red = 0;
        score->ColorObject->staves->green = 0;
        score->ColorObject->staves->blue = 0;
        score->ColorObject->clefs->red = 0;
        score->ColorObject->clefs->green = 0;
        score->ColorObject->clefs->blue = 0;
        score->ColorObject->objects->red = 0;
        score->ColorObject->objects->green = 0;
        score->ColorObject->objects->blue = 0;

        score->Identity = g_malloc(sizeof(Identity_t));
        if ( ! score->Identity ) {
                printf("Memory exhausted!\n");
                return NULL;
        }

        score->Identity->title = g_string_new(_("My Score"));
        score->Identity->subtitle = g_string_new(_("made with gscore"));
        score->Identity->composer = g_string_new(_("gscore's user"));

        score->staff_extremity_end_x = 300; /* Just a value to start, nothing really important */
        score->staff_startx = Spacings.Clefs.sb + STANDARD_KEY_SIZE + Spacings.Clefs.sa + 
                get_key_signature_spacing(KEY_SIGNATURE_TREBLE_EMPTY) + Spacings.KeySignatures.saks +
                STANDARD_TIME_SIGNATURE_SIZE + Spacings.TimeSignatures.sats;


        /* Create a Staff, to have something when we start the software */
        /* Should be removed and put in staff_new */

        if( ! create_staff(score, 5, 8, Spacings.Measures.xpsfm, Spacings.Measures.ypsfm) )
                printf("ERROR CREATING STAFF");

        set_staff_selected(score, 0);

        staff_set_key(score, get_staff_selected(score), TREBLE_KEY);

        staff_set_key_signature(score, get_staff_selected(score), KEY_SIGNATURE_TREBLE_B_SHARP);


        return score;

}

/**
 * score_staff_add:
 * @score: score the staff is added to
 * @staff: staff to add to the score. If NULL, it will add a standard staff
 *
 * Adds the staff to the score 
 * 
 * Returns: TRUE if success. FALSE if failed.
 */
extern gboolean
score_staff_add(Score_t *score, Staff_t *staff)
{

        return create_staff(score, 5, 8, Spacings.Measures.xpsfm, Spacings.Measures.ypsfm);

}

/**
 * score_get_from_widget:
 * @widget: widget to want to get score from
 *
 * Gets the score object from widget
 *
 * Returns: Score_t object or NULL if failed
 */
extern Score_t * 
score_get_from_widget(GtkWidget *widget)
{
        GtkWidget *swidget;

        swidget = glade_xml_get_widget(score_xml, "score");
        if ( ! swidget ) return NULL;

        return (Score_t *) g_object_get_data(G_OBJECT(swidget), "score");
}

/**
 * score_set_to_widget:
 * @widget: widget to want to set score to
 *
 * Sets the score object from widget
 *
 * Returns: TRUE if success, FALSE if failed
 */
extern gboolean
score_set_to_widget(Score_t *score, GtkWidget *widget)
{
        GtkWidget *swidget;

        swidget = glade_xml_get_widget(score_xml, "score");
        if ( ! swidget ) return FALSE;

        g_object_set_data(G_OBJECT(swidget), "score", score);
        
        return TRUE;
}
  

/**
 * score_window_new:
 * @score: score object
 *
 * Creates a new score window
 * 
 * Returns: TRUE if success. FALSE if failed.
 */
extern gboolean
score_window_new(Score_t *score)
{
        Display_t *Display;
        Score_selection_t *selection;
        KeyCursor_t *KeyCursor;
        ScoreWidget *sw;

        GtkWidget *score_window;


        GtkWidget *viewport;


        selection = g_malloc(sizeof(Score_selection_t));
        selection->x_origin = 0;
        selection->y_origin = 0;
        selection->x = 0;
        selection->y = 0;
  
        if(score == NULL) {
                score = score_new();
        }

        KeyCursor = g_malloc(sizeof(KeyCursor_t));
  
        KeyCursor->position = 0;


        Display = gscore_display_new();

        score_xml = glade_xml_new(get_file_from_data_dir("glade/score-ui.glade"),
                            NULL, NULL);

        score_window = glade_xml_get_widget(score_xml, "score");
        glade_xml_signal_autoconnect(score_xml);
        g_signal_connect(G_OBJECT(score_window), "key_press_event",
                         G_CALLBACK(score_key_press_event), NULL);

        viewport = glade_xml_get_widget(score_xml, "score_viewport");

        sw = score_widget_new();
        score->height = 500;
        score->width = 500;

        gtk_widget_set_usize(GTK_WIDGET(sw), score->width, score->height);
        g_signal_connect (G_OBJECT (sw), "paint", G_CALLBACK (layout_paint), NULL);

        gtk_container_add(GTK_CONTAINER(viewport), sw);

        score_set_to_widget(score, score_window);

        gtk_widget_show_all(score_window);
  
}

extern gboolean 
score_staff_set_extremity_end_x(Score_t *score, gdouble extremity_end_x)
{
        score->staff_extremity_end_x = extremity_end_x;

	return TRUE;
}

