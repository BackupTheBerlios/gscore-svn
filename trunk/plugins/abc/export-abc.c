/* Export ABC functions */

#include <glib.h>
#include <stdio.h>

#include "../../src/include/plugin.h"
#include "../../src/include/gscore.h"
#include "../../src/include/constants.h"

/* ACCIDENTALS */
#define ABC_SHARP "^"
#define ABC_FLAT "_"
#define ABC_NATURAL "="
#define ABC_DOUBLESHARP "^^"
#define ABC_DOUBLEFLAT "__"

static FILE *savefile;

/* To make the score look nicer, we must go to next line every four staves */
static guint measure_counter = 1;


static void print_in_file(const gchar *s)
{
        fputs(s, savefile);
}

static gchar * get_char_from_key(gint key)
{

     gchar * value = NULL;


     switch(key){
     case NO_KEY: return "empty";
     case TREBLE_KEY: return "treble";
     case BASS_KEY: return "bass";
     case ALTO_KEY: return "alto";
     case TAB_KEY: return "tab";
     default: return "unknown key";
     }

     return "";
}

static gchar* get_char_from_key_signature(gint key_signature)
{

        switch(key_signature)
        {
        case KEY_SIGNATURE_TREBLE_EMPTY:
                return "C";
        case KEY_SIGNATURE_TREBLE_F_SHARP:
                return "G";
        case KEY_SIGNATURE_TREBLE_C_SHARP:
                return "D";
        case KEY_SIGNATURE_TREBLE_G_SHARP:
                return "A";
        case KEY_SIGNATURE_TREBLE_D_SHARP:
                return "E";
        case KEY_SIGNATURE_TREBLE_A_SHARP:
                return "B";
        case KEY_SIGNATURE_TREBLE_E_SHARP:
                return "F#";
        case KEY_SIGNATURE_TREBLE_B_SHARP:
                return "C#";
        case KEY_SIGNATURE_TREBLE_B_FLAT:
                return  "F";
        case KEY_SIGNATURE_TREBLE_E_FLAT:
                return "Bb";
        case KEY_SIGNATURE_TREBLE_A_FLAT:
                return "Eb";
        case KEY_SIGNATURE_TREBLE_D_FLAT:
                return "Ab";
        case KEY_SIGNATURE_TREBLE_G_FLAT:
                return "Db";
        case KEY_SIGNATURE_TREBLE_C_FLAT:
                return "Gb";
        case KEY_SIGNATURE_TREBLE_F_FLAT:
                return "Cb";
        }
        g_warning("Wrong signature\n");
        return "";
  
}

static gchar *get_char_from_accidental(accidentals_e accidentals)
{
        if (accidentals & A_SHARP)
                return ABC_SHARP;
        if (accidentals & A_DOUBLESHARP)
                return ABC_DOUBLESHARP;
        if (accidentals & A_FLAT)
                return ABC_FLAT;
        if (accidentals & A_DOUBLEFLAT)
                return ABC_DOUBLEFLAT;
        if (accidentals & A_NATURAL)
                return ABC_NATURAL;

        g_warning("Unsupported accidental object\n");
        return "";
}

static gchar *get_char_from_beam(gint type, object_e object)
{

        if (object & PO_BEAMED)
                {
                        return "";
                } else {
                        return " ";
                }

        return "";
}

static gchar *get_char_from_pitch(gint key, gint type, gint pitch)
{
        gint offset;
        
        switch(key)
        {
        case TREBLE_KEY:
                offset = 4;
                break;
        default:
             offset = 0;
        }

        switch(type)
        {
        case DOUBLEWHOLE:
        case WHOLE:
        case HALF:
        case QUARTER:
        case EIGHTH:
        case SIXTEENTH:
             switch(pitch+offset)
             {
             case -7: return "C,";
             case -6: return "D,";
             case -5: return "E,";
             case -4: return "F,";
             case -3: return "G,";      
             case -2: return "A,";
             case -1: return "B,";
             case  0: return "C";
             case  1: return "D";
             case  2: return "E";
             case  3: return "F";
             case  4: return "G";
             case  5: return "A";
             case  6: return "B";
             case  7: return "c";
             case  8: return "d";
             case  9: return "e";
             case 10: return "f";
             case 11: return "g";
             case 12: return "a";
             case 13: return "b";
             }
             
        case DOUBLEWHOLEREST:
        case WHOLEREST:
        case HALFREST:
        case QUARTERREST:
        case EIGHTHREST:
        case SIXTEENTHREST:
        case THIRTYSECONDREST:
        case SIXTYFOURTHREST:
             return "z";
        }

        g_warning("wrong position for note\n");
  
        return "";
}

