/* This is a midi filter plugin */
/* 25/04/2005: on fait marcher le plugin Toady+Fremo*/
#include <glib.h>

/* #include <simili.h> */

#include "plugin.h"
#include "gscore.h"

#include "midi-constants.h"
/* #include "midi-export.h" */

#define API_VERSION 1
#define PLUGIN_TYPE GSCORE_PLUGIN_FILTER

#define PLUGIN_NAME "Midi"
#define PLUGIN_VERSION "1"
#define PLUGIN_SUMMARY "Midi"
#define PLUGIN_DESCRIPTION "Midi plugin filter"
#define PLUGIN_AUTHOR "Sebastien Tricaud <toady@gscore.org>"
#define PLUGIN_HOMEPAGE GSCORE_HOMEPAGE


/* Extensions for the filter */
const gchar *extensions[] = {"mid", NULL};


/* Filter related functions */
gboolean midi_filter_export (Score_t *score,
			       const gchar *filename,
			       void *user_data);
gboolean midi_filter_import (Score_t **score,
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
	plugin->filter->import     = midi_filter_import;
	plugin->filter->export     = midi_filter_export;

	return plugin;
}

/* Functions */
void init(void)
{
	g_print("Initialisation of %s\n", PLUGIN_NAME);
}

void quit(void)
{
	g_print("Quitting %s\n", PLUGIN_NAME);
}

void run(void)
{
	g_print("Running of %s\n", PLUGIN_NAME);
}



/* Filter functions */
gboolean midi_filter_export (Score_t *score,
			       const gchar *filename,
			       void *user_data)
{

/*         save_file(filename, score); */
  g_print("caca midi\n");


	return TRUE;
}

gboolean midi_filter_import (Score_t **score,
			     const gchar *filename,
			     void *user_data)
{

        return TRUE;
}
