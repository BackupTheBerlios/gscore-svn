/*
 * realize_area.h
 * gscore - a music score editor
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

#ifndef _DRAW_H_
#define _DRAW_H_


gint draw_cursor(const gchar *xbm_file, const gchar *mask_xbm_file, gint width, gint height);

gint x_space(GList *list, gint index);

gint print_objects(GList *list);

gint draw_note(gchar *file, gboolean selected, gint x, gint y, gint line_x1, gint line_y1,
               gint line_x2, gint line_y2);

gint draw_pixmap(GdkWindow *window, gchar *file, gdouble x, gdouble y);

gint draw_point(gint x, gint y);

gint average(gint staff);

gint index_object(gint staff, gint x);

gint draw_staff(guint16 nb_lines, gdouble space_btwn_line, gdouble x1, gdouble y1, gdouble x2, gboolean line, gboolean selected);

gint draw_eighth_up(gboolean selected, gint x, gint y);

gint draw_eighth_down(gboolean selected, gint x, gint y);

gint draw_sixteenth_up(gboolean selected, gint x, gint y);

gint draw_sixteenth_down(gboolean selected, gint x, gint y);

gint draw_red_rectangle(gint x1, gint y1, gint x2, gint y2);

void draw_tie(gint x, gint y, gint width, gint heigth);

/* void draw_selection(gint x, gint y, gint width, gint height); */

void draw_lines_for_object(gint staff, gboolean above, gint nb_lines, gint x);

gint draw_placement(gint x, gint y);

gint draw_selection(gint x_origin, gint y_origin, gint x, gint y);

/* gboolean white_score(GtkWidget *drawingarea); */

gboolean colorize_drawingarea(GtkWidget *drawingarea, guint red, guint green, guint blue);

void draw_line(gint red, gint green, gint blue, gint x1, gint y1, gint x2, gint y2);

void draw_page_limit(gint x);

void draw_staff_extension(Staff_t *staff, gint position, gdouble x);

#endif
