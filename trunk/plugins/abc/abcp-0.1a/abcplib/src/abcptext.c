/*
 Manage all the fields that have text values.
 
 It also manages comma separated lists:
 
 
 XEO1L1O2L2...
   \ \ \ \ \___ ...
    \ \ \ \____ Length of second element
     \ \ \_____ Offset of second element  
      \ \______ Length of first element
       \_______ Offset of first element  

*/


#include "abcp.h"

static char * text(char t, char* pak, char *str,char s)
{
  int m=2, l=0;
  
  YYCTYPE *YYCURSOR,*YYSTART;

             /*01234567*/
  setpack(pak,"XE");
  
  
  if (str==NULL || pak==NULL) return NULL;

  YYCURSOR=str;
   
  while (*YYCURSOR) {
    YYSTART=YYCURSOR;
    sethex(pak+m,(char *)YYCURSOR - str);
    m+=2;
    while (*YYCURSOR && *YYCURSOR != s)
      YYCURSOR++;
    sethex(pak+m,YYCURSOR-YYSTART);
    m+=2;
    pak[m]='\0';
    if (*YYCURSOR) YYCURSOR++;  
  } 
  pak[0]=t;
  
  return pak;
}


#define abcN(f,l,s) char *abcN ## f (char* pak, char *str)\
                                      { return text(l,pak,str,s); }

abcN(string,      '$','\0')
abcN(list,        ',',',')
