/*
 * main.c
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

/* main.c is for initialization of the program: assigning values to variables and 
 * giving callbacks to the window and the score area widget.
 * If you want to see how the score is drawn, please have a look at realize_area.c */


#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>

#include "gettext.h"

#include "gscore.h"
#include "constants.h"
#include "splash.h"
#include "file.h"
#include "realize_area.h"
#include "selection.h"
#include "key_event.h"
#include "plugin.h"
#include "macros.h"
#include "draw.h"
#include "spacings.h"
#include "key_cursor.h"
#include "mouse_event.h"

GtkWidget *Window;
GladeXML *gladexml;

GList *plugins_list;
gint nb_plugins;


Score_t     Score;

Selection_t Selection;
Clipboard_t Clipboard;
KeyCursor_t KeyCursor;
Spacings_t  Spacings;

static void 
print_gpl(void)
{
	g_print("\nGscore v %s, Copyright 2001-2005 Sebastien Y. Tricaud\n", g_strdup_printf("%s", VERSION));
	g_print("Gscore comes with ABSOLUTELY NO WARRANTY and is provided AS IS;\n");
	g_print("This is free software, and you are welcome to redistribute it\n");
	g_print("under certain conditions;\n");
	g_print("Please read the file COPYING provided with the program for details.\n\n");
}



/***
 *** gives the right value to variables on starting
 ***/

static 
void gscore_init(void)
{
	// Global variables initializations

	print_gpl();

	set_spacings_init();
	set_values_spacings_spinbuttons();

	/* What we display in the score */
	Score.Display = g_malloc(sizeof(Display_t));
	Score.Display->measure_number = TRUE;
	Score.Display->instruments = FALSE;
	Score.Display->clefs = TRUE;
	Score.Display->score_expressions = TRUE;
	Score.Display->barlines = TRUE;
	Score.Display->ending_bar = TRUE;
	Score.Display->key_signature = TRUE;
	Score.Display->time_signature = TRUE;
	Score.Display->tempo = TRUE;

	Score.Staff_list = NULL;   /* Staff list */

	Score.tempo = 60;
	Score.tempo_text = g_string_new("");

	Score.Identity = g_malloc(sizeof(Identity_t));
	Score.Identity->title = g_string_new(_("My Score"));
	Score.Identity->subtitle = g_string_new(_("made with gscore"));
	Score.Identity->composer = g_string_new(_("gscore's user"));

	Score.staff_extremity_end_x = 100; /* Just a value to start, nothing really important */
	Score.staff_startx = Spacings.Clefs.sb + STANDARD_KEY_SIZE + Spacings.Clefs.sa + 
		get_key_signature_spacing(KEY_SIGNATURE_TREBLE_EMPTY) + Spacings.KeySignatures.saks +
		STANDARD_TIME_SIGNATURE_SIZE + Spacings.TimeSignatures.sats;

	Selection.object_type = CURSOR;
	Selection.x_origin = 0;
	Selection.y_origin = 0;
	Selection.x = 0;
	Selection.y = 0;
	Selection.accidentals |= A_NONE;

	/* Create a Staff, to have something when we start the software */

	if( ! create_staff(5, 8, Spacings.Measures.xpsfm, Spacings.Measures.ypsfm))
		printf("ERROR CREATING STAFF");

	set_staff_selected(0);

	staff_set_key(get_staff_selected(), TREBLE_KEY);

	staff_set_key_signature(get_staff_selected(), KEY_SIGNATURE_TREBLE_EMPTY);

/* 	set_staff_unselect(get_staff_selected()); */
/* 	set_staff_selected(1); */

	KeyCursor.position = 0;
}

/*** 
 *** Events on the drawing area
 ***/

static gboolean
drawing_area_events(GtkWidget *canvas, GdkEvent  *ev)
{

        GdkEventButton *event_btn;

	switch (ev->type)
		{
		
		case GDK_MOTION_NOTIFY:
			return mouse_motion_event(canvas, (GdkEventMotion *)ev, NULL);

		case GDK_KEY_PRESS:
			printf("Key press\n");
			break;

		case GDK_KEY_RELEASE:
			printf("Key Realeased\n");
			break;

			/* 		return key_event(canvas, (GdkEventKey *)ev); */
		
		case GDK_BUTTON_PRESS:
			switch(ev->button.button)
				{
				case 1:
					/* Select the staff with which you want to work */
					event_btn = (GdkEventButton *)ev;
					printf("A2: %.0f\n", event_btn->y);
					set_staff_selected(get_staff_id(event_btn->y));
					/* For the selection */
					return set_selection_origin(canvas, (GdkEventButton *)ev);
				case 3:
					/* 			return popup_action(canvas, (GdkEventButton *)ev); */
					break;
				}
			break;
		
		case GDK_BUTTON_RELEASE:
			switch(ev->button.button)
				{
				case 1:
					return mouse_button_release_event(canvas, (GdkEventButton *)ev, NULL);
				}
			break;
		
		case GDK_EXPOSE:
			return score_area_callback(canvas, (GdkEventExpose *)ev);

		default:
			return FALSE;
		}

}

