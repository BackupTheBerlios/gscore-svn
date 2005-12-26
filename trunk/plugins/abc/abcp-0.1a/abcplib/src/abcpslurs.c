#include "abcp.h"

/*
  Slurs and ties
  
  01234 
  -ETDd
    \\\__ dotted (.)
     \\__ direction (U,D,A) 
      \__ type (S=open slur, T=tie)
     
           
*/


char *abcNSlurTie(char *pak, char *str)
{
  
  char *t=NULL;
  char c;
  int m,n,d;
  
  YYCTYPE *YYCURSOR,*YYLIMIT,*YYMARKER,*YYSTART;

  if (str==NULL || pak==NULL) return NULL;
  
  YYCURSOR=str; skipspace(YYCURSOR);
  
             /*012345678901234567890123456789*/
  setpack(pak,"-ETDd");
  
  if (*YYCURSOR == '.') {
    pak[4]='.';
    YYCURSOR++;
  }
  
  pak[2]=*YYCURSOR++;
  
  switch (*YYCURSOR) {
    case '\'' : pak[3]='U'; break;
    case ','  : pak[3]='D'; break;
  }
  
  return pak;
}

