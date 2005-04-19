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
#include "display.h"
#include "draw.h"
#include "draw_barline.h"
#include "constants.h"
#include "score.h"
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

GladeXML  *score_xml;
GtkWidget *score_widget;

/*
 * BEGIN: GTK WIDGETS
 * This are temporary GTK Widget so that I can make the release and strop strugling with
 * glade to get data from some random boxes
 * That shouldn't be there, it will be dropped latter.
 */
extern void 
set_header_widget(GtkButton *widget, gpointer user_data)
{
        GtkWidget *dialog;
        GtkWidget *button;
        GtkWidget *main_vbox, *vbox, *hbox;
        GtkWidget *label;
        GtkWidget *title_entry;
        GtkWidget *subtitle_entry;
        GtkWidget *composer_entry;
        GtkWidget *hseparator;

        gint response;

        Score_t *score;
	score = score_get_from_widget(widget);

        
        dialog = gtk_dialog_new_with_buttons("Set Header", NULL,
                                             GTK_DIALOG_MODAL, 
                                             GTK_STOCK_CANCEL,
                                             GTK_RESPONSE_REJECT,
                                             GTK_STOCK_OK,
                                             GTK_RESPONSE_ACCEPT,
                                             NULL);

        hbox = gtk_hbox_new(FALSE, 10);
        gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox,
                           TRUE, TRUE, 0);

        vbox = gtk_vbox_new(TRUE, 10);
        gtk_box_pack_start(GTK_BOX(hbox), vbox,
                           TRUE, TRUE, 0);

        label = gtk_label_new("Title: ");
        gtk_box_pack_start(GTK_BOX(vbox), label,
                           FALSE, FALSE, 5);

        label = gtk_label_new("Subtitle: ");
        gtk_box_pack_start(GTK_BOX(vbox), label,
                           FALSE, FALSE, 5);

        label = gtk_label_new("Composer: ");
        gtk_box_pack_start(GTK_BOX(vbox), label,
                           FALSE, FALSE, 5);

        vbox = gtk_vbox_new(TRUE, 10);
        gtk_box_pack_start(GTK_BOX(hbox), vbox,
                           TRUE, TRUE, 5);

        title_entry = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(vbox), title_entry,
                           FALSE, FALSE, 5);
	gtk_entry_set_text(GTK_ENTRY(title_entry), score->Identity->title->str);

        subtitle_entry = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(vbox), subtitle_entry,
                           FALSE, FALSE, 5);
	gtk_entry_set_text(GTK_ENTRY(subtitle_entry), score->Identity->subtitle->str);

        composer_entry = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(vbox), composer_entry,
                           FALSE, FALSE, 5);
	gtk_entry_set_text(GTK_ENTRY(composer_entry), score->Identity->composer->str);
    
        gtk_widget_show_all(dialog);

        response = gtk_dialog_run (GTK_DIALOG (dialog));

        if (response == GTK_RESPONSE_ACCEPT) {
                score->Identity->title = g_string_new(gtk_entry_get_text(GTK_ENTRY(title_entry)));
                score->Identity->subtitle = g_string_new(gtk_entry_get_text(GTK_ENTRY(subtitle_entry)));
                score->Identity->composer = g_string_new(gtk_entry_get_text(GTK_ENTRY(composer_entry)));
        }

        gtk_widget_destroy (dialog);
}
/* 
 * END: GTK WIDGETS
 */


/*
 * FIXME: Should be backported to libgscore
 * Creates a new score object
 * @Returns: the score object
 */ 
