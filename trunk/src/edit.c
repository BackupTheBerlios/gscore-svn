/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * edit.c
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

#include "edit.h"
#include "constants.h"
#include "common.h"
#include "gscore.h"
#include "position.h"


void edit_undo(void)
{
     
}

/* extern void  */
/* edit_cut(void) */
/* { */
/*      GList *listrunner; */
/*      gint i; */
/*      gboolean something_selected = FALSE; */

/*      listrunner = g_list_first(Score.Staff[Score.staff_selected].Note_list); */
     
/*      while (listrunner) */
/*      { */
/* 	     Note_t *note; */
	     
/* 	     note = (Note_t *)listrunner->data; */
	     
/* 	     if (note->selected) */
/* 	     { */

/* 		     something_selected = TRUE; */

/* /\* 		     Clipboard.note_list = g_malloc(sizeof(Note_t)); *\/ */
		     
/* /\* 		     Clipboard.Note_list = g_list_append(Clipboard.Note_list,  *\/ */
/* /\* 							 note); *\/ */

/* /\*   *\/ */
/* 		     Score.Staff[Score.staff_selected].current_x -= get_spacing_for_object(note->type); */

/* /\* 		     Score.Staff[Score.staff_selected].Note_list = g_list_remove_all(Score.Staff[Score.staff_selected].Note_list, (Note_t *)note); *\/ */
		     	     
/* 	     } */
	     
/* 	     listrunner = g_list_next(listrunner); */
/*      } */

/*      g_list_free(listrunner); */

/*      if (something_selected) */
/*           refresh(); */
/*      else */
/*           gw_message_info(_("You should select something if you want to cut")); */

/* } */

/* void */
/* edit_go_to_measure(gpointer callback_data, guint callback_action, GtkWidget *widget) */
/* { */
/*      GtkWidget * dialog; */
/*      GtkWidget * spinbutton; */

/*      GtkAdjustment * adj; */
     
          
/*      dialog = gtk_dialog_new_with_buttons(_("Go to measure"), NULL, */
/*                                           GTK_DIALOG_MODAL, */
/*                                           GTK_STOCK_CANCEL, GTK_RESPONSE_REJECT, */
/*                                           GTK_STOCK_OK, GTK_RESPONSE_ACCEPT, */
/*                                           NULL); */
     
/*      g_signal_connect(G_CALLBACK(dialog), "destroy", */
/*                       G_CALLBACK(gtk_widget_destroyed), */
/*                       &dialog); */
     

/*      adj = GTK_ADJUSTMENT(gtk_adjustment_new(Score.Staff[get_staff_selected()].measure_number, */
/*                                              1, Score.Staff[get_staff_selected()].total_measures, */
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

/* } */

