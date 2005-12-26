/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorebase/display.h
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

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <libgscore/gscoretypes.h>

G_BEGIN_DECLS

typedef struct _Display
{

        gboolean measure_number;
        gboolean instruments;
        gboolean clefs;
        gboolean score_expressions;
        gboolean barlines;
        gboolean ending_bar;
        gboolean key_signature;
        gboolean time_signature;
        gboolean tempo;

} _Display;

G_END_DECLS

#endif /* __DISPLAY_H__ */