Score_t *gscore_score_new(void)
{

        Score_t *score;


        score = g_malloc(sizeof(Score_t));

        if ( ! score ) {
                printf("Memory exhausted!\n");
                return NULL;
        }

        score->Staff_list = NULL;   /* Staff list */
                
        score->object_id = 0;
        score->tempo = 60;
        score->tempo_text = g_string_new("");

/*         score->Colors = g_malloc(sizeof(GscoreColors_t)); */
/*         if ( ! score->Colors ) { */
/*                 printf("Memory exhausted!\n"); */
/*                 return NULL; */
/*         } */
/*         score->Colors->staves[0] = 0; /\* red *\/ */
/*         score->Colors->staves[1] = 0; /\* green *\/ */
/*         score->Colors->staves[2] = 0; /\* blue *\/ */
/*         score->Colors->objects[0] = 0; /\* red *\/ */
/*         score->Colors->objects[1] = 0; /\* green *\/ */
/*         score->Colors->objects[2] = 0; /\* blue *\/ */

        score->Identity = g_malloc(sizeof(Identity_t));
        if ( ! score->Identity ) {
                printf("Memory exhausted!\n");
                return NULL;
        }

        score->Identity->title = g_string_new(_("My Score"));
        score->Identity->subtitle = g_string_new(_("made with gscore"));
        score->Identity->composer = g_string_new(_("gscore's user"));

        score->staff_extremity_end_x = 100; /* Just a value to start, nothing really important */
        score->staff_startx = Spacings.Clefs.sb + STANDARD_KEY_SIZE + Spacings.Clefs.sa + 
                get_key_signature_spacing(KEY_SIGNATURE_TREBLE_EMPTY) + Spacings.KeySignatures.saks +
                STANDARD_TIME_SIGNATURE_SIZE + Spacings.TimeSignatures.sats;


        /* Create a Staff, to have something when we start the software */

        if( ! create_staff(score, 5, 8, Spacings.Measures.xpsfm, Spacings.Measures.ypsfm) )
                printf("ERROR CREATING STAFF");

        set_staff_selected(score, 0);

        staff_set_key(score, get_staff_selected(score), TREBLE_KEY);

        staff_set_key_signature(score, get_staff_selected(score), KEY_SIGNATURE_TREBLE_EMPTY);

        /* 	set_staff_unselect(get_staff_selected()); */
        /* 	set_staff_selected(1); */

        return score;

}

static GtkWidget *get_toplevel(GtkWidget *widget)
{
        GladeXML *xml = glade_get_widget_tree(widget);

        if(xml == gladexml) {
                return glade_xml_get_widget(xml, "main_window");
        } else {
                return  glade_xml_get_widget(xml, "score_window");
        }
}


Score_t* score_get_from_widget(GtkWidget *widget)
{
        GtkWidget *parent;
        parent = get_toplevel(widget);
        if(parent == NULL) return NULL;
        return (Score_t *) g_object_get_data(G_OBJECT(parent), "score");
}

extern gboolean 
score_set_to_widget(Score_t *score, GtkWidget *widget)
{
        GtkWidget *parent;
        parent = get_toplevel(widget);
        if (parent == NULL) return FALSE;
        g_object_set_data(G_OBJECT(parent), "score", score);
        
        return TRUE;
        
}
  
GtkWidget *score_get_area_from_widget(GtkWidget *widget)
{
        GtkWidget *parent;
        parent = get_toplevel(widget);
        if(parent == NULL) return NULL;
        return (GtkWidget *) g_object_get_data(G_OBJECT(parent), "area");
}


Display_t *score_get_display_from_widget(GtkWidget *widget)
{
        GtkWidget *parent;
        parent = get_toplevel(widget);
        if(parent == NULL) return NULL;
        return (Display_t *) g_object_get_data(G_OBJECT(parent), "display");
}

Score_selection_t *score_get_selection_from_widget(GtkWidget *widget)
{
        GtkWidget *parent;
        parent = get_toplevel(widget);
        if(parent == NULL) return NULL;
        return (Score_selection_t *) g_object_get_data(G_OBJECT(parent), "selection");
}

KeyCursor_t *score_get_cursor_from_widget(GtkWidget *widget)
{
        GtkWidget *parent;
        parent = get_toplevel(widget);
        if(parent == NULL) return NULL;
        return (KeyCursor_t *) g_object_get_data(G_OBJECT(parent), "cursor");
}

