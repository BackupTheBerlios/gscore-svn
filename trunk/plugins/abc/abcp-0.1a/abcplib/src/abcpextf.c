#include "abcp.h"

/*
-- BEGIN
  -none
     2F01 begintext
     2F02 endtext
     2F03 newpage
     2F04 vskip
  
  -<ABCString>
     2E01 center
     2E02 text
     2E03 abc-copyright
     2E04 abc-version  
     2E05 abc-creator  
     2E06 abc-charset  
     2E07 abc-include  
     2E08 abc-edited-by
        
  -<fontname> <size>
     2D01 annotationfont
     2D02 composerfont
     2D03 gchordfont
     2D04 infofont
     2D06 partsfont
     2D07 subtitlefont
     2D08 setfont-1
     2D09 setfont-2
     2D0A setfont-3
     2D0B setfont-4
     2D0C tempofont
     2D0D textfont
     2D0E titlefont
     2D0F vocalfont
     2D10 wordsfont
     
  -<length>
     2C01 botmargin
     2C02 composerspace
     2C03 indent
     2C04 infospace
     2C06 leftmargin
     2C07 musicspace
     2C08 pageheight
     2C09 pagewidth
     2C0A partsspace
     2C0B rightmargin
     2C0C staffsep
     2C0D subtitlespace
     2C0E sysstaffsep
     2C0F textspace
     2C10 titlespace
     2C11 topmargin
     2C12 topspace
     2C13 vocalspace
     2C14 wordsspace
  
  -<logical>
     2B01 continueall
     2B02 exprabove
     2B03 exprbelow
     2B04 freegchord
     2B05 musiconly
     2B06 measurebox
     2B07 graceslurs
     2B08 infoline
     2B09 landscape
     2B0A oneperpage
     2B0B printtempo
     2B0C stretchlast
     2B0D stretchstaff
     2B0E vocalabove
     2B0F withxrefs
     2B10 writehistory
       
  -<number>
     2A01 lineskipfac
     2A02 maxshrink
     2A03 parskipfac
     2A04 sep
     2A05 scale
       
  -<integer>
     2901 barnumbers
     2902 barsperstaff
     2903 measurefirst
     2904 measurenb
     2905 setbarnb
        
  -<mix>
     2880 MIDI midi
     
          - A<num>|<lenght>x<length>
     2881 papersize 
     
          - not|octave|pitch
     2882 propagate-accidentals
     
          - <voice-id1> <voice-id2>...<voice-idn>
     2883 score staves
     
          - none|added|all
     2884 writeout-accidentals
     
     2885 deco
     
     2886 postscript
-- END

*/  

#include "abcpextf.h"

int getextfield (YYCTYPE **str)
{   int m=0, d=1;

  YYCTYPE *YYCURSOR = *str;
  YYCTYPE *YYSTART;
  YYCTYPE c;
   
  skipspace(YYCURSOR);
  YYSTART=YYCURSOR;
  
  while (*YYCURSOR && !isspace(*YYCURSOR))
   YYCURSOR++;
  
  c=*YYCURSOR;
  *YYCURSOR='\0';
  
  m=code(YYSTART);
  d=shash(YYSTART);
  *YYCURSOR=c;
  
  if (d == (m & 0xFFFF)) {
    *str=YYCURSOR;
    return (m >> 16);
  }
  
  return 0;
}

