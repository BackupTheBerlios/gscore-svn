/*
 * score.c
 * gscore - a musical score editor
 *
 * (C) Copyright 2001-2004 Sebastien Tricaud
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

#include "gscore.h"
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

#define OK     "OK"
#define CANCEL "Cancel"


extern void
set_tempo(void)
{
        GtkWidget *spinbutton;
        GtkWidget *entry;
        GtkWidget *radiobutton;
	Score_t *score;
	GtkWidget *area;
	
	spinbutton =  glade_xml_get_widget (gladexml, "tempo_spinbutton");
	entry =  glade_xml_get_widget (gladexml, "tempo_entry");
	score = score_get_from_widget(entry);
	area = score_get_area_from_widget(entry);
	
        score->tempo = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton));

	radiobutton =  glade_xml_get_widget (gladexml, "tempo_quarter_rb");
        g_print("state: %d\n", gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton)));

        score->tempo_text = g_string_new(gtk_entry_get_text((GtkEntry *)entry));

	refresh(area);
}

void add_staff (gint data)
{
/*      switch (data) */
/*      { */
/*      case TREBLE_KEY:  */
/*           g_message("Add a trebble key"); */
/*           break; */
/*      } */
}


extern
gint score_add_tab (gpointer callback_data, guint callback_action, GtkWidget *widget)
{

/*      Score.nb_staves++; */
     
/*      Score.Staff[Score.nb_staves-1].nb_lines = 6; */
/*      Score.Staff[Score.nb_staves-1].space_btw_lines = 10; */
/*      Score.Staff[Score.nb_staves-1].space_with_staff_up = 50; */
/*      Score.Staff[Score.nb_staves-1].key = TAB_KEY; */
/*      Score.Staff[Score.nb_staves-1].extremity_end_x = Score.Staff[Score.nb_staves-2].extremity_end_x; */
/*      Score.Staff[Score.nb_staves-1].extremity_begin_x = Score.Staff[Score.nb_staves-2].extremity_begin_x; */
/*      Score.Staff[Score.nb_staves-1].extremity_begin_y = Score.Staff[Score.nb_staves-2].extremity_end_y+Score.Staff[Score.nb_staves-1].space_with_staff_up; */
/*      Score.Staff[Score.nb_staves-1].extremity_end_y = Score.Staff[Score.nb_staves-1].extremity_begin_y-1 + (Score.Staff[Score.nb_staves-1].nb_lines+((Score.Staff[Score.nb_staves-1].nb_lines-1)*Score.Staff[Score.nb_staves-1].space_btw_lines)); */
/* /\*      Score.Staff[Score.nb_staves-1].middle = Score.Staff[Score.nb_staves-1].extremity_begin_y; *\/ */

/*      Score.height = Score.Staff[Score.nb_staves-1].extremity_end_y + 100; */

/*      draw_staff(Score.Staff[Score.nb_staves-1].nb_lines, Score.Staff[Score.nb_staves-1].space_btw_lines,  */
/*                 Score.Staff[Score.nb_staves-2].extremity_begin_x,  */
/*                 Score.Staff[Score.nb_staves-2].extremity_end_y + Score.Staff[Score.nb_staves-1].space_with_staff_up, */
/*                 Score.Staff[Score.nb_staves-2].extremity_end_x, TRUE, TRUE); */

/* /\*      draw_barline_endstaff(Score.nb_staves); *\/ */
/*      refresh(); */

	return 0;
}

