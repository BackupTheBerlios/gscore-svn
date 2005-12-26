
#include "abcp.h"


/*

-- BEGIN  

  240 none
  24F perc drum
  241 french frenchviolin
  242 violin
  251 soprano
  252 mezzo mezzosoprano
  254 tenor
  255 baritone
  265 subbass

  E4A treble
  E5A alto
  E6A bass

  34C +22
  34D +15
  34E +8
  350 -8
  351 -15
  352 -22

  F01 clef
  F02 o octave
  F03 t transpose
  F04 s stafflines                        
  F05 m middle
  F06 stem stems
  F07 gstem gstems
  F08 name nm
  F09 subname shortname snm
  
-- END

*/



/*
  Key
  01234567890
  KETMabcdefg
  ||\\\_______ explicit accidentals (nNfFsS)
  |  \\_______ Mode (see table below)
  K   \_______ Tonic [A-G]  P (HP), p (Hp) Z (none)
    
  M Major          
  m Minor          
  X Mix            
  D Dor            
  P Phr            
  L Lyd            
  l Loc            
  I Ion            
  A Aeo
  E Explicit

Tonic use the following coding as notes:

n abcdefg 
f ijklmno
s qrstuvw
N ABCDEFG
F IJKLMNO
S QRSTUVW

Errors      

1= Missing Tonic
2= Unknown mode
3= 
4=
5=
6= Syntax error
        
 Clef:
 012345678901234567
 CENOTTLMMDNNnnSSss
 ||\\\ \\ \\   \________ subname length
 C  \\\ \\ \\___________ name length
     \\\ \\ \___________ stem direction 0100 ggss  01=auto; 10=up; 11=down;
      \\\ \\____________ Middle (pitch and octave on the middle line [A-G] default B)
       \\\ \____________ Staff lines (0 .. 9)
        \\\_____________ Semitones transpose (-128 .. +127)
         \\_____________ Octave transpose 'O'=0
          \_____________ clef name + center line
                           40 none         (none)
                           4F percussion   (perc)
                           4F perc         (perc)
                           41 frenchviolin (treble1)
                           41 french       (treble1)
                           4A violin       (treble)
                           4A treble       (treble)
                           51 soprano      (alto1)
                           52 mezzosoprano (alto2)
                           5A alto         (alto)
                           54 tenor        (alto4)
                           55 baritone     (alto5)
                           6A bass         (bass)
                           65 subbass      (bass5)

                                        line
                           treble  0100 xxxx
                           alto    0101 xxxx
                           bass    0110 xxxx

If line is 0 the clef is invisible (i.e. "none" is "treble0").
if line is A (10) no line value has been specified

Staff lines
  The parser handles up to 9 staff lines numbered from 1
to 9, the position of the clef and/or the the "middle=" 
parameters determine the note on each line.


*/


/*!re2c

WS=[\040\011\012\015];
any=[\000-\377];
NS = any\WS;
DQS = ["] (any\["]) ["];
SQS = ['] (any\[']) ['];
D = [0-9];
H = [0-9A-Fa-f];
SIGN=[\053\055];

a = [aA];
b = [bB];
c = [cC];
d = [dD];
e = [eE];
f = [fF];
g = [gG];
h = [hH];
i = [iI];
j = [jJ];
k = [kK];
l = [lL];
m = [mM];
n = [nN];
o = [oO];
p = [pP];
q = [qQ];
r = [rR];
s = [sS];
t = [tT];
u = [uU];
v = [vV];
w = [wW];
x = [xX];
y = [yY];
z = [zZ];

NOTE = [ABCDEFGabcdefg];

*/

