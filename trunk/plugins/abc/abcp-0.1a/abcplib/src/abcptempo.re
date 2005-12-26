#include "abcp.h"

/*
           1         2
 012345678901234567890123456789
 QESSxxN1D1N2D2N3D3N4D4CCLLll
                   \    \ \___  <num>
                        \____   
                         
 Q: [1/8 [2/8 [ 3/8 [4/8]]] =] <num>] ["string"] 
 Q: ["string"] [1/8 [2/8 [ 3/8 [4/8]]] =] <num>]
 Q: C<num0>=<num1>
 
 
*/

/*!re2c
WS=[\040\011\012\015];
any=[\000-\377];
NS = any\WS;
DQS = ["] (any\["]) ["];
SQS = ['] (any\[']) ['];
D = [0-9];
*/

/*
  0 = OK
  1 = integer (no den!)
  2 = not a number!
*/

int getfrac(YYCTYPE **str,int *num, int *den)
{
  YYCTYPE *YYCURSOR;
  int ret=2;
  
  YYCURSOR = *str;
  
  *num=0; *den=1;
  
  skipspace(YYCURSOR);  
  if (isdigit(*YYCURSOR)) {
    while (isdigit(*YYCURSOR))
      *num = *num * 10 + (*YYCURSOR++ - '0');
    ret=1;
  
    skipspace(YYCURSOR);
    if (*YYCURSOR == '/') {
      *den=0;
      YYCURSOR++;
      skipspace(YYCURSOR);
      while (isdigit(*YYCURSOR))
        *den = *den * 10 + (*YYCURSOR++ - '0');
      ret=0;
      skipspace(YYCURSOR);
    }
  }
  *str = YYCURSOR;   
  return ret;
}

char *abcNTempo(char *pak, char *str)
{
  char *t=NULL;
  char c;
  int m,n,d;
  
  YYCTYPE *YYCURSOR,*YYLIMIT,*YYMARKER,*YYSTART;

  if (str==NULL || pak==NULL) return NULL;
  
  YYCURSOR=str; skipspace(YYCURSOR);
  YYLIMIT=str;  while (*YYLIMIT) YYLIMIT++;
    
             /*012345678901234567890123456789*/
  setpack(pak,"QESSxxN1D1N2D2N3D3N4D4CCLLll");

  STATE(tempo) {
    /*!re2c
      "C"      { GOTO(common); }
      D        { YYCURSOR-- ; GOTO(beats); }
      ["]      { GOTO (string); }
      any      { setperr(pak,1); GOTO(done); }
    */
  }

  STATE(common) {
    m=0;
    STATE(num) {
      /*!re2c
        D             { m=(m*10) + (YYCURSOR[-1] -'0'); GOTO(num); }
        WS* "=" WS*   { sethex(pak+22,m); GOTO(common); }
        WS* [\000]    { sethex(pak+24,m); GOTO(done); }
        WS* ["]       { sethex(pak+24,m); GOTO(string); }
        any           { setperr(pak,3); GOTO(done); } 
      */
    }
  }

  STATE(waitstring) {
    /*!re2c
      WS+     { GOTO(waitstring); }
      ["]     { GOTO(string); }
      [\000]  { GOTO(done); }
      any     { setperr(pak,3); GOTO(done); } 
    */
  }
      
  STATE(string) {
    YYSTART=YYCURSOR;
    /*printf("%s\n",YYCURSOR); */
    STATE(str) {
      /*!re2c
        "\\" any    { GOTO(str); }
        
        [\000]      { YYCURSOR--; GOTO(done); }
                      
        ["]         { sethex(pak+2,(char *)YYSTART-str);
                      sethex(pak+4,YYCURSOR-YYSTART);
                      GOTO(beats); }
        any         { GOTO(str); }
      */
    }
  }
  
  STATE(beats) {
    t=pak+6;
    
    STATE(beat) {
      m=getfrac(&YYCURSOR,&n,&d);
      if (m == 0) {
        sethex(t,n);
        sethex(t+2,d);
        t += 4;
        if (t>pak+20) GOTO(waitbeatnum);
        GOTO(beat);
      }
      if (m == 1) {
        sethex(pak+24,n);
        GOTO(waitstring);
      }
      /*printf("%d,%s\n",m,YYCURSOR);*/
      if (m == 2) {
        if (*YYCURSOR == '=') {
          YYCURSOR++;
          GOTO(beatnum);
        }
        if (*YYCURSOR == '"')  {
          YYCURSOR++;
          GOTO(string);
        }
        
        if (*YYCURSOR == '\0') GOTO(done);
      }
      setperr(pak,4);
      GOTO(done);
    }
  }

  STATE(waitbeatnum) {
    /*!re2c
      WS+     { GOTO(waitbeatnum); }
      [\000]  { GOTO(done); }
      [=]     { GOTO(waitbeatnum); }
      D       { YYCURSOR-- ; GOTO(beatnum); }
      any     { setperr(pak,3); GOTO(done); } 
    */
  }
    
  STATE(beatnum) {
    m=getfrac(&YYCURSOR,&n,&d);
    if (m < 2) {
      sethex(pak+24,n);
      sethex(pak+26,d);
    }
    else 
      setperr(pak,4);
    GOTO(waitstring);  
  }
  
  STATE(done)
    return pak;
}

