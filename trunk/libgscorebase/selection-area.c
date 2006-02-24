/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * selection.c
 * gscore - a musical notation software
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


#include <glib.h>

#include <libgscore/gscoretypes.h>
#include <libgscorebase/selection-area.h>


extern SelectionArea * gscore_selection_area_new(void);
extern gint            gscore_selection_area_set_active(SelectionArea *selectionarea, gboolean active);
extern gboolean        gscore_selection_area_get_active(SelectionArea *selectionarea);
extern gint            gscore_selection_area_set_x(SelectionArea *selectionarea, gdouble x);
extern gdouble         gscore_selection_area_get_x(SelectionArea *selectionarea);
extern gint            gscore_selection_area_set_y(SelectionArea *selectionarea, gdouble y);
extern gdouble         gscore_selection_area_get_y(SelectionArea *selectionarea);
extern gint            gscore_selection_area_set_width(SelectionArea *selectionarea, gdouble width);
extern gdouble         gscore_selection_area_get_width(SelectionArea *selectionarea);
extern gint            gscore_selection_area_set_height(SelectionArea *selectionarea, gdouble height);
extern gdouble         gscore_selection_area_get_height(SelectionArea *selectionarea);


extern SelectionArea *
gscore_selection_area_new(void)
{

        SelectionArea *selectionarea;

        selectionarea = g_malloc(sizeof(selectionarea));
        if ( ! selectionarea ) {
                g_print("Memory exhausted!\n");
                return NULL;
        }

        gscore_selection_area_set_active(selectionarea, FALSE);
        gscore_selection_area_set_x(selectionarea, 0);
        gscore_selection_area_set_y(selectionarea, 0);
        gscore_selection_area_set_width(selectionarea, 0);
        gscore_selection_area_set_height(selectionarea, 0);

        return selectionarea;
}

extern gint
gscore_selection_area_set_active(SelectionArea *selectionarea, gboolean active)
{
        selectionarea->active = active;

        return 0;
}

extern gboolean
gscore_selection_area_get_active(SelectionArea *selectionarea)
{
        return selectionarea->active;
}

extern gint
gscore_selection_area_set_x(SelectionArea *selectionarea, gdouble x)
{
        selectionarea->x = x;

        return 0;
}

extern gdouble
gscore_selection_area_get_x(SelectionArea *selectionarea)
{
        return selectionarea->x;
}


extern gint
gscore_selection_area_set_y(SelectionArea *selectionarea, gdouble y)
{
        selectionarea->y = y;

        return 0;
}

extern gdouble
gscore_selection_area_get_y(SelectionArea *selectionarea)
{
        return selectionarea->y;
}

extern gint
gscore_selection_area_set_width(SelectionArea *selectionarea, gdouble width)
{
        selectionarea->width = width;

        return 0;
}

extern gdouble
gscore_selection_area_get_width(SelectionArea *selectionarea)
{
        return selectionarea->width;
}

extern gint
gscore_selection_area_set_height(SelectionArea *selectionarea, gdouble height)
{
        selectionarea->height = height;

        return 0;
}

extern gdouble
gscore_selection_area_get_height(SelectionArea *selectionarea)
{
        return selectionarea->height;
}


