#ifndef ABCP_H
#define ABCP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef GLOBAL
#undef GLOBAL
#define GLOBAL(x,y) x=y
#else
#define GLOBAL(x,y) extern x
#endif

#ifdef DLL
#include <windows.h>
#define ABCAPI __declspec(dllexport)
#else
#define ABCAPI
#endif


#ifndef USHORT
#define USHORT unsigned short int
#endif

#ifndef ULONG
#define ULONG unsigned long int
#endif

/* A simple rational numbers handling.
   Assumes ULONG has at least 32 bits space */
#define RATIONAL     unsigned long int
#define RAT(n,d)     ((n)<<16|(d))
#define RAT_NUM(r)   ((r)>>16)
#define RAT_DEN(r)   ((r) & 0xFFFF)
#define RAT_VAL(r)   (((double)RAT_NUM(r)/(double)RAT_DEN(r)))

#define RAT_EQU(r,s) (RAT_CMP(r,s) == 0)

RATIONAL RAT_CMP(RATIONAL r, RATIONAL s);
RATIONAL RAT_SIMPLIFY(RATIONAL r);

/* Macros to hide the shame of using goto's!!! :) */
#define STATE(x)  s_##x:
#define GOTO(x) goto s_##x
#define ENDSTATE  


/*
** This is the re2c interface
*/

#define YYCTYPE   unsigned char
#define YYCURSOR  cursor
#define YYLIMIT   limit
#define YYMARKER  marker
#define YYFILL(n)


#define S_EOF        0x0000
#define S_ERROR      0x0001
#define S_LIMBO      0x0002
#define S_NONE       0x0003
#define S_TUNE       0x0004
#define S_FIELD      0x1000  
#define S_EXTFIELD   0x2000
#define S_INFIELD    0x4000
#define S_ANYFIELD   0x7000
#define S_CFIELD     0x5000  /* A "colon" field like A: or [A:]*/


#define m_LFIELD(x)  ((x)->state & 0x00FF)
#define m_isFIELD(x) ((x)->state & S_FIELD)

#define abcSt USHORT

typedef enum {
  T_FIRST,
  T_UNKNOWN,   T_NONE,         T_EOF,       T_COMMENT,   T_EMPTYLINE,
  T_EXTFIELD,  T_FIELD,        T_NOTE,      T_WSPACE,    T_BAR,
  T_INFIELD,   T_TEXT,         T_ENDLINE,   T_CONTINUE,  T_DECOR,
  T_REST,      T_INVREST,      T_MULTIREST, T_SPACER,    T_NPLET,
  T_OPENSLUR,  T_CLOSESLUR,    T_DOTRIGHT,  T_DOTLEFT,   T_CHORDSTART,
  T_CHORDEND,  T_CHORD,        T_REPEAT,    T_GRACEAPP,  T_GRACEACC,
  T_GRACEEND,  T_TIE,          T_STRING,    T_STRINGUNF, T_ANNOTATION,
  T_BREAK,     T_OVERLAY,      T_STARTLINE, T_FIELDB,    T_PRAGMA,
  T_LYR_SYLL,  T_LYR_BLANK,    T_LYR_BAR,   T_LYR_SPACE, T_LYR_CONT,
  T_LYR_VERSE, T_OPENSLUR_DOT, T_TIE_DOT,   T_DUPMESURE, T_DECOR_BLANK,
  T_BSPACE,
  T_LAST
} abcToks;


typedef struct {
  USHORT   guard;
  USHORT   token;
  USHORT   state;
  USHORT   line;
  USHORT   toklen;
  USHORT   nextstate;
  ULONG    bufsize;
  FILE    *file;
  YYCTYPE *cursor;
  YYCTYPE *limit;
  YYCTYPE *marker;
  YYCTYPE *tokstr;
  YYCTYPE *filename;
  YYCTYPE *nextln;
  YYCTYPE  pack[81];   /* The packed parsed token */
  YYCTYPE  lastch;
  YYCTYPE  buffer[1];  /* The rest of the array will be malloced */
} abcScanner;

#define abcHandle void * 
typedef char *abcPacked;
int getextfield (YYCTYPE **str);

/* LEVEL 0 - Scanner interface */
typedef int (*abcHandler)(abcHandle h);

int abcScanFile(char *filename,abcHandler handler);
int abcScanString(char *buffer,abcHandler handler);

int         abcToken(abcScanner *s);
const char *abcTokenName(int n);
int         abcState(abcScanner *s);
const char *abcStateName(int s);
const char *abcString(abcScanner *s);
const abcPacked   abcParsedString(abcScanner *s);
const char *abcFilename(abcScanner *s);
int         abcLine(abcScanner *s);
int         abcColumn(abcScanner *s);


/* LEVEL 1 - Elements interpretation */

#define STM(x) do {x} while(0)

#define setspace(p,n) STM( int _d=0;\
                           while (_d<n) p[_d++]=' ';\
                           p[n]='\0';\
                         )
                      
#define setpack(p,s) STM( int _i=1; p[0]=s[0];\
                          while (s[_i]) p[_i++]=' ';\
                          p[_i]='\0';\
                          p[1]='@';\
                        )

#define setperr(e,n) STM( (e)[1] |= (n == 0 || n >6)?  '@' :  '@' | 1<<(n-1) ;)

GLOBAL(char *hexdigits, "0123456789ABCDEF");

#define sethex(h,n)  STM( (h)[0]=hexdigits[((n) >>4)  & 0xF];\
                          (h)[1]=hexdigits[(n)      & 0xF];\
                     )

#define sethex2(h,n) STM( (h)[0]=hexdigits[((n) >>12) & 0xF];\
                          (h)[1]=hexdigits[((n) >>8)  & 0xF];\
                          (h)[2]=hexdigits[((n) >>4)  & 0xF];\
                          (h)[3]=hexdigits[(n)      & 0xF];\
                     )

#define skipspace(x)   STM( while (isspace(*x)) x++;)
#define skiptospace(x) STM( while (*(x) && !isspace(*(x))) x++;)

int getfrac(YYCTYPE **cursor,int *num, int *den);
                      
typedef char *(abcNfunc)(char *pak, char *str);
                                      
abcNfunc abcNNote;
abcNfunc abcNKey;
abcNfunc abcNVoice;
abcNfunc abcNDecoration;
abcNfunc abcNMeter;
abcNfunc abcNLength;
abcNfunc abcNTempo;
abcNfunc abcNSlurTie;
abcNfunc abcNBar;


abcNfunc abcNlist;
abcNfunc abcNstring;

#endif
