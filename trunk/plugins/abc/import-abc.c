#include <glib.h>
#include "import-abc.h"

#include "abcp.h"

static Score_t *theScore;

/* Function called whenever a token is found */
int my_handler(abcHandle h)
{
  abcScanner *scan = (abcScanner *) h;
  int t;
  char *s;
  char *f;
  USHORT l;
  USHORT c;
  char *x;
  char*y;
  
  t=abcToken(scan);
  s=abcString(scan);
  f=abcFilename(scan);
  l=abcLine(scan);
  c=abcColumn(scan);
  x=abcStateName(abcState(scan));

/*   g_printf("%s %03d,%03d:%s %s\n",x,l,c,abcTokenName(t),s); */


  switch(t)
    {
    case T_FIELDB:
/*     case T_TEXT: */
      g_printf("Comment: '%s'\n", abcString(h));
      y=abcParsedString(h);
      if (*y && *y != '?') printf("%s\n",y); 
      break;
    default:
      g_printf("%s ", abcTokenName(t));
      break;
    }
  
  
    

  return 0;
  
}


extern gboolean abc_load_file(const gchar *filename,
			  Score_t **score)
{
  g_printf("Calling abc_load_file('%s')\n", filename);
  

  theScore = *score;
  
  g_printf("Before abcScanFile\n");
  abcScanFile((char *) filename, my_handler);
  g_printf("After abcScanFile\n");
  
  return TRUE;
}

