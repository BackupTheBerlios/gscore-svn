#include "abcp.h"


/*



1 |   T_BAR_SINGLE
2 |]  T_BAR_THIN_THICK
3 ||  T_BAR_THIN_THIN
4 [|  T_BAR_THIN_THICK
5 |:  T_BAR_START_1
6 :|  T_BAR_END_1
7 ::  T_BAR_ENDSTART_1
8 .|  dotted
9 [|] Invisible

  |ETes
     \\__ repsstart
      \__ repsend
     
      
      
 |:::  :::|::  ::|

*/

/*!re2c
WS=[\040\011\012\015];
any=[\000-\377];
NS = any\WS;
DQS = ["] (any\["]) ["];
SQS = ['] (any\[']) ['];
D = [0-9];
EOS=[\000];
*/


char *abcNBar(char *pak, char *str)
{
  char *t;char c;
  int m=0, d=0,n=1;
  YYCTYPE *YYCURSOR,*YYLIMIT,*YYMARKER,*YYSTART;

  if (str==NULL || pak==NULL) return NULL;
  
  YYCURSOR=str; skipspace(YYCURSOR);
  YYLIMIT=str;  while (*YYLIMIT) YYLIMIT++;
    
             /*012345678901234567890123456789*/
  setpack(pak,"|ETes");  
 
  
  pak[3]='0'; pak[4]='0';
  
  /*!re2c
    
    "|]"    { pak[2] = '2'; GOTO(done);}
    "||"    { pak[2] = '3'; GOTO(done);}
    "[|"    { pak[2] = '4'; GOTO(done);}
    ".|"    { pak[2] = '8'; GOTO(done);}
    "[|]"   { pak[2] = '9'; GOTO(done);}

    ":"     { d=1; GOTO(reps_end); }
    "|:"    { m=1; GOTO(reps_start); }
    
    "|"     { pak[2] = '1'; GOTO(done);}
    
    any     { setperr(pak,1); GOTO(done); }
      
  */  
 
  STATE(reps_end) {
    
    /*!re2c
      ":"      { d++; GOTO(reps_end);}
      
      EOS      { m=d>1; d-=m;
                GOTO(reps_found); }  
      
      "|"      { GOTO(skip_bars); }
    */
  }

  STATE(skip_bars) {
    /*!re2c
      "|"    { GOTO(skip_bars); }
      ":"    { m++; GOTO(reps_start); }
      EOS    { GOTO(reps_found); }
      any    { setperr(pak,2); GOTO(done); }
    */
  }
  
  STATE(reps_start) {
    /*!re2c
      ":"    { m++; GOTO(reps_start); }
      EOS    { GOTO(reps_found); }
      any    { setperr(pak,3); GOTO(done); }
    */
  }
  
  STATE(reps_found) {
    pak[2] = '0';
    pak[3] = '0'+d;
    pak[4] = '0'+m;
    GOTO(done);
  }
    
  STATE(done)
    return pak;
}

