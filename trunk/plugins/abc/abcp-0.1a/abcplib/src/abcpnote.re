
#include "abcp.h"

/*
  Note parsing
  
  The following function will return "nominal" characteristics for a note.
  With "nominal", I mean that the real values could depend from other factors.
  
  A note with pitch "b" is actually a "_b" if the key is Fmaj but the function
  abcNoteAccidental("b") always returns "NONE".
  
  Returns the uppercase ASCII representation of the pitch (i.e. 'A'-'G')
  or '?' if no note is found.
  
  Returns an ASCII char representing the accidentals
  n=none, N=natural, f=flat, F=double flat, s=sharp, S=double sharp
  
 The "nominal" Octave of the note (no trasposition is considered)
   0 C,,,,   -> B,,,
   1 C,,,
   2 C,,    -> B,
   3 C,     -> B
   4 C   -> b 
   5 c   -> b'
   6 c'  -> b''
   7 c''
   8 c'''
   9 c'''' -> b'''''
   
   
 and so on. 

  The maximum extension for octaves is 0 .. 9 with the (central C being 4)
  The function manages equalities like: "C' = c" , "A', = A,' = A", ...
  
  This implies that ABCp can handle sounds in the range 16.3Hz .. 15.8MHz,
  
 The "nominal" note length is expressed as a fraction of the
 default length as stated by the L: field
 
 Also microtones are supported in the same form as abcm2ps:
   ^3/4C _/f'
   
 
0123456789012
NEPAONNDDnndd
\\\\\\ \ \ \___ microtone denominator (in hex 00 .. FF)
 \\\\\\ \ \____ microtone mumerator   (in hex 00 .. FF)
  \\\\\\ \_____ length denominator    (in hex 00 .. FF)
   \\\\\\______ length mumerator      (in hex 00 .. FF)
    \\\\\______ octave (see above)
     \\\\______ Accidental n=none, N=natural, f=flat, F=double flat,       
      \\\                  s=sharp S=double sharp
       \\\                 Optional accidentals (e.g. (=) are coded
        \\\                using the following letter:
         \\\               O=opt. natural, g=opt. flat, G=opt. dbl. flat 
          \\\              t=sharp T=double sharp
           \\\___ Pitch 
            \\___ Error
             \___ Type (Note = 'N')

 
 
             
Errors      

1= Pitch not found
2= Octave out of range  0 .. 9
3= Length out of range   0 .. 255
4=
5=
6=
        
*/

/*!re2c

WS=[\040\011];
any=[\000-\377];
D = [0-9];
*/


char * abcNNote(char* pak, char *str)
{
  YYCTYPE *YYCURSOR,*YYLIMIT,*YYMARKER,*YYSTART;
  char c;
  int oct=0;
  int num=1,den=1;
  int t;
  
  if (str==NULL || pak==NULL) return NULL;
    
  YYCURSOR=str; while (isspace(*YYCURSOR)) YYCURSOR++;
  YYLIMIT=str;  while (*YYLIMIT) YYLIMIT++;
  
             /*0123456789012*/
  setpack(pak,"NEPAONNDDnndd");

  
  
  if (*YYCURSOR == 'Z' ||
      *YYCURSOR == 'z' ||
      *YYCURSOR == 'x' ) {
    pak[2]=*YYCURSOR++; 
    goto duration; 
  }
  
  t=0;
  if (*YYCURSOR == '(') {
    t=1;
    YYCURSOR++;
  }
  
accidental: 
   
  /*!re2c
    "__" { t+='F' ; goto pitch;}
    "^^" { t+='S' ; goto pitch;}
    "_"  { t+='f' ; goto mtone;}
    "^"  { t+='s' ; goto mtone;}
    "="  { t+='N' ; goto pitch;}
    any  { YYCURSOR-- ; goto pitch;}
  */

mtone:  
   YYSTART=YYCURSOR;

  /*!re2c
    D+      { num = atoi(YYSTART)          ; goto mtone;}
    [/] D+  { den = atoi(YYSTART+1)        ; goto pitch;}
    [/]+    { den = 1<<(YYCURSOR-YYSTART)  ; goto pitch;}
    any     { YYCURSOR-- ; goto pitch;}
  */
  
  
pitch:
  sethex(pak+9,num);
  sethex(pak+11,den);

  if (*YYCURSOR == ')') YYCURSOR++;
  
  pak[2] = toupper(*YYCURSOR);
  pak[3] = t<2? 'n':t ;
    
  /*!re2c
    [AB]      { oct = 3; goto octave;}
    [CDEFGab] { oct = 4; goto octave;}
    [cdefg]   { oct = 5; goto octave;}
    any       { setperr(pak,1) ; goto gotnote;}
  */

octave:
  /*!re2c
    ['] { oct++      ; goto octave;}
    [,] { oct--      ; goto octave;}
    any { YYCURSOR-- ; goto gotpitch;}
  */

gotpitch:

  if (oct < 0)      { setperr(pak,2); oct = 0; }
  else if (oct > 9) { setperr(pak,2); oct = 9; }
  
  pak[4] = '0' + oct;
  num=1;den=1;
  
duration:
  YYSTART=YYCURSOR;
  
  /*!re2c
    D+      { num = atoi(YYSTART)          ; goto duration;}
    [/] D+  { den = atoi(YYSTART+1)        ; goto gotnote;}
    [/]+    { den = 1<<(YYCURSOR-YYSTART)  ; goto gotnote;}
    any     { goto gotnote;}
  */
    
gotnote:

  sethex(pak+5,num);
  sethex(pak+7,den);

  return pak;
}
