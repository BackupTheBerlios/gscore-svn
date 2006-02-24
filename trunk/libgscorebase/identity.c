/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * libgscorebase/identity.c
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
#include <libgscore/gscoreerrors.h>
#include <libgscorebase/identity.h>

extern Identity * gscore_identity_new(void);

extern Identity *
gscore_identity_new(void)
{

        Identity *identity;

        identity = g_malloc(sizeof(identity));
        if ( ! identity ) {
                g_print("Memory exhausted: cannot allocate new score\n");
                return NULL;
        }

        identity->title     = g_string_new("");
        identity->subtitle  = g_string_new("");
        identity->composer  = g_string_new("");
        identity->copyright = g_string_new("");

        identity->filename  = g_string_new("");


        return identity;

}
