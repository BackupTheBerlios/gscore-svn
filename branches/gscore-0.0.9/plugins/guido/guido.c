/*
 * guido.c
 * plugin to read/write guido music
 *
 * (C) Copyright 2005 Sebastien Tricaud
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
 *
*/


#include <glib.h>

#include "plugin.h"
#include "gscore.h"

#define API_VERSION 1
#define PLUGIN_TYPE GSCORE_PLUGIN_FILTER

#define PLUGIN_NAME "GUIDO"
#define PLUGIN_VERSION "1"
#define PLUGIN_SUMMARY "GUIDO"
#define PLUGIN_DESCRIPTION "Import/Export GUIDO Music"
#define PLUGIN_AUTHOR "Sebastien Tricaud <toady@gscore.org>"
#define PLUGIN_HOMEPAGE GSCORE_HOMEPAGE


/* Extensions for the filter */
const gchar *extensions[] = {"gmn", NULL};


/* Filter related functions */
gboolean guido_filter_export (Score_t *score,
                              const gchar *filename,
                              void *user_data);
gboolean guido_filter_import (Score_t **score,
                              const gchar *filename,
                              void *user_data);
/* Plugin multi-purpose functions */
void init(void);		/* When gscore application initialy starts up */
void quit(void);		/* When gscore application exits */
void run (void);		/* To run anything everytime the plugin is called */


/* The main function */
GscorePlugin *
gscore_plugin_init(void)
{
	GscorePlugin *plugin;


	/* Some memory allocations */
	GSCORE_PLUGIN_INIT(plugin);

	plugin->info->api_version = API_VERSION;
	plugin->info->type        = PLUGIN_TYPE;
	plugin->info->priority    = GSCORE_PRIORITY_DEFAULT;
	plugin->info->name        = PLUGIN_NAME;
	plugin->info->version     = PLUGIN_VERSION;
	plugin->info->summary     = PLUGIN_SUMMARY;
	plugin->info->description = PLUGIN_DESCRIPTION;
	plugin->info->author      = PLUGIN_AUTHOR;
	plugin->info->homepage    = PLUGIN_HOMEPAGE;

	plugin->init_proc   = init;
	plugin->quit_proc   = quit;
	plugin->run_proc    = run;

	plugin->filter->extensions = extensions;
	plugin->filter->import     = guido_filter_import;
	plugin->filter->export     = guido_filter_export;

	return plugin;
}


/* Functions */
void init(void)
{
	g_print("Initializing %s\n", PLUGIN_NAME);
}

void quit(void)
{
	g_print("Quitting %s\n", PLUGIN_NAME);
}

void run(void)
{
	g_print("Running %s\n", PLUGIN_NAME);
}

/* Filter functions */
gboolean guido_filter_export (Score_t *score,
                              const gchar *filename,
                              void *user_data)
{
	return TRUE;
}

gboolean guido_filter_import (Score_t **score,
                              const gchar *filename,
                              void *user_data)
{
        g_print("Import function called for %s\n", PLUGIN_NAME);
	g_print("Loading %s\n", filename);

}
