/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorebase/selection.h
 * gscore - a musical score editor
 *
 * (C) Copyright 2001-2006 Sebastien Tricaud
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

#ifndef __SELECTION_H__
#define __SELECTION_H__

#include <glib.h>
#include <libgscore/gscoretypes.h>

G_BEGIN_DECLS

struct _SelectionArea {
        gboolean active;
        gdouble  x, y;
        gdouble  width;
        gdouble  height;
};

SelectionArea * gscore_selection_area_new(void);
gint            gscore_selection_area_set_active(SelectionArea *selectionarea, gboolean active);
gboolean        gscore_selection_area_get_active(SelectionArea *selectionarea);
gint            gscore_selection_area_set_x(SelectionArea *selectionarea, gdouble x);
gdouble         gscore_selection_area_get_x(SelectionArea *selectionarea);
gint            gscore_selection_area_set_y(SelectionArea *selectionarea, gdouble y);
gdouble         gscore_selection_area_get_y(SelectionArea *selectionarea);
gint            gscore_selection_area_set_width(SelectionArea *selectionarea, gdouble width);
gdouble         gscore_selection_area_get_width(SelectionArea *selectionarea);
gint            gscore_selection_area_set_height(SelectionArea *selectionarea, gdouble height);
gdouble         gscore_selection_area_get_height(SelectionArea *selectionarea);

G_END_DECLS

#endif /* __SELECTION_H__ */
