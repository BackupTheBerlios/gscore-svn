/*
 * score.h
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

#ifndef _SCORE_H_
#define _SCORE_H_

#include "key_cursor.h"

void set_tempo(void);

void score_set_tempo (gpointer callback_data, guint callback_action,
                      GtkWidget * widget);

gint score_add_tab (gpointer callback_data, guint callback_action,
                    GtkWidget * widget);

void remove_score (gpointer callback_data, guint callback_action,
	    GtkWidget * widget);

void score2tab (gpointer callback_data, guint callback_action,
		GtkWidget * widget);

void properties (gpointer callback_data, guint callback_action,
	    GtkWidget * widget);

void score_midi_play (gpointer callback_data, guint callback_action,
                      GtkWidget * widget);

void on_set_header_activate_default(void);

void score_set_header_ok(void);

Score_t *score_get_from_widget(GtkWidget *widget);

GtkWidget *score_get_area_from_widget(GtkWidget *widget);

Display_t *score_get_display_from_widget(GtkWidget *widget);

Score_selection_t *score_get_selection_from_widget(GtkWidget *widget);

KeyCursor_t *score_get_cursor_from_widget(GtkWidget *widget);

void score_create_window(Score_t *score);

/*
void keybindings (gpointer callback_data,
		  guint callback_action, GtkWidget * widget);
*/
#endif