GtkScrolledWindow *score_get_scrolled_window_from_widget(GtkWidget *widget)
{
        GtkWidget *parent;
        parent = get_toplevel(widget);
        if(parent == NULL) return NULL;
        return (GtkScrolledWindow *) g_object_get_data(G_OBJECT(parent), "scrolledwindow");
}

void score_create_window(Score_t *score)
{
        Display_t *Display;
        Score_selection_t *selection;
        KeyCursor_t *KeyCursor;
        ScoreWidget *sw;
        
        GtkWidget *viewport;
/*         GladeXML *xml; */
/*         GtkWidget *window; */
/*         GtkWidget *area; */

/*         GtkScrolledWindow *scrolled_window; */
  

        selection = g_malloc(sizeof(Score_selection_t));
        selection->x_origin = 0;
        selection->y_origin = 0;
        selection->x = 0;
        selection->y = 0;
  
        if(score == NULL) {
                score = gscore_score_new();
        }

        KeyCursor = g_malloc(sizeof(KeyCursor_t));
  
        KeyCursor->position = 0;


        Display = gscore_display_new();

        score_xml = glade_xml_new(get_file_from_data_dir("glade/score-ui.glade"),
                            NULL, NULL);

        score_widget = glade_xml_get_widget(score_xml, "score");
        glade_xml_signal_autoconnect(score_xml);
        g_signal_connect(G_OBJECT(score_widget), "key_press_event",
                         G_CALLBACK(score_key_press_event), NULL);

        viewport = glade_xml_get_widget(score_xml, "score_viewport");

        sw = score_widget_new();
        score->height = 500;
        score->width = 500;

        gtk_widget_set_usize(GTK_WIDGET(sw), score->width, score->height);
        g_signal_connect (G_OBJECT (sw), "paint", G_CALLBACK (layout_paint), NULL);

        gtk_container_add(GTK_CONTAINER(viewport), sw);

        g_print("OK\n");

        gtk_widget_show(sw);

/*         area = glade_xml_get_widget(xml, "sw_score_da"); */

/*         scrolled_window = glade_xml_get_widget(xml, "sw_score_sw"); */

/*         g_object_set_data(G_OBJECT(window), "score", score); */
/*         g_object_set_data(G_OBJECT(window), "area", area); */
/*         g_object_set_data(G_OBJECT(window), "selection", selection); */
/*         g_object_set_data(G_OBJECT(window), "cursor", KeyCursor); */
/*         g_object_set_data(G_OBJECT(window), "display", Display); */
/*         g_object_set_data(G_OBJECT(window), "scrolledwindow", scrolled_window); */

        /*   glade_set_widgets(xml); */

/*         g_print("**** staff_selected = %d\n", score->staff_selected); */
  
/*         g_signal_connect(GTK_OBJECT(area), "expose_event", */
/*                          G_CALLBACK(score_area_callback), NULL); */
/*         g_signal_connect(GTK_OBJECT(area), "button_press_event", */
/*                          G_CALLBACK(mouse_button_press_event), NULL); */
/*         g_signal_connect(GTK_OBJECT(area), "button_release_event", */
/*                          G_CALLBACK(mouse_button_release_event), NULL); */


/*           g_signal_connect(GTK_OBJECT(area), "motion_notify_event", */
/*         		   G_CALLBACK(mouse_motion_event), NULL); */
	
/*         staff_update_statusbar(xml); */

        gtk_widget_show_all(score_widget);
  
        /* Set the white color to the drawing area */
        /* We want the score to be white */
/*         if ( ! area ) { */
/*                 printf(_("Error: The score layout cannot be drawn\n")); */
/*                 /\*     return -1; *\/ */
/*         } else { */
/*                 colorize_drawingarea(area, 65535, 65535, 65535); */
/*         } */
}

gboolean score_set_staff_extremity_end_x(Score_t *score, gdouble extremity_end_x)
{
        score->staff_extremity_end_x = extremity_end_x;

	return TRUE;
}

