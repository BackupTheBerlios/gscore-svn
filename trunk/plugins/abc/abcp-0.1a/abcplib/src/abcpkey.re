
#include "abcp.h"


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
     \\\ \\ \___________ stem direction  0100 ggss  00=auto; 11=none; 10=up; 01=down;
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

                           71 doh1 (Gregorian)
                           72 doh2 
                           73 doh3
                           74 doh4
                           75 Fa1  (Gregorian)
                           76 Fa2
                           77 Fa3
                           78 Fa4
                           
                                        line
                           treble  0100 xxxx
                           alto    0101 xxxx
                           bass    0110 xxxx
                           doh     0111 0xxx
                           fa      0111 1xxx

If line is 0 the clef is invisible (i.e. "none" is "treble0").
if line is A (10) no line value has been specified

Staff lines
  The parser handles up to 9 staff lines numbered from 1
to 9, the position of the clef and/or the the "middle=" 
parameters determine the note on each line.

Stems
  
 0100 ggss  00=auto; 11=none; 10=up; 01=down;

Errors:
1= invalid note
2=
3=
4= Unrecognized token
5=
6=

*/


/*!re2c

WS=[\040\011\012\015];
any=[\001-\377];
NS = any\WS;
DQS = ["] (any\["]) ["];
SQS = ['] (any\[']) ['];
D = [0-9];
H = [0-9A-Fa-f];
SIGN=[\053\055];
EOS=[\000];

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

#define getnum(x,s) do {char t; t=*s; x=0;\
                        if (t=='-' || t == '+') s++;\
                        while(isdigit(*s)) x=x*10+ (*s++ - '0');\
                        if (t=='-') x=-x;\
                       } while(0)
                       

#define v(x) (*v-'0')

static char *clef(char *pak, char *str,int off)
{
  int m,d;
  char *t; char c;
  int i;
  
  YYCTYPE *YYCURSOR,*YYLIMIT,*YYMARKER,*YYSTART,*YYEND;

  if (str==NULL || pak==NULL) return NULL;
  
  YYCURSOR=str;
  YYLIMIT=str;  while (*YYLIMIT) YYLIMIT++; 
  /*printf("clef: '%s'\n",YYCURSOR);*/
  
               /*012345678901234567*/
  /*setpack(pak,"CENOTTLMMDNNnnSSss");*/
  pak[0]='C';
  pak[1]='@';
  pak[9]='@';

  STATE(get_clef) {
  /* printf("\n---\n%s\n--\n",str); */
    skipspace(YYCURSOR);
    YYSTART=YYCURSOR;
    
    /*!re2c
    
      "clef" WS* "="? WS*  { if (!isalpha(YYCURSOR[1])) {
                               pak[2] = 0x3A;
                               switch (*YYCURSOR) {
                                 case 'F': pak[2] += 0x10;
                                 case 'C': pak[2] += 0x10;
                                 case 'G': pak[2] += 0x10;
                                           YYCURSOR++;
                                           break;
                                 default: pak[2]=' ';
                               }
                             }
                             GOTO(get_clef);
                           }
      
      "none"               { pak[2] = 0x40; GOTO(get_clef); }
      "perc" | "drum"      { pak[2] = 0x4F; GOTO(get_clef); }
      "french" "violin"?   { pak[2] = 0x41; GOTO(get_clef); }
      "violin"             { pak[2] = 0x42; GOTO(get_clef); }
      "soprano"            { pak[2] = 0x51; GOTO(get_clef); }
      "mezzo" "soprano"?   { pak[2] = 0x52; GOTO(get_clef); }
      "tenor"              { pak[2] = 0x54; GOTO(get_clef); }
      "baritone"           { pak[2] = 0x55; GOTO(get_clef); }
      "subbass"            { pak[2] = 0x65; GOTO(get_clef); }
      
      "treble"             { pak[2] = 0x4A; GOTO(get_clef); }
      "alto"               { pak[2] = 0x5A; GOTO(get_clef); }
      "bass"               { pak[2] = 0x6A; GOTO(get_clef); }
      "Doh" | "doh"        { pak[2] = 0x77; GOTO(get_clef); }
      "Fa"  | "fa"         { pak[2] = 0x7F; GOTO(get_clef); }
                          
      "treble" D           { pak[2] = YYCURSOR[-1] + 0x10; GOTO(get_clef); }
      "alto" D             { pak[2] = YYCURSOR[-1] + 0x20; GOTO(get_clef); }
      "bass" D             { pak[2] = YYCURSOR[-1] + 0x30; GOTO(get_clef); }
      
      ("Doh" | "doh") D    { pak[2] = (YYCURSOR[-1] & 0x07) + 0x70; GOTO(get_clef); }
      ("Fa" | "fa") D      { pak[2] = (YYCURSOR[-1] & 0x07) + 0x78; GOTO(get_clef); }
      
      "+22"                { pak[3] = 'O'+3; GOTO(get_clef); }
      "+15"                { pak[3] = 'O'+2; GOTO(get_clef); }
      "+8"                 { pak[3] = 'O'+1; GOTO(get_clef); }
      "-8"                 { pak[3] = 'O'-1; GOTO(get_clef); }
      "-15"                { pak[3] = 'O'-2; GOTO(get_clef); }
      "-22"                { pak[3] = 'O'-3; GOTO(get_clef); }
                          
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
                             GOTO(get_clef);
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
                             GOTO(get_clef);
                           }
                            
      "s" "tafflines"?  WS*  "="?  WS*  D 
                           { pak[6]=YYCURSOR[-1]; GOTO(get_clef); }
                      
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
                             GOTO(get_clef);
                           }
                      
      "g"? "stem" "s"? WS*  "="?  WS*
                           { if (*YYCURSOR == '\'' || *YYCURSOR == '"') YYCURSOR++;
                             pak[9]= toupper(*YYCURSOR);
                             if ((pak[9] != 'U') && (pak[9] != 'D')) pak[9]=' ';
                             while (*YYCURSOR && !isspace(*YYCURSOR)) YYCURSOR++;
                             GOTO(get_clef);
                           }            

      ("name" | "nm") WS* "="? WS*
                           { d=10; GOTO(get_name); }

      ("subname" | "snm" | "shortname" ) WS* "=" WS*
                           { d=14; GOTO(get_name); }
                                                        
      EOS                  { GOTO(done); }
      any                  { while (*YYCURSOR & (!isspace(*YYCURSOR))) YYCURSOR++;
                             setperr(pak,1);
                             GOTO(get_clef); }
           
    */
  }     

  STATE(get_name) {
    c=*YYCURSOR;
    if (c == '\'' || c == '"') YYCURSOR++;
    else c=' '; 
    sethex(pak+d,off+((char *)YYCURSOR-str));
    m=0;
    while (m<256 && *YYCURSOR && *YYCURSOR != c) {
      m++; *YYCURSOR++;
      if (*YYCURSOR && YYCURSOR[-1] == '\\') {
        m++; *YYCURSOR++;
      }
    }
    sethex(pak+d+2,m);
    while (*YYCURSOR && *YYCURSOR == c) YYCURSOR++;
    GOTO(get_clef);
  }
   
  STATE(done)
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
  
  YYCURSOR=str; skipspace(YYCURSOR);
  YYLIMIT=str;  while (*YYLIMIT) YYLIMIT++;

  
             /*01234567890123456789012345678*/
  setpack(pak,"KETMabcdefgCENOTTSMMDNNnnSSss");
  
  if (! *YYCURSOR) GOTO(done);
  
  /* .{ Get the Tonic */
  YYSTART=YYCURSOR;
  
  /*!re2c
    NOTE [#b]?  { t='n';
                  if ((YYCURSOR - YYSTART) > 1) 
                    t = (YYSTART[1] == '#')? 's': 'f';
                  pak[2] = abcpkdnote(*YYSTART,t);
                  GOTO(mode);
                }
    "HP"        { pak[2] = 'P'; GOTO(mode); }       
    "Hp" | "hp" { pak[2] = 'p'; GOTO(mode); }
    n o n e     { pak[2] = 'Z'; GOTO(mode); }
    
    any         { YYCURSOR--  ; GOTO(mode); }
  */
  /* .} */
  
  /* .{ Get the mode */
  STATE(mode) {
    /*!re2c
      WS+        { GOTO(mode); }
    
      m a j NS*  { pak[3]='M' ; GOTO(exp);}
      m i n NS*  { pak[3]='m' ; GOTO(exp);}
      m i x NS*  { pak[3]='X' ; GOTO(exp);}
      d o r NS*  { pak[3]='D' ; GOTO(exp);}
      p h r NS*  { pak[3]='P' ; GOTO(exp);}
      l y d NS*  { pak[3]='L' ; GOTO(exp);}
      l o c NS*  { pak[3]='l' ; GOTO(exp);}
      i o n NS*  { pak[3]='I' ; GOTO(exp);}
      a e o NS*  { pak[3]='A' ; GOTO(exp);}
      e x p NS*  { pak[3]='E' ; GOTO(exp);}
      "m"        { pak[3]='m' ; GOTO(exp);}
      "M"        { pak[3]='M' ; GOTO(exp);}
      EOS        { GOTO(done); }
      any        { YYCURSOR-- ; GOTO(exp);}
    */
  }
  /* .} */
  
  /* .{ Get explicit accidentals in the key */
  
  STATE(exp) {
    YYSTART=YYCURSOR;
    
    /*!re2c
      WS+        { GOTO(exp); }
      "^^" NOTE  { pak[3 + (YYCURSOR[-1] & 0x07)] = 'S'; GOTO(exp); }
      "^"  NOTE  { pak[3 + (YYCURSOR[-1] & 0x07)] = 's'; GOTO(exp); }
      "__" NOTE  { pak[3 + (YYCURSOR[-1] & 0x07)] = 'F'; GOTO(exp); }
      "_"  NOTE  { pak[3 + (YYCURSOR[-1] & 0x07)] = 'f'; GOTO(exp); }
      "="  NOTE  { pak[3 + (YYCURSOR[-1] & 0x07)] = 'N'; GOTO(exp); }
      
      NOTE "##"  { pak[3 + (*YYSTART & 0x07)] = 'S'; GOTO(exp); }
      NOTE "#"   { pak[3 + (*YYSTART & 0x07)] = 's'; GOTO(exp); }
      NOTE "bb"  { pak[3 + (*YYSTART & 0x07)] = 'F'; GOTO(exp); }
      NOTE "b"   { pak[3 + (*YYSTART & 0x07)] = 'f'; GOTO(exp); }
      NOTE "="   { pak[3 + (*YYSTART & 0x07)] = 'N'; GOTO(exp); }
      EOS        { GOTO(done); }
      
      any        { YYCURSOR-- ; GOTO(clef);}
    */
  }
  /* .} */

  STATE(clef)
    clef(pak+11,YYCURSOR,(char *)YYCURSOR-str);
  
  STATE(done)
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
  
  YYCURSOR=str; skipspace(YYCURSOR);
  YYLIMIT=str;  while (*YYLIMIT) YYLIMIT++;
  
             /*012345678901234567890123*/
  setpack(pak,"VEIIiiCENOTTSMMDNNnnSSss");
  
  sethex(pak+2,(char *)YYCURSOR-str);
  YYSTART=YYCURSOR;   
  
  while (m<65 && *YYCURSOR && !isspace(*YYCURSOR)) {
    m++;
    YYCURSOR++;
  }
  sethex(pak+4,YYCURSOR-YYSTART);
  
  while (*YYCURSOR && !isspace(*YYCURSOR)) YYCURSOR++;
  
  if (*YYCURSOR)
    clef(pak+6,YYCURSOR,(char *)YYCURSOR-str);
  
  return pak;
}   


/*
           
 0123456
 LENNDDS
   \ \ \__ Specified as string
    \ \___ denominamtor
     \____ Numerator   
     
 L: <num/den>
 0 doublewhole
 1 whole
 2 half
 3 quarter 
 4 eighth 
 5 sixteenth 
 6 thirtysecond 
 7 sixtyfourth 
 8 onetwentyeighth
 
*/


char *abcNLength(char *pak, char *str)
{
  char *t;char c;
  int m=0, d=1,n=1;
  YYCTYPE *YYCURSOR,*YYLIMIT,*YYMARKER,*YYSTART;

  if (str==NULL || pak==NULL) return NULL;
  
  YYCURSOR=str; skipspace(YYCURSOR);
  
               /*012345678901234567890123*/
  setpack(pak,"LENNDDS");
  
  m=getfrac(&YYCURSOR,&n,&d);


  if (m >1 ) 
    setperr(pak,m);
  else {
    sethex(pak+2,n);
    sethex(pak+4,d);     
  }
  return pak;
}

