/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorebase/object_color.h
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

#ifndef __OBJECT_COLOR_H__
#define __OBJECT_COLOR_H__

#include <libgscore/gscoretypes.h>

G_BEGIN_DECLS

struct _GscoreColor
{

        gdouble red;
        gdouble green;
        gdouble blue;

} _GscoreColor;

struct _ObjectColor
{

        struct _GscoreColor *staves;
        struct _GscoreColor *clefs;
        struct _GscoreColor *objects;

} _ObjectColor;


ObjectColor * gscore_object_color_new(void);

G_END_DECLS

#endif /* __OBJECT_COLOR_H__ */