void
remove_score (gpointer callback_data, guint callback_action, GtkWidget *widget)
{
/*      GtkWidget *dialog; */
     
/*      GtkWidget *label; */
/*      GtkWidget *ok_button; */
/*      GtkWidget *cancel_button; */
     
     
/*      dialog = gtk_dialog_new(); */
/*      gtk_widget_show(dialog); */
     
     
/*      label = gtk_label_new("\nBEWARE!\n  Erase the current staff ?  \n"); */
/*      gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), label); */
     
/*      ok_button = gtk_button_new_with_label(" Yes "); */
/*      g_signal_connect_swapped(GTK_OBJECT(ok_button), "clicked", */
/*                               G_CALLBACK(gtk_widget_destroy), GTK_OBJECT(dialog)); */
/*      gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->action_area), ok_button); */
     
/*      cancel_button = gtk_button_new_with_label(" No "); */
/*      g_signal_connect_swapped(GTK_OBJECT(cancel_button), "clicked", */
/*                               G_CALLBACK(gtk_widget_destroy), */
/*                               GTK_OBJECT(dialog));  */
/*      gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->action_area), cancel_button); */
     
/*      gtk_widget_show_all(dialog); */

}

void
score2tab (gpointer callback_data, guint callback_action, GtkWidget *widget)
{
/*      GList *tmp_list; */


/*      for ( tmp_list = Score.Staff[Score.staff_selected].Object_list ; tmp_list ; tmp_list = g_list_next(tmp_list)) */
/*      { */
/*           gint number = 0;  */
/*           gint string = 0; */
/*           gint calcul_string = 0; */
/*           Object_t *object; */
          
/*           object = (Object_t *)tmp_list->data; */
          
          
/*           switch (object->pitch) */
/*           { */
               
/*           case 0: */
/* /\*                number = score_to_tab_simple_return_number(object->position); *\/ */
/* /\*                string = score_to_tab_simple_return_string(object->position); *\/ */
/*                string = 1; */
/*                number = 0; */
/*                if ( string == 1 ) { */
/*                     calcul_string = Score.Staff[1].extremity_begin_y-3; */
/*                } */
/*                if ( number == 0 ) { */
                    
/*                     draw_note(TWO, FALSE, object->x, calcul_string, 0, 0, 0, 0); */
/* /\*                     draw_note(two_xpm, object->x, calcul_string, 0, 0, 0, 0); *\/ */
/*                               } */
/*                break; */

/*           case 1: */
/*                number = score_to_tab_simple_return_number(object->pitch); */
/*                string = score_to_tab_simple_return_string(object->pitch); */
/*                if ( string == 1 ) { */
/*                     calcul_string = Score.Staff[1].extremity_begin_y-3; */
/*                } */
/*                if ( number == 1 ) { */
                    
/*                     draw_note(FIVE, FALSE, object->x, calcul_string, 0, 0, 0, 0); */
/* /\*                     draw_note(five_xpm, object->x, calcul_string, 0, 0, 0, 0); *\/ */
/*                               } */
/*                break; */

/*           case 3: */
/*                number = score_to_tab_simple_return_number(object->pitch); */
/*                string = score_to_tab_simple_return_string(object->pitch); */
/*                if ( string == 1 ) { */
/*                     calcul_string = Score.Staff[1].extremity_begin_y-3; */
/*                } */
/*                if ( number == 3 ) { */
                    
/*                     draw_note(THREE, FALSE, object->x, calcul_string, 0, 0, 0, 0); */
/* /\*                     draw_note(three_xpm, object->x, calcul_string, 0, 0, 0, 0); *\/ */
/*                               } */
/*                break; */
               
/*           } */

/*      }                */
}
/* void score_midi_play (gpointer callback_data, guint callback_action, */
/*                       GtkWidget * widget) */
/* { */
/*      GscoreExportFilter *ef; */
/*      const char *filename; */

/*      filename = g_strconcat(g_get_tmp_dir(),"/","gscore-midi-play.mid",NULL); */
     
/*      g_print("filename: %s\n", filename); */

/*      ef = filter_guess_export_filter(filename); */
/*      ef->export(get_score(), filename, ef->user_data); */


/*      system(g_strdup_printf("/usr/bin/timidity %s", filename)); */

/*      system(g_strdup_printf("/bin/rm -f %s", filename)); */

/* /\*      execl("/usr/bin/timidity", "timidity", filename, NULL); *\/ */

/* /\*      g_print("Play_midi\n");  *\/ */

/* } */

