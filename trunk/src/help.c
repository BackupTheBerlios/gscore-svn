/*
 * help.c
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

#include <stdlib.h>
#include <gtk/gtk.h>

#include "gscore.h"
#include "macros.h"


/* void */
/* help_help_callback(gpointer callback_data, guint callback_action, GtkWidget *widget) */
/* { */
/*      const gchar *helpdir;  */
/*      gchar *helpindex = NULL, *command;  */

/*      helpindex = get_file_from_data_dir("doc/index.html"); */

/*      g_print("helpindex = %s\n", helpindex); */
     
/*      command = getenv("BROWSER"); */
/*      command = g_strdup_printf("%s 'file://%s' &", command ? command : "mozilla", helpindex); */
/*      system(command); */

/* } */

void
help_report_bug(gpointer callback_data, guint callback_action, GtkWidget *widget)
{
	GtkWidget *dialog;

	dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL,
					GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
					"Visit http://www.gscore.org/bugs\n\nPlease specify:\n- The version of gscore you are using\n- Your operating system\n- How the bug happens\n- If you can reproduce it\n\nThanks.");
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK)
		gtk_widget_destroy(dialog);
}