static char *clef(char *pak, char *str,int off)
{
  int m=0; int d=1;
  char *t; char c;
  
  YYCTYPE *YYCURSOR,*YYLIMIT,*YYMARKER,*YYSTART;

  if (str==NULL || pak==NULL) return NULL;
  
  YYCURSOR=str; while (isspace(*YYCURSOR)) YYCURSOR++;
  YYLIMIT=str;  while (*YYLIMIT) YYLIMIT++;
  
               /*012345678901234567*/
  /*setpack(pak,"CENOTTLMMDNNnnSSss");*/
   pak[0]='C';
   pak[1]='@';
   
clef:  
  /*!re2c
    WS+ { goto clef; }
    
    "clef" WS* "="? WS* [CGFcgf]?
                         { switch (YYCURSOR[-1]) {
                             case 'G': case 'g': pak[2]= 0x4A; break;
                             case 'C': case 'c': pak[2]= 0x5A; break;
                             case 'F': case 'f': pak[2]= 0x6A; break;
                           }
                           goto clef;
                         }
    
    "none"               { pak[2] = 0x40; goto clef; }
    "perc" | "drum"      { pak[2] = 0x4F; goto clef; }
    "french" "violin"?   { pak[2] = 0x41; goto clef; }
    "violin"             { pak[2] = 0x42; goto clef; }
    "soprano"            { pak[2] = 0x51; goto clef; }
    "mezzo" "soprano"?   { pak[2] = 0x52; goto clef; }
    "tenor"              { pak[2] = 0x54; goto clef; }
    "baritone"           { pak[2] = 0x55; goto clef; }
    "subbass"            { pak[2] = 0x65; goto clef; }

    "treble"             { pak[2] = 0x4A; goto clef; }
    "alto"               { pak[2] = 0x5A; goto clef; }
    "bass"               { pak[2] = 0x6A; goto clef; }
                        
    "treble" D           { pak[2] = YYCURSOR[-1] + 0x10; goto clef; }
    "alto" D             { pak[2] = YYCURSOR[-1] + 0x20; goto clef; }
    "bass" D             { pak[2] = YYCURSOR[-1] + 0x30; goto clef; }

    "+22"                { pak[3] = 'O'+3; goto clef; }
    "+15"                { pak[3] = 'O'+2; goto clef; }
    "+8"                 { pak[3] = 'O'+1; goto clef; }
    "-8"                 { pak[3] = 'O'-1; goto clef; }
    "-15"                { pak[3] = 'O'-2; goto clef; }
    "-22"                { pak[3] = 'O'-3; goto clef; }
    
    "o" "ctave"? WS* "="? WS* SIGN? D+
                         { d=1; m=0;
                           YYSTART=YYCURSOR;
                           while (isdigit(*(--YYSTART))) {
                             m += (*YYSTART - '0') * d;
                             d *= 10;
                           }
                           if (m>9) m=9;
                           if (*YYSTART == '-') m = -m;
                           pak[3] = 'O'+m;
                           goto clef;
                         }
                                   
    "t" "ranspose"?  WS* "="?  WS* SIGN? D+
                         { d=1; m=0;
                           YYSTART=YYCURSOR;
                           while (isdigit(*(--YYSTART))) {
                             m += (*YYSTART - '0') * d;
                             d *= 10;
                           }
                           if (m>127) m=127;
                           if (*YYSTART == '-') m = 256-m;
                           sethex(pak+4,m);
                           goto clef;
                         }
                          
    "s" "tafflines"?  WS*  "="?  WS*  D 
                         { pak[6]=YYCURSOR[-1]; goto clef; }
                    
    "m" "iddle"?  WS*  "="?  WS*  NOTE [',]*
                         { d=1; m=0;
                           YYSTART=YYCURSOR;
                           while (!isalpha(*(--YYSTART))) {
                             switch (*YYSTART) {
                               case '\'': m++; break;
                               case ',' : m--; break;
                             }
                           }
                           if (*YYSTART < 'C') m += 3;
                           else if (*YYSTART < 'c') m += 4;
                           else m+=5;
                           if (m<0) m=0; if (m>9) m=9;
                           pak[7]=toupper(*YYSTART);
                           pak[8]='0'+m;
                           goto clef;
                         }
                    
    "stem" "s"? WS*  "="?  WS*
                         { if (*YYCURSOR == '\'' || *YYCURSOR == '"') YYCURSOR++;
                           pak[9]= toupper(*YYCURSOR);
                           if ((pak[9] != 'U') && (pak[9] != 'D')) pak[9]=' ';
                           while (*YYCURSOR && !isspace(*YYCURSOR)) YYCURSOR++;
                           goto clef;
                         } 
                    
    ("name" | "nm") WS* "="? WS*
                         { c=*YYCURSOR;
                           if (c == '\'' || c == '"') YYCURSOR++;
                           else c=' '; 
                           sethex(pak+10,off+(YYCURSOR-str));
                           m=0;
                           while (m<256 && *YYCURSOR && *YYCURSOR != c) {
                             m++; *YYCURSOR++;
                             if (*YYCURSOR && YYCURSOR[-1] == '\\') {
                               m++; *YYCURSOR++;
                             }
                           }
                           sethex(pak+12,m);
                           while (*YYCURSOR && *YYCURSOR != c) YYCURSOR++;
                           goto clef;
                         }
                    
    (("subname") | ("snm")) WS* "="? WS*
                         { c=*YYCURSOR;
                           if (c == '\'' || c == '"') YYCURSOR++;
                           else c=' '; 
                           sethex(pak+14,off+(YYCURSOR-str));
                           m=0;
                           while (m<256 && *YYCURSOR && *YYCURSOR != c) {
                             m++; *YYCURSOR++;
                             if (*YYCURSOR && YYCURSOR[-1] == '\\') {
                               m++; *YYCURSOR++;
                             }
                           }
                           sethex(pak+16,m);
                           while (*YYCURSOR && *YYCURSOR != c) YYCURSOR++;
                           goto clef;
                         }
                       
    [\000]               { goto gotclef; }
                           
    any                  {while (*YYCURSOR & (!isspace(*YYCURSOR))) YYCURSOR++;
                          goto clef;
                         }
  */

gotclef:

  return pak;
}


static char abcpkdnote(char p, char a)
{
  p = (p-1) & 0x07;
  
  switch(a) {
    case 'S': return ('Q' + p);
    case 's': return ('q' + p);
    case 'F': return ('I' + p);
    case 'f': return ('i' + p);
    case 'N': return ('A' + p);
    default : return ('a' + p);
  }
}