void showda(void)
{

	g_print("EXPOSE EVENT\n");

}

static
void glade_set_widgets(void)
{
	GtkWidget *objects_vbox, *buttons_vbox;
	GtkWidget *objects_hbox;
	GtkWidget *object_button;

	Score.area = glade_xml_get_widget (gladexml, "sw_score_da");

	gtk_widget_set_events(Score.area, GDK_EXPOSURE_MASK
			      | GDK_LEAVE_NOTIFY_MASK
			      | GDK_BUTTON_PRESS_MASK
			      | GDK_BUTTON_MOTION_MASK
                              | GDK_BUTTON1_MOTION_MASK
                              | GDK_KEY_PRESS_MASK
                              | GDK_KEY_RELEASE_MASK
			      | GDK_BUTTON_RELEASE_MASK
			      | GDK_POINTER_MOTION_MASK);

	Score.height = 500;
	Score.width = 500;

	g_signal_connect(GTK_OBJECT(Score.area), "expose_event",
			 G_CALLBACK(score_area_callback), NULL);
	g_signal_connect(GTK_OBJECT(Score.area), "button_press_event",
			 G_CALLBACK(mouse_button_press_event), NULL);
	g_signal_connect(GTK_OBJECT(Score.area), "button_release_event",
			 G_CALLBACK(mouse_button_release_event), NULL);
	g_signal_connect(GTK_OBJECT(Score.area), "motion_notify_event",
			 G_CALLBACK(mouse_motion_event), NULL);

}


int main(int argc, char *argv[]) 
{
	GtkWidget *widget;

	gint i = 0;
	gchar *full_filename;
	GscorePlugin *plugin;
	plugin_pnf *ppnf;

	gint scale = 0;

	FILE *fp;


	gtk_init(&argc, &argv);


	nb_plugins = gscore_plugins_load(&plugins_list);

	splash_create();

	for ( i = 0; i < nb_plugins; i++) {
			ppnf = g_list_nth_data(plugins_list, i);
			full_filename = g_strconcat(ppnf->path, G_DIR_SEPARATOR_S, ppnf->filename, NULL);

			g_print("filename: %s\n", full_filename);
			GSCORE_PLUGIN_INIT(plugin);
			plugin = gscore_plugin_get(full_filename);

			if ( ! plugin ) {
				gw_message_error(g_strdup_printf(_("Unable to load plugin %s"),full_filename));
			} else {
				plugin->init_proc();
				splash_update("Loading plugins...", 
					      plugin->info->name, nb_plugins - i);
			}
	}

	splash_destroy();

	gladexml = glade_xml_new(get_file_from_data_dir("glade/gscore.glade"), NULL, NULL);

	if ( ! gladexml ) 
		g_error(_("Glade file not found in %s\n"), get_file_from_data_dir("glade/"));


	glade_xml_signal_autoconnect(gladexml);

	glade_set_widgets();

	gscore_init();

	

	widget = glade_xml_get_widget (gladexml, "score_window");
	gtk_widget_show(widget);
	g_signal_connect(GTK_OBJECT(widget), "key_press_event",
			 G_CALLBACK(score_key_press_event), NULL);


        staff_update_statusbar();

	/* Set the white color to the drawing area */
	/* We want the score to be white */
	if ( ! Score.area ) {
		printf(_("Error: The score layout cannot be drawn\n"));
		exit(1);
	} else {
		colorize_drawingarea(Score.area, 65535, 65535, 65535);
	}

	fp = fopen(g_strconcat(g_get_home_dir(), "/.gscore", NULL), "r");
	if ( ! fp ) { 		/* The file doesn't exist, gscore is launched for the first time! */
		gw_message_info("Congratulations!\nYou are running Gscore for the first time!\n\nFirst of all, this is not a final version. There are many bugs, many features missing...\nHowever, feel free to report bugs and wishes to help this software to become better.\n\nA few tips to start:\n- <Space>: adds the object\n- <Tab>: add a single barline\n- <Del>: Erase the objects selected with the mouse.\n\nThis release can make ABC Music. If you want to print your score, you need the abc tools (abcm2ps for example).");
		fp = fopen(g_strconcat(g_get_home_dir(), "/.gscore", NULL), "w");
		fprintf(fp, "Gscore 0.0.9\n");
	}
	fclose(fp);


	gtk_main();
  
	return(0);
}