static gchar *get_char_for_duration(const gint value)
{
        switch(value)
        {
        case EIGHTH:     
        case EIGHTHREST:
             return "/";
        case SIXTEENTH:
        case SIXTEENTHREST:
             return "/4";
        case QUARTER:
        case QUARTERREST:
             return "";
        case HALF:
        case HALFREST:
             return "2";
        case WHOLE:
        case WHOLEREST:
             return "4";
        case DOUBLEWHOLE:
        case DOUBLEWHOLEREST:
             return "8";
        }

        g_warning("Unsupported label %d\n", value);
        return "";
}

static gchar *get_char_from_staccato(object_e object)
{
     if (object & PO_STACCATO)
          return ".";
     else
          return "";
}

static void abc_print_object(gpointer data, gpointer user_data)
{
        Object_t *object;

        object = (Object_t *) data;

        switch(object->type){
                /* Barlines */
        case BARLINE_SINGLE:
		if ( measure_counter == 4 ) {
			g_print(" |\n");
			measure_counter = 1;
		} else {
			g_print(" | ");
			measure_counter++;
		}
                break;
        case BARLINE_DOUBLE:
                g_print(" || ");
                break;
        case BARLINE_OPENREPEAT:
                g_print(" |: ");
                break;
        case BARLINE_CLOSEREPEAT:
                g_print(" :| ");
                break;
        default:
                g_print("%s%s%s%s%s",
                        get_char_from_staccato(object->nature),
                        get_char_from_beam(object->type, object->nature),
                        get_char_from_accidental(object->accidentals),
                        get_char_from_pitch((gint) user_data, object->type, object->pitch),
                        get_char_for_duration(object->type));

        }


}

extern void save_file(const gchar *filename, Score_t *score)
{
        GPrintFunc old_handler;

        GList *listrunner_staves = g_list_first(score->Staff_list);
        GList *listrunner_objects;

        Staff_t *staff_data;
        Object_t *object_data;
        gint staff_counter = 0;

        g_print("save_file(%s)\n", filename);

        savefile = fopen(filename, "w");
        old_handler = g_set_print_handler(print_in_file);

        g_print("%% File generated by Gscore ");
        g_print(APP_VERSION);
        g_print("\n%% http://www.gscore.org\n%%\n");

        g_print("X:1\n");
        g_print("T:%s\n", score->Identity->title->str);
        g_print("T:%s\n", score->Identity->subtitle->str);
        g_print("A:%s\n", score->Identity->composer->str);
        g_print("Q:%d\n", score->tempo);

        while (listrunner_staves) {
                        staff_data = (Staff_t *)listrunner_staves->data;

			g_print("%%\n");
			g_print("V:%d\n", staff_counter);
			g_print("L:1/4\n");
			g_print("K:%s\n", get_char_from_key_signature(staff_data->key_signature));

			if ( ! staff_data->Object_list)
				printf("liste nulle\n");

                        g_list_foreach(staff_data->Object_list, abc_print_object, (gpointer) staff_data->key);

                        g_print("\n");

                        staff_counter++;

                        listrunner_staves = g_list_next(listrunner_staves);
	}
        g_list_free(listrunner_staves);
        
/*         g_print("Key: %s\n", get_char_from_key(staff_data->key)); */




/*  = g_list_nth_data(score->Staff_list, 0); */

/*         g_print("X:1\n"); */
/*         g_print("T:%s\n", score->Identity.title); */
/*         if(score->Identity.subtitle) */
/*                 g_print("T:%s\n", score->Identity.subtitle); */
/*         if(score->Identity.composer) */
/*                 g_print("A:%s\n", score->Identity.composer); */
/* 	g_print("Q:%d\n", score->tempo); */

/*         for ( staff = 0; staff < score->nb_staff; staff++) */
/*           { */
/* 			g_print("%%\n"); */
/* 			g_print("V:%d\n", staff); */
/* 			g_print("L:1/4\n"); */
/* 			g_print("K:%s\n", get_key_from_sig(score, staff)); */
/* /\* 			g_list_foreach(score->Staff[staff].Note_list, abc_print_object, (gpointer) score->Staff[staff].key); *\/ */
		
/* 			g_print("\n"); */
/*           } */
	
        g_set_print_handler(old_handler);
        fclose(savefile);
  
}
