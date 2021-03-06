/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
/*
 * glade.c
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

#include <glade/glade.h>
#include <libgscore/gscoreerrors.h>

#include "include/glade.h"
#include "include/gettext.h"

static GladeXML *gxml;

extern GSCORE_ERROR gxml_create(char *filename);


extern GSCORE_ERROR
gxml_create(char *filename)
{

	gxml = glade_xml_new(filename, NULL, NULL);
	
	if ( ! gxml ) {
		g_error(_("Glade file not found in %s\n"), filename);
		
		return GSCORE_FILENOTFOUND;
	}
	

	glade_xml_signal_autoconnect(gxml);

	return GSCORE_NOERR;

}
