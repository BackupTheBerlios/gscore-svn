#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef HASH

#include "phash.c"


void outlist(char *code0, char *key)
{
  ub4 hash;
  hash = PHASH(key, strlen(key));  
  printf("/* %4d */ 0x%s%04X, /* %-25s */\n", hash, code0, shash(key), key);
}

#else

void outlist(char *code0, char *key)
{
  printf("%s\n", key);
}
#endif

#define MAXLEN 120

int main(int argc, char **argv)
{
  char mytext[MAXLEN];
  char code0[8];
  int n;
  int s=0;
  char *t;
  char *q;
    
  while (fgets(mytext, MAXLEN, stdin))  {
    n=strlen(mytext);
    while (n>0 && isspace(mytext[n-1])) mytext[--n]='\0';
    t=mytext;
    while (isspace(*t)) t++;

    if (strncmp(t,"-- BEGIN",8) == 0) s=1;
    if (strncmp(t,"-- END",6) == 0) s=0;
 
    if (s>0 && *t && *t != '-') {
      q=strtok(t," \t\n");
      strncpy(code0,q,4);
      code0[4]='\0';
      q=strtok(NULL," \t\n");
      while (q && *q) {
        outlist(code0,q);
        q=strtok(NULL," \t\n");
      }
    }
  }
 
  return 0;
}
