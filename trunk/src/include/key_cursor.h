/*
 * cursor.c
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

extern struct KeyCursor_t KeyCursor;

void draw_key_cursor(gint position, gdouble current_x, gdouble extremity_begin_y);
gint get_key_cursor_position(void);

typedef struct KeyCursor_t
{

        gint position;

        gdouble x_returned;
        gdouble y_returned;
/*         gint x_returned; */
/*         gint y_returned; */

} KeyCursor_t;

