/* This is a simple filter plugin */

#include <glib.h>

#include "plugin.h"
#include "gscore.h"
#include "macros.h"

#define API_VERSION 1
#define PLUGIN_TYPE GSCORE_PLUGIN_FILTER

#define PLUGIN_NAME "Simple"
#define PLUGIN_VERSION "1"
#define PLUGIN_SUMMARY "Simple as simple"
#define PLUGIN_DESCRIPTION "Simple plugin for understanding how to write a plugin"
#define PLUGIN_AUTHOR "Sebastien Tricaud <toady@gscore.org>"
#define PLUGIN_HOMEPAGE GSCORE_HOMEPAGE


/* Extensions for the filter */
const gchar *extensions[] = {"smp","simple", NULL};


/* Filter related functions */
gboolean simple_filter_export (Score_t *score,
			       const gchar *filename,
			       void *user_data);
gboolean simple_filter_import (Score_t **score,
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
	plugin->filter->import     = simple_filter_import;
	plugin->filter->export     = simple_filter_export;

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
gboolean simple_filter_export (Score_t *score,
			       const gchar *filename,
			       void *user_data)
{
        Staff_t *staff_data;
        GList *listrunner;


	g_print("Export function called for %s\n", PLUGIN_NAME);
	g_print("Saving %s\n", filename);

        /* Just to show that we get the tempo from the score from gscore */
        g_print("Tempo: %d\n", score->tempo);

	g_print("Other objects...\n");
	

        staff_data = g_list_nth_data(score->Staff_list, 0);
        listrunner = g_list_first(staff_data->Object_list);
        while (listrunner)
                {
                        Object_t *object_data;

                        object_data = (Object_t *)listrunner->data;

                        printf("Object->id = %d\n", object_data->id);
                        printf("Object->type = %d\n", object_data->type);
                        printf("Object->nature = %d\n", object_data->nature);
                        printf("Object->accidentals = %d\n", object_data->accidentals);
                        printf("Object->x = %d\n", object_data->x);
                        printf("Object->y = %d\n", object_data->y);
                        printf("Object->x2 = %d\n", object_data->x2);
                        printf("Object->y2 = %d\n", object_data->y2);
                        printf("Object->x3 = %d\n", object_data->x3);
                        printf("Object->y3 = %d\n", object_data->y3);
                        printf("Object->pitch = %d\n", object_data->pitch);
                        printf("Object->tab_number = %d\n", object_data->tab_number);
                        printf("Object->is_selected = %d\n", object_data->is_selected);

                        listrunner = g_list_next(listrunner);
                }

        g_list_free(listrunner);



	return TRUE;
}

gboolean simple_filter_import (Score_t **score,
			       const gchar *filename,
			       void *user_data)
{
        Score_t *spi;
        GladeXML *gladexml;

        g_print("Import function called for %s\n", PLUGIN_NAME);
	g_print("Loading %s\n", filename);


	gladexml = glade_xml_new(get_file_from_data_dir("glade/gscore.glade"), NULL, NULL);


        /* The following sets the tempo for the score */
        GSCORE_PLUGIN_STRUCT_INIT(spi);

        spi->area = glade_xml_get_widget (gladexml, "sw_score_da");
        spi->Staff_list = NULL;
        spi->staff_extremity_end_x = 0;
        spi->tempo = 10;

        /* We give the structure to the pointer */
        /* I believe it's cleaner this way. Now it's up to you */
        GSCORE_PLUGIN_STRUCT_INIT(*score);
        *score = spi;

	return TRUE;
}
