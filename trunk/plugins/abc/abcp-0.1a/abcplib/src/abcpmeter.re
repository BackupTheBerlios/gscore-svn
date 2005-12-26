
#include "abcp.h"

/*

  012345678901234
  MEPNNDDnnxxddyy
    \\ \ \ \ \ \__ Length of denominator string
     \\ \ \ \ \___ Denominator string offset
      \\ \ \ \____ Length of numerator string
       \\ \ \_____ Numerator string offset
        \\ \______ Denominator value (0-20)
         \\_______ Numerator value (1-20)
          \_______ Parenthesis A=all, N=numerator,
                   D=denominator, " "=none
             
  Meter can be in one of the following format:
  
  C      0/4  (to distinguish it from 4/4)
  C|     0/2  (to distinguish it from 2/2)
  n/d
  n      n/0  (to distinguish it from an explicit n/1)
  a+b+c/d
  "none" 0/1
  "free" 0/1
     
  Meter can be surrounded by parenthesis:
  
  (n/d)   1001  49 'I'
  (n)/d   1100  4C 'L'
  n/(d)   0011  43 'C'
  
     0100 xxxx
                     
Error

1=Invalid numerator
2=Invalid denominator
3=Invalid parenthesis
4=
5=
6=    

*/


/*!re2c

EOS=[\000];
EOL=[\002];

WS=[\040\011\012\015];
any=[\001-\377];
D = [0-9];
*/


char * ABCAPI abcNMeter(char* pak, char *str)
{
  int t;
  int m=0, l=0;
  int n,d;
  int noff,doff;
  int nlen,dlen;
  
  
  YYCTYPE *YYCURSOR,*YYLIMIT,*YYMARKER,*YYSTART,*YYEND;

  if (str==NULL || pak==NULL) return NULL;
  
  YYCURSOR=str; skipspace(YYCURSOR);
  YYLIMIT=str;  while (*YYLIMIT) YYLIMIT++;
  
             /*012345678901234*/  
  setpack(pak,"MEPNNDDnnxxddyy");
  
  pak[2]='@';

  if (*YYCURSOR == '(') {
    pak[2] |= 8;
    YYCURSOR++;
  }
    
  skipspace(YYCURSOR);
  
  n=0;  nlen=0; noff=(char *)YYCURSOR-str;
  d=0;  dlen=0; doff=0;           
    
  /*!re2c
    [Cc]             { d=4; nlen=1; GOTO(gotmeter); }
    [Cc] "|"         { d=2; nlen=2; GOTO(gotmeter); }
    "none" | "free"  { d=1; nlen=4; GOTO(gotmeter); }
    any              {YYCURSOR-- ; GOTO(numerator); }

  */
     
  STATE(numerator) { 
    YYSTART=YYCURSOR;
    m=0;
  
    STATE(num) {
      /*!re2c
        WS+           { GOTO(num); }
        D             { m = m*10 + (YYCURSOR[-1] - '0');
                        YYEND=YYCURSOR; GOTO(num);
                      }
        "+"           { n += m; m=0;    GOTO(num); }
        ")"           { pak[2] |= 4;    GOTO(skipslash); }
        "/"           {                 GOTO(denominator); }
                                        
        EOS           { YYCURSOR--;     GOTO(denominator); }
        
        any           { setperr(pak,1); GOTO(got); }
      */
    }
  }
  
  STATE(skipslash) {
    skipspace(YYCURSOR);
    if (*YYCURSOR == '/') YYCURSOR++;
  }
   
  STATE(denominator) {
    n += m; nlen=YYEND-YYSTART; noff=(char *)YYSTART-str;
    d=0; 
    
    skipspace(YYCURSOR);
    if (*YYCURSOR == '(') {
      pak[2] |= 2;
      YYCURSOR++;
      skipspace(YYCURSOR);
    }
    YYSTART=YYCURSOR;
    m=0;
      
    STATE(den) {
  
      /*!re2c
        D              { m = m*10 + (YYCURSOR[-1] - '0');
                         GOTO(den);
                       }
        WS+ | EOS      { GOTO(gotden); }
           
        any            { setperr(pak,2); GOTO(got); }
      */
    }
  }
  
  STATE(gotden) {
    d = m; dlen=YYCURSOR-YYSTART; doff=(char *)YYSTART-str;
    skipspace(YYCURSOR);
  }
  
  STATE(gotmeter) {

    sethex(pak+3,n); sethex(pak+5,d);
    sethex(pak+7,noff);  sethex(pak+9,nlen);
    sethex(pak+11,doff); sethex(pak+13,dlen);
      
    skipspace(YYCURSOR);
    if (*YYCURSOR == ')') pak[2] |= 1;
    
    switch (pak[2]) {
      case 0x40 :
      case 0x43 :
      case 0x49 :
      case 0x4C : break;
      default:  setperr(pak,3);  
    } 
  }
  
  STATE(got) {
    return pak;
  }
}