void score_set_tempo(gpointer callback_data, guint callback_action, GtkWidget *widget)
{

/*      GtkWidget * dialog; */
/*      GtkWidget * spinbutton; */

/*      GtkAdjustment * adj; */
     
          
/*      dialog = gtk_dialog_new_with_buttons(_("Set the tempo"), NULL, */
/*                                           GTK_DIALOG_MODAL, */
/*                                           GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, */
/*                                           GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, */
/*                                           NULL); */
     
/*      g_signal_connect(G_CALLBACK(dialog), "destroy", */
/*                       G_CALLBACK(gtk_widget_destroyed), */
/*                       &dialog); */
     

/*      adj = GTK_ADJUSTMENT(gtk_adjustment_new(Score.tempo, */
/*                                              40, 300, */
/*                                              1.0, 10.0, 10.0 )); */
/*      spinbutton = gtk_spin_button_new(adj, 1.0, 0); */
/*      gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), spinbutton); */
/*      gtk_widget_show(spinbutton); */

/*      /\* Execute the OK button action *\/ */
/*      if (gtk_dialog_run(GTK_DIALOG(dialog))==GTK_RESPONSE_ACCEPT) */
/*      { */
/*           Score.tempo = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton)); */
/*      } */
/*      gtk_widget_destroy(dialog); */
}

void on_set_header_activate_default(void)
{
	GtkWidget *title;
	GtkWidget *subtitle;
	GtkWidget *composer;
	Score_t *score;
	
	title = glade_xml_get_widget(gladexml, "title_entry");
	subtitle = glade_xml_get_widget(gladexml, "subtitle_entry");
	composer = glade_xml_get_widget(gladexml, "composer_entry");
	score = score_get_from_widget(title);
	
	gtk_entry_set_text(GTK_ENTRY(title), score->Identity->title->str);
	gtk_entry_set_text(GTK_ENTRY(subtitle), score->Identity->subtitle->str);
	gtk_entry_set_text(GTK_ENTRY(composer), score->Identity->composer->str);

}

