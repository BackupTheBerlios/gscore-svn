/* This is a midi filter plugin */

#include <glib.h>

#include <simili.h>

#include "plugin.h"
#include "gscore.h"

#include "midi-constants.h"

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

midi_t *midi_out;
midi_msg_t mmsg;
int chan = 0;                 /* chan = staff */

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

void open_midi(const gchar *filename)
{

	if (!(midi_out = midi_file_create (filename, MIDI_FLAG_PUT | MIDI_FLAG_CREATE)))
/* 		gw_message_error(_("Cannot save the file")); */

	/* Set the default Timestamp for a quarter */
	midi_file_set_tpqn (midi_out, DEFAULT_TIMESTAMP);
}

void write_note(int chan, int note_type, int note, int velocity)
{

	MIDI_MSG_NOTE_ON(&mmsg, chan, note, velocity);


	if (midi_put_msg (midi_out, &mmsg) < 0)
		{
			printf ("midi_put_msg return -1\n");
		}

	switch (note_type)
		{
		case DOUBLEWHOLE:
			mmsg.timestamp += DOUBLEWHOLE_TIMESTAMP;
			break;
		case WHOLE:
			mmsg.timestamp += WHOLE_TIMESTAMP;
			break;
		case HALF:
			mmsg.timestamp += HALF_TIMESTAMP;
			break;
		case QUARTER:
			mmsg.timestamp += QUARTER_TIMESTAMP;
			break;
		case EIGHTH:
			mmsg.timestamp += EIGHTH_TIMESTAMP;
			break;
		case SIXTEENTH:
			mmsg.timestamp += SIXTEENTH_TIMESTAMP;
			break;
		default:
			mmsg.timestamp += DEFAULT_TIMESTAMP;
		}

	MIDI_MSG_NOTE_OFF(&mmsg, chan, note, velocity);

	if (midi_put_msg (midi_out, &mmsg) < 0)
		{
			printf ("midi_put_msg return -1\n");
		}
}

void close_midi(void)
{
  midi_destroy (midi_out);
}


static int get_note_from_pitch(int pitch)
{
	switch (pitch)
		{
		case -7: return G4;
		case -6: return A4;
		case -5: return B4;
		case -4: return C5;
		case -3: return D5;
		case -2: return E5;
		case -1: return F5;
		case 0: return G5;
		case 1: return A5;
		case 2: return B5;
		case 3: return C6;
		case 4: return D6;
		case 5: return E6;
		case 6: return F6;
		case 7: return G6;
		case 8: return A6;
		case 9: return B6;
		case 10: return C7;
		case 11: return D7;
		case 12: return E7;
		case 13: return F7;
		case 14: return G7;
		case 15: return A7;
		}
}

static void midi_export_object(gpointer data, gpointer user_data)
{
        Object_t *object;

        object = (Object_t *) data;

	write_note(chan, object->type, get_note_from_pitch(object->pitch), VELOCITY);

}

/* Filter functions */
gboolean midi_filter_export (Score_t *score,
			       const gchar *filename,
			       void *user_data)
{
/*         Staff_t *staff_data; */
/*         GList *listrunner; */


/* 	g_print("Export function called for %s\n", PLUGIN_NAME); */
/* 	g_print("Saving %s\n", filename); */

/*         /\* Just to show that we get the tempo from the score from gscore *\/ */
/*         g_print("Tempo: %d\n", score->tempo); */

/* 	g_print("Other objects...\n"); */
	

/*         staff_data = g_list_nth_data(score->Staff_list, 0); */
/*         listrunner = g_list_first(staff_data->Object_list); */
/*         while (listrunner) */
/*                 { */
/* /\*                         Object_t *object_data; *\/ */

/* /\*                         object_data = (Object_t *)listrunner->data; *\/ */

/* 			mmsg.timestamp = 0; */
			
/* /\* 			MIDI_MSG_CHPROG(&mmsg, chan, staff_data->midi_instrument); *\/ */
/* /\* 			MIDI_MSG_CHAN(&mmsg, chan, staff_data->midi_instrument); *\/ */
/* 			midi_put_msg(midi_out, &mmsg); */
			
/* 			g_list_foreach(staff_data->Object_list, midi_export_object, (gpointer) staff_data->key); */
/* 			chan++; */

/* /\*                         printf("Object->id = %d\n", object_data->id); *\/ */
/* /\*                         printf("Object->type = %d\n", object_data->type); *\/ */
/* /\*                         printf("Object->nature = %d\n", object_data->nature); *\/ */
/* /\*                         printf("Object->accidentals = %d\n", object_data->accidentals); *\/ */
/* /\*                         printf("Object->x = %d\n", object_data->x); *\/ */
/* /\*                         printf("Object->y = %d\n", object_data->y); *\/ */
/* /\*                         printf("Object->x2 = %d\n", object_data->x2); *\/ */
/* /\*                         printf("Object->y2 = %d\n", object_data->y2); *\/ */
/* /\*                         printf("Object->x3 = %d\n", object_data->x3); *\/ */
/* /\*                         printf("Object->y3 = %d\n", object_data->y3); *\/ */
/* /\*                         printf("Object->pitch = %d\n", object_data->pitch); *\/ */
/* /\*                         printf("Object->tab_number = %d\n", object_data->tab_number); *\/ */
/* /\*                         printf("Object->is_selected = %d\n", object_data->is_selected); *\/ */

/*                         listrunner = g_list_next(listrunner); */
/*                 } */

/*         g_list_free(listrunner); */

/* 	close_midi(); */

	return TRUE;
}

gboolean midi_filter_import (Score_t **score,
			       const gchar *filename,
			       void *user_data)
{
        Score_t *spi;

        midi_t *midi;

        int nb_tracks;
        int tempo;

        g_print("Import function called for %s\n", PLUGIN_NAME);
	g_print("Loading %s\n", filename);

        /* The following sets the tempo for the score */
        GSCORE_PLUGIN_STRUCT_INIT(spi);

/*         spi->tempo = 10; */
        midi = midi_file_create(filename, MIDI_FLAG_GET);

        nb_tracks = midi_file_get_nb_tracks(midi);


        while ( midi_get_msg(midi, &mmsg) >= 0 ) {
                if(MIDI_MSG_EOF (&mmsg)) break;
                if(MIDI_MSG_EOT (&mmsg)) break;
                if(MIDI_MSG_NULL (&mmsg)) break;

                switch(MIDI_MSG_TYPE(&mmsg)) {
                case MIDI_SYSTEM:
                        switch(MIDI_MSG_STATUS(&mmsg)) {
                        case MIDI_SYS_META:
                                switch(MIDI_MSG_DATA1(&mmsg)) {
                                case MIDI_SYS_META_TEMPO:
                                        tempo = MIDI_MSG_TEMPO(&mmsg);
                                        printf("Tempo = %d\n", tempo);
                                        break;
                                }
                                break;
                        }
                        break;
                case MIDI_NOTE_ON:
                        printf("Note_on: %d", MIDI_MSG_NOTE(&mmsg));
                        break;
                }

        }

        


        /* We give the structure to the pointer */
        /* I believe it's cleaner this way. Now it's up to you */
        GSCORE_PLUGIN_STRUCT_INIT(*score);
        *score = spi;

	return TRUE;
}
