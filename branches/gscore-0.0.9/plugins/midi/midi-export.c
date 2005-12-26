/* -*- mode:C; tab-width:8; c-default-style:linux; c-basic-offset:8; indent-tabs-mode:nil -*- */
#include <glib.h>

#include <simili.h>

#include "plugin.h"
#include "gscore.h"

#include "midi-constants.h"
#include "midi-export.h"
 
/* 			mmsg.timestamp = 0; */
			
/* /\* 			MIDI_MSG_CHPROG(&mmsg, chan, staff_data->midi_instrument); *\/ */
/* /\* 			MIDI_MSG_CHAN(&mmsg, chan, staff_data->midi_instrument); *\/ */
/* 			midi_put_msg(midi_out, &mmsg); */

/* 	close_midi(); */
midi_t *midi_out = NULL;

static int track = 0;                 /* track = staff */



static void 
write_note(int chan, int note_type, int note, int velocity)
{
	midi_msg_t mmsg;

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
        Staff_t  *staff = (Staff_t *)user_data; 
        Object_t *object;
	

        gchar *char_from_object = NULL;

        object = (Object_t *) data;

	/* FIXME: Ne pas assumer que les objets sont tous des notes ('spece d'Espie!) */
	write_note(0, object->type, get_note_from_pitch(object->pitch), 127);
}

extern void 
save_file(const gchar *filename, Score_t *score)
{

        GList *listrunner_staves = g_list_first(score->Staff_list);

        Staff_t *staff_data;

        g_print("save_file(%s)\n", filename);

	midi_out = midi_file_create (filename, MIDI_FLAG_PUT | MIDI_FLAG_CREATE);
	if( ! midi_out )
	  goto error;

	midi_file_set_tpqn (midi_out, DEFAULT_TIMESTAMP);

        while (listrunner_staves) {
                        staff_data = (Staff_t *)listrunner_staves->data;

			if ( ! staff_data->Object_list)
				printf("liste nulle\n");

                        g_list_foreach(staff_data->Object_list, midi_export_object, (gpointer) staff_data);

			midi_file_next_track(midi_out);
                        listrunner_staves = g_list_next(listrunner_staves);
	}
        g_list_free(listrunner_staves);
        
	midi_destroy (midi_out);
	return;

 error:
	g_print("Erreur dans midi-export\n");
}



/*         g_print("T:%s\n", score->Identity->title->str); */
/*         g_print("T:%s\n", score->Identity->subtitle->str); */
/*         g_print("A:%s\n", score->Identity->composer->str); */
/*         g_print("Q:%d\n", score->tempo); */
/* 			g_print("V:%d\n", staff_counter); */
/* 			g_print("L:1/4\n"); */
/* 			g_print("K:%s clef=%s\n", get_char_from_key_signature(staff_data->key_signature),  */
/*                                 get_char_from_key(staff_data->key)); */