void score_set_header_ok(void)
{
	GtkWidget *title;
	GtkWidget *subtitle;
	GtkWidget *composer;
	Score_t *score;

	title = glade_xml_get_widget(gladexml, "title_entry");
	subtitle = glade_xml_get_widget(gladexml, "subtitle_entry");
	composer = glade_xml_get_widget(gladexml, "composer_entry");
	score = score_get_from_widget(title);

	score->Identity->title = g_string_assign(score->Identity->title, gtk_entry_get_text(GTK_ENTRY(title)));
	score->Identity->subtitle = g_string_assign(score->Identity->subtitle, gtk_entry_get_text(GTK_ENTRY(subtitle)));
	score->Identity->composer = g_string_assign(score->Identity->composer, gtk_entry_get_text(GTK_ENTRY(composer)));

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

void score_create_window(Score_t *score)
{
        Display_t *Display;
        Score_selection_t *selection;
        KeyCursor_t *KeyCursor;
        GladeXML *xml;
        GtkWidget *window;
        GtkWidget *area;
  
        selection = g_malloc(sizeof(Score_selection_t));
        selection->x_origin = 0;
        selection->y_origin = 0;
        selection->x = 0;
        selection->y = 0;
  
        if(score==NULL) {
                score = g_malloc(sizeof(Score_t));
    	

                score->Staff_list = NULL;   /* Staff list */
                
                score->object_id = 0;
                score->tempo = 60;
                score->tempo_text = g_string_new("");

                score->Identity = g_malloc(sizeof(Identity_t));
                score->Identity->title = g_string_new(_("My Score"));
                score->Identity->subtitle = g_string_new(_("made with gscore"));
                score->Identity->composer = g_string_new(_("gscore's user"));

                score->staff_extremity_end_x = 100; /* Just a value to start, nothing really important */
                score->staff_startx = Spacings.Clefs.sb + STANDARD_KEY_SIZE + Spacings.Clefs.sa + 
                        get_key_signature_spacing(KEY_SIGNATURE_TREBLE_EMPTY) + Spacings.KeySignatures.saks +
                        STANDARD_TIME_SIGNATURE_SIZE + Spacings.TimeSignatures.sats;


                /* Create a Staff, to have something when we start the software */

                if( ! create_staff(score, 5, 8, Spacings.Measures.xpsfm, Spacings.Measures.ypsfm))
                        printf("ERROR CREATING STAFF");

                set_staff_selected(score, 0);

                staff_set_key(score, get_staff_selected(score), TREBLE_KEY);

                staff_set_key_signature(score, get_staff_selected(score), KEY_SIGNATURE_TREBLE_EMPTY);

                /* 	set_staff_unselect(get_staff_selected()); */
                /* 	set_staff_selected(1); */

        }

        KeyCursor = g_malloc(sizeof(KeyCursor_t));
  
        KeyCursor->position = 0;



        Display = g_malloc(sizeof(Display_t));
        Display->measure_number = TRUE;
        Display->instruments = FALSE;
        Display->clefs = TRUE;
        Display->score_expressions = TRUE;
        Display->barlines = TRUE;
        Display->ending_bar = TRUE;
        Display->key_signature = TRUE;
        Display->time_signature = TRUE;
        Display->tempo = TRUE;

        /*   xml = glade_xml_new(get_file_from_data_dir("glade/gscore.glade"), */
        /* 		      "score_window", NULL); */
        /* BEGIN Dirty hack */
        xml = glade_xml_new(get_file_from_data_dir("glade/gscore.glade"),
                            NULL, NULL);
        window = glade_xml_get_widget(xml, "main_window");
        gtk_widget_hide(window);
        /* END Dirty hack */
        window = glade_xml_get_widget(xml, "score_window");
        glade_xml_signal_autoconnect(xml) ;
  
        g_signal_connect(GTK_OBJECT(window), "key_press_event",
                         G_CALLBACK(score_key_press_event), NULL);

        area = glade_xml_get_widget(xml, "sw_score_da");

        g_object_set_data(G_OBJECT(window), "score", score);
        g_object_set_data(G_OBJECT(window), "area", area);
        g_object_set_data(G_OBJECT(window), "selection", selection);
        g_object_set_data(G_OBJECT(window), "cursor", KeyCursor);
        g_object_set_data(G_OBJECT(window), "display", Display);

        /*   glade_set_widgets(xml); */
        score->height = 500;
        score->width = 500;
  
        g_signal_connect(GTK_OBJECT(area), "expose_event",
                         G_CALLBACK(score_area_callback), NULL);
        g_signal_connect(GTK_OBJECT(area), "button_press_event",
                         G_CALLBACK(mouse_button_press_event), NULL);
        g_signal_connect(GTK_OBJECT(area), "button_release_event",
                         G_CALLBACK(mouse_button_release_event), NULL);
        /*   g_signal_connect(GTK_OBJECT(area), "motion_notify_event", */
        /* 		   G_CALLBACK(mouse_motion_event), NULL); */
	
        staff_update_statusbar(xml);

        gtk_widget_show(window);
  
        /* Set the white color to the drawing area */
        /* We want the score to be white */
        if ( ! area ) {
                printf(_("Error: The score layout cannot be drawn\n"));
                /*     return -1; */
        } else {
                colorize_drawingarea(area, 65535, 65535, 65535);
        }
}

gboolean score_activate_callback(GtkWidget *widget)
{
  static const char *props[] = {
    "score", "area", "selection", "cursor", "display",
    NULL};
  int i;
  GtkWidget *main_window;
  GtkWidget *score_window;
  
  main_window = glade_xml_get_widget(gladexml, "main_window");
  score_window = get_toplevel(widget);
  
  for(i=0; props[i] != NULL; ++i) {
    g_object_set_data(G_OBJECT(main_window), props[i],
		      g_object_get_data(G_OBJECT(score_window),
					props[i]));
    
  }
  return TRUE;
  
}