char *abcNKey(char *pak, char *str)
{
  char t;
  int m=0, d=1;
  YYCTYPE *YYCURSOR,*YYLIMIT,*YYMARKER,*YYSTART;

  if (str==NULL || pak==NULL) return NULL;
  
  YYCURSOR=str; while (isspace(*YYCURSOR)) YYCURSOR++;
  YYLIMIT=str;  while (*YYLIMIT) YYLIMIT++;
  
             /*01234567890123456789012345678*/
  setpack(pak,"KETMabcdefgCENOTTSMMDNNnnSSss");
  
  /* .{ Get the Tonic */
  YYSTART=YYCURSOR;
  
  /*!re2c
    NOTE [#b]?  { t='n';
                  if ((YYCURSOR - YYSTART) > 1) 
                    t = (YYSTART[1] == '#')? 's': 'f';
                  pak[2] = abcpkdnote(*YYSTART,t);
                  goto mode;
                }
    "HP"        { pak[2] = 'P'; goto mode; }       
    "Hp" | "hp" { pak[2] = 'p'; goto mode; }
    n o n e     { pak[2] = 'Z'; goto mode; }
    
    any         { YYCURSOR--  ; goto mode; }
  */
  /* .} */
  
  /* .{ Get the mode */
mode:
  /*!re2c
    WS+        { goto mode; }

    m a j NS*  { pak[3]='M' ; goto exp;}
    m i n NS*  { pak[3]='m' ; goto exp;}
    m i x NS*  { pak[3]='X' ; goto exp;}
    d o r NS*  { pak[3]='D' ; goto exp;}
    p h r NS*  { pak[3]='P' ; goto exp;}
    l y d NS*  { pak[3]='L' ; goto exp;}
    l o c NS*  { pak[3]='l' ; goto exp;}
    i o n NS*  { pak[3]='I' ; goto exp;}
    a e o NS*  { pak[3]='A' ; goto exp;}
    e x p NS*  { pak[3]='E' ; goto exp;}
    "m"        { pak[3]='m' ; goto exp;}
    "M"        { pak[3]='M' ; goto exp;}
    
    any        { YYCURSOR-- ; goto exp;}
  */
  /* .} */
  
  /* .{ Get explicit accidentals in the key */
  
exp:
  YYSTART=YYCURSOR;

  /*!re2c
    WS+        { goto exp; }
    "^^" NOTE  { pak[3 + (YYCURSOR[-1] & 0x07)] = 'S'; goto exp; }
    "^"  NOTE  { pak[3 + (YYCURSOR[-1] & 0x07)] = 's'; goto exp; }
    "__" NOTE  { pak[3 + (YYCURSOR[-1] & 0x07)] = 'F'; goto exp; }
    "_"  NOTE  { pak[3 + (YYCURSOR[-1] & 0x07)] = 'f'; goto exp; }
    "="  NOTE  { pak[3 + (YYCURSOR[-1] & 0x07)] = 'N'; goto exp; }
    
    NOTE "##"  { pak[3 + (*YYSTART & 0x07)] = 'S'; goto exp; }
    NOTE "#"   { pak[3 + (*YYSTART & 0x07)] = 's'; goto exp; }
    NOTE "bb"  { pak[3 + (*YYSTART & 0x07)] = 'F'; goto exp; }
    NOTE "b"   { pak[3 + (*YYSTART & 0x07)] = 'f'; goto exp; }
    NOTE "="   { pak[3 + (*YYSTART & 0x07)] = 'N'; goto exp; }
    
    any        { YYCURSOR-- ; goto clef;}
  */
  
  /* .} */

clef:
  
  clef(pak+11,YYCURSOR,YYCURSOR-str);
  
  return pak;
}   


/*
Voice
  012345678890123456789012
  VEIIiiCENOTTSMMDNNnnSSss
    \ \
     \ \_________________ ID length 
      \__________________ ID offset  

*/

char *abcNVoice(char *pak, char *str)
{
  char *t;
  int m=0, d=1;
  YYCTYPE *YYCURSOR,*YYLIMIT,*YYMARKER,*YYSTART;

  if (str==NULL || pak==NULL) return NULL;
  
  YYCURSOR=str; while (isspace(*YYCURSOR)) YYCURSOR++;
  YYLIMIT=str;  while (*YYLIMIT) YYLIMIT++;
  
             /*012345678901234567890123*/
  setpack(pak,"VEIIiiCENOTTSMMDNNnnSSss");
  
  sethex(pak+2,YYCURSOR-str);
  YYSTART=YYCURSOR;   
  
  while (m<65 && *YYCURSOR && !isspace(*YYCURSOR)) {
    m++;
    YYCURSOR++;
  }
  sethex(pak+4,YYCURSOR-YYSTART);
  
  while (*YYCURSOR && !isspace(*YYCURSOR)) YYCURSOR++;
  
  clef(pak+6,YYCURSOR,YYCURSOR-str);
  
  return pak;
}   

