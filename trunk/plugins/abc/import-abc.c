#include <glib.h>
#include <glib/gprintf.h>

#include <staff.h>
#include <objects.h>

#include "import-abc.h"

#include "abcp.h"

static Score_t *theScore;

static const char *pitch_string = "CDEFGABcdefgab";

typedef struct 
{
  gint nomin;
  gint denom;
} duration_t;

static duration_t base_note;

typedef struct 
{
  gint pitch;
  duration_t duration;
} note_t;

static note_t *parse_note(char *string)
{
  static note_t the_note;
  int pitch;
  int i;

  /* Determine the note pitch */
  pitch = strchr(pitch_string, string[0]) - pitch_string;
  for(i=1; string[i] == '\''; ++i){
    pitch+=8;
  }
  for(i=1; string[i]==','; ++i) {
    pitch-=8;
  }
  /* Determine the note duration */

  /* Return result */
  the_note.pitch = pitch;
  the_note.duration.nomin = 1;	/* FIXME */
  the_note.duration.denom = 1;	/* FIXME */

  return &the_note;
}


/** Function called whenever a token is found */
int my_handler(abcHandle h)
{
  abcScanner *scan = (abcScanner *) h;
  int t;
  char *s;
/*   char *f; */
  USHORT l;
  USHORT c;
  char *x;
  char*y;
  static gint numStaff;
  static gint numTitle;
  note_t *the_note;
  
  t=abcToken(scan);
  s= (char*) abcString(scan);
/*   f=abcFilename(scan); */
  l=abcLine(scan);
  c=abcColumn(scan);
  x= (char*) abcStateName(abcState(scan));

  switch(t)
    {
    case T_FIELDB:
/*     case T_TEXT: */
/*       g_printf("Field: '%s'\n", abcString(h)); */
/*       g_printf("String : '%s'\n", s); */
/*       g_printf("State : '%s'\n", x); */

      if(strcmp(x, "S_FIELD_X")==0) {
	numTitle = 0;
	numStaff = -1;
      }else if(strcmp(x,"S_FIELD_T")==0) {
	switch(numTitle) 
	  {
	  case 0:
	    theScore->Identity->title = g_string_new((gchar*) s);
	    ++numTitle;
	    theScore->windows_title = g_strdup((gchar*)s);
	    
	    g_printf("Title : %s\n", s);
	    break;
	  case 1:
	    theScore->Identity->subtitle = g_string_new((gchar*) s);
	    ++numTitle;
	    g_printf("Subtitle %s\n", s);
	    break;
	  default:
	    theScore->Identity->subtitle = 
	      g_string_append(theScore->Identity->subtitle,"\n");
	    theScore->Identity->subtitle = 
	      g_string_append(theScore->Identity->subtitle,s);
	    
	  }
      } else if(strcmp(x, "S_FIELD_C")==0) {
	theScore->Identity->composer = g_string_new((gchar *) s);
	g_printf("Composer : %s\n", s);
      } else if(strcmp(x,"S_FIELD_V")==0) {
/* 	create_staff(5, 0,0,0); */
	/* Copy/Paste from staff.c */
	/* FIXME: we should find a better way to create objects */
	theScore->Staff = g_malloc(sizeof(Staff_t));
	theScore->Staff->nb_lines= 5;
	theScore->Staff->space_btw_lines = 0;
        theScore->Staff->is_selected = FALSE;
        theScore->Staff->key = NO_KEY;
        theScore->Staff->key_signature = KEY_SIGNATURE_EMPTY;
        theScore->Staff->time_signature[0] = TIME_SIGNATURE_NORMAL;
        theScore->Staff->time_signature[1] = 4;
        theScore->Staff->time_signature[2] = 4;
        theScore->Staff->measure_number = 1;
        theScore->Staff->total_measures = theScore->Staff->measure_number;
        theScore->Staff->extremity_begin_x = 0;
        theScore->Staff->extremity_begin_y = 0;
        theScore->Staff->midi_instrument = MIDI_GRAND_PIANO;
        theScore->Staff->Object_list = NULL;

	theScore->Staff_list = g_list_append(theScore->Staff_list,
					     theScore->Staff);

	g_printf("Voice: %s\n", s);
	++numStaff;
      } else {
	g_printf("Other field : %s\n",x);
      }
      
      y=abcParsedString(h);
      if (*y && *y != '?') printf("%s\n",y); 
      break;
    case T_NOTE:
      the_note = parse_note(s);
/*       add_object(numStaff,HALF, 0, 0, 0,0,0,0,0,0,0,the_note->pitch,0,FALSE); */
      /* FIXME: Use generic function when one is available */
      theScore->Staff->Object = g_malloc(sizeof(Object_t));
      theScore->Staff->Object->id= ++theScore->object_id;
      theScore->Staff->Object->type = HALF; /* TODO: Calculate the real value */
      theScore->Staff->Object->nature = 0;
      theScore->Staff->Object->accidentals = 0;
      theScore->Staff->Object->group_id = 0;
      theScore->Staff->Object->is_selected = FALSE;

      theScore->Staff->Object_list = g_list_append(theScore->Staff->Object_list,
						   theScore->Staff->Object);
      theScore->staff_extremity_end_x += object_get_spacing(HALF);
      
      
      g_print("Note: %s\n", s);
      break;
      
    default:
      g_printf("%s ", abcTokenName(t));
      break;
    }

  return 0;
  
}


extern gboolean abc_load_file(const gchar *filename,
			  Score_t *score)
{
  g_printf("Calling abc_load_file('%s')\n", filename);
  

  theScore = score;
  base_note.nomin = 1;
  base_note.denom = 8;
  
  g_printf("Before abcScanFile\n");
  theScore->Identity->filename = g_string_new((gchar *) filename);
  theScore->Staff_list = NULL;
  theScore->tempo_text = g_string_new("");
  theScore->nb_staves = 0;
  
  abcScanFile((char *) filename, my_handler);
  g_printf("After abcScanFile\n");
  
  return TRUE;
}

