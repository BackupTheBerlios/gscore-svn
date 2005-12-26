#include "abcp.h"

char buffer[1024];
char *cursor=buffer;

int nbars=0;
int incipitfound;

int handleincipit(abcHandle h)
{
  int     t = abcToken(h);
  char    *str = abcString(h);
  int     s = abcState(h);

  if (t == T_FIELDB) {
    if (s == (S_FIELD | 'T')) {
      *cursor++ =' '; *cursor='\0';
      strcat(cursor,str);
    }
    else if (s == (S_FIELD | 'X')) {
      cursor=buffer;  buffer[0]='\0';
      sprintf(cursor, "%4d -",atoi(str));
      nbars=1;
      incipitfound=0;
    }
  }
  else if (t == T_EMPTYLINE || t == T_EOF) {
    if (*buffer) printf("%s\n",buffer);
    cursor=buffer;  buffer[0]='\0';
  }
  else if (s == S_TUNE    &&  nbars < 5 &&
           t != T_ENDLINE && t != T_STARTLINE &&
           t != T_FIELD   && t != T_EXTFIELD ) {
      if (! incipitfound) {
        strcat(cursor,"\n       ");
        while (*cursor) cursor++;
      }
      else if (t == T_BAR)
        nbars++;
      strcat(cursor,str);
      incipitfound = 1;
  } 
  while (*cursor) cursor++;
  return 0;
}


int main(int argc,char *argv[])
{
  if (argc < 2) {
    fprintf(stderr,"Usage: incipit file.abc\n");
    return 1;
  }
  
  cursor=buffer;  buffer[0]='\0';
  if (abcScanFile(argv[1],handleincipit)) {
    fprintf(stderr,"ERROR! cannot scan %s\n",argv[1]);
    return 1;
  }

  return 0;
}

