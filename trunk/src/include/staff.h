/*
 * staff.h
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

#ifndef _STAFF_H_
#define _STAFF_H_


gboolean create_staff(guint8 nb_lines, guint8 space_btw_lines,
                      gdouble extremity_begin_x, gdouble extremity_begin_y);

gboolean delete_staff(gint staff);

gint get_staff_selected(void);

gint get_staff_key_signature(guint staff);

gboolean staff_set_key(gint staff, gint key);

void staff_set_key_callback(void);

gint staff_get_key(gint staff);

gboolean staff_set_current_x(gint staff, gint current_x);

gint staff_get_current_x(gint staff);

gdouble get_staff_extremity_begin_x(gint staff);

gdouble get_staff_extremity_begin_y(gint staff);

gboolean staff_set_key_signature(gint staff, gint key_signature);

gboolean staff_set_time_signature(gint staff, gint signature_type, gint number_of_beats, gint beat_duration);

gboolean staff_set_midi_instrument(gint staff, gint midi_instrument);

gint staff_get_y_for_next(void);

gboolean staff_update_statusbar(void);

gboolean staff_set_start_x(gint staff, gint start_x);

gint staff_get_start_x(gint staff);

void staff_key_signature(gpointer callback_data, guint callback_action, GtkWidget *widget);

void staff_time_signature(gpointer callback_data, guint callback_action, GtkWidget *widget);

/* void staff_set_midi_instrument(gpointer callback_data, guint callback_action, GtkWidget *widget); */

void staff_display_measures_numbers(gpointer callback_data, guint callback_action, GtkWidget *widget);

gint get_staff_id(gdouble y);

void deselect_all_staffs(void);

void set_staff_selected(gint staff);

void set_staff_unselect(gint staff);

gint staff_remove_staff(gpointer callback_data, guint callback_action, GtkWidget *widget);

gint get_staff_key(gint staff);

void test_remove(void);

void staff_add_staff (gpointer callback_data, guint callback_action, GtkWidget * widget);

gdouble get_staff_extremity_end_y(gint staff_id);

#endif
