/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscore/gscoretypes.h
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

#ifndef __GSCORETYPES_H__
#define __GSCORETYPES_H__

G_BEGIN_DECLS

/* In libgscorebase/score.h: */
typedef struct _Score Score;

/* In libgscorebase/identity.h */
typedef struct _Identity Identity;

/* In libgscorebase/object-color.h */
typedef struct _ObjectColor ObjectColor;

/* In libgscorebase/staff.h */
typedef struct _Staff Staff;

/* In libgscorebase/object.h */
typedef struct _Object Object;

/* In libgscorebase/display.h */
typedef struct _Display Display;

/* In libgscorebase/selection.h */
typedef struct _SelectionArea SelectionArea;

/* In libgscorespacings/spacings.h */
typedef struct _Spacings Spacings;

G_END_DECLS

#endif /* __GSCORETYPES_H__ */
