/*
 * view.c
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

#include "gscore.h"
#include "common.h"



extern void
on_view_measure_number_activate(void)
{

        GtkWidget *widget;


	widget =  glade_xml_get_widget (gladexml, "view_measure_number");

        if ( gtk_check_menu_item_get_active((GtkCheckMenuItem *)widget) ) {
                Score.Display->measure_number = TRUE;
		refresh();
	} else {
                Score.Display->measure_number = FALSE;
		refresh();
	}

}

extern void
on_view_instruments_activate(void)
{

        GtkWidget *widget;


	widget =  glade_xml_get_widget (gladexml, "view_instruments");

        if ( gtk_check_menu_item_get_active((GtkCheckMenuItem *)widget) ) {
                Score.Display->instruments = TRUE;
		refresh();
	} else {
                Score.Display->instruments = FALSE;
		refresh();
	}

}


extern void
on_view_tempo_activate(void)
{

        GtkWidget *widget;


	widget =  glade_xml_get_widget (gladexml, "view_tempo");

        if ( gtk_check_menu_item_get_active((GtkCheckMenuItem *)widget) ) {
                Score.Display->tempo = TRUE;
		refresh();
	} else {
                Score.Display->tempo = FALSE;
		refresh();
	}

}

extern void
on_view_clefs_activate(void)
{

        GtkWidget *widget;


	widget =  glade_xml_get_widget (gladexml, "view_clefs");

        if ( gtk_check_menu_item_get_active((GtkCheckMenuItem *)widget) ) {
                Score.Display->clefs = TRUE;
		refresh();
	} else {
                Score.Display->clefs = FALSE;
		refresh();
	}

}

extern void
on_view_score_expressions_activate(void)
{

        GtkWidget *widget;


	widget =  glade_xml_get_widget (gladexml, "view_score_expressions");

        if ( gtk_check_menu_item_get_active((GtkCheckMenuItem *)widget) ) {
                Score.Display->score_expressions = TRUE;
		refresh();
	} else {
                Score.Display->score_expressions = FALSE;
		refresh();
	}

}

extern void
on_view_barlines_activate(void)
{

        GtkWidget *widget;


	widget =  glade_xml_get_widget (gladexml, "view_barlines");

        if ( gtk_check_menu_item_get_active((GtkCheckMenuItem *)widget) ) {
                Score.Display->barlines = TRUE;
		refresh();
	} else {
                Score.Display->barlines = FALSE;
		refresh();
	}

}

extern void
on_view_ending_bar_activate(void)
{

        GtkWidget *widget;


	widget =  glade_xml_get_widget (gladexml, "view_ending_bar");

        if ( gtk_check_menu_item_get_active((GtkCheckMenuItem *)widget) ) {
                Score.Display->ending_bar = TRUE;
		refresh();
	} else {
                Score.Display->ending_bar = FALSE;
		refresh();
	}

}

extern void
on_view_key_signature_activate(void)
{

        GtkWidget *widget;


	widget =  glade_xml_get_widget (gladexml, "view_key_signature");

        if ( gtk_check_menu_item_get_active((GtkCheckMenuItem *)widget) ) {
                Score.Display->key_signature = TRUE;
		refresh();
	} else {
                Score.Display->key_signature = FALSE;
		refresh();
	}

}

extern void
on_view_time_signature_activate(void)
{

        GtkWidget *widget;


	widget =  glade_xml_get_widget (gladexml, "view_time_signature");

        if ( gtk_check_menu_item_get_active((GtkCheckMenuItem *)widget) ) {
                Score.Display->time_signature = TRUE;
		refresh();
	} else {
                Score.Display->time_signature = FALSE;
		refresh();
	}

}

extern void
on_sw_score_headers_menuitem_activate(void)
{

	GtkWidget *widget;


	widget = glade_xml_get_widget(gladexml, "sw_score_headers_da");

	gtk_widget_show(widget);

}

/* void */
/* toolbar_notes(gpointer callback_data, guint callback_action, GtkWidget *widget) */
/* { */
/*   GtkWidget * Bar; */
/*   GtkWidget * hbox; */
/*   GtkWidget * ic_button; */
/*   GtkWidget * pixmap_wid; */

/*   gint i; */
/*   gchar *note_bar[]={"cursors/ic_rondecarree.xpm", "cursors/ic_ronde.xpm", "cursors/ic_blanche.xpm",  */
/*                      "cursors/ic_noire.xpm", "cursors/ic_croche.xpm", "cursors/ic_doublecroche.xpm", */
/*                      "cursors/ic_triplecroche.xpm", "cursors/ic_croche4.xpm", "cursors/ic_croche5.xpm"}; */

/*   // window  */
/*   dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL); */
/*   g_signal_connect(GTK_OBJECT(dialog), "delete_event", */
/* 		     G_CALLBACK(gtk_widget_destroy), NULL); */

/*   g_signal_connect(GTK_OBJECT(dialog), "destroy", */
/* 		     G_CALLBACK(gtk_widget_destroy), NULL); */

/*   /\* */
/*   g_signal_connect(GTK_OBJECT(dialog),g_object_weak_ref(), */
/* 		     G_CALLBACK(gtk_widget_destroy), NULL); */
/*   *\/ */
/*   // bar  */
/*   Bar = gtk_handle_box_new(); */
/*   gtk_container_add(GTK_CONTAINER(dialog), Bar);   */

/*   // hbox  */
/*   hbox = gtk_hbox_new(FALSE, 0); */
/*   gtk_container_add(GTK_CONTAINER(Bar), hbox); */

/*   // we put buttons in bar  */

/*   for ( i=0 ; i<9 ; i++ )  */
/*   { */
/* /\*   pixmap = gdk_pixmap_create_from_xpm_d(dialog->window, &mask, &c, *\/ */
/* /\* 					note_bar[i]); *\/ */
/* /\*   pixmapwid = gtk_pixmap_new(pixmap, mask); *\/ */
/*        pixmap_wid = gtk_image_new_from_file(note_bar[i]); */
/*        ic_button = gtk_button_new(); */
/*        gtk_container_add(GTK_CONTAINER(ic_button), pixmap_wid); */
/*        gtk_box_pack_start(GTK_BOX(hbox), ic_button, FALSE, FALSE, 0); */
/*   } */


/*   gtk_widget_show_all(dialog); */

/* } */


/* extern void */
/* view_measures_number(gpointer callback_data, guint callback_action, GtkWidget *widget) */
/* { */

/* /\*      if (Score.Staff[get_staff_selected()].View.measures_number == TRUE) *\/ */
/* /\*           Score.Staff[get_staff_selected()].View.measures_number = FALSE; *\/ */
/* /\*      else *\/ */
/* /\*           Score.Staff[get_staff_selected()].View.measures_number = TRUE; *\/ */

/*      refresh(); */

/* } */
