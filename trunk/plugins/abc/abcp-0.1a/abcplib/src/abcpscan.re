/*
 .T ABCp A generic ABC Parser
 .A ...
 .d Aug 2004

 .abstract
   This is the '/scanner/ used in ABCp. The main function
   is '{abcNextToken()} that returns the next token in a file
   based on the current state.
 ..

 .disclaimer
   This code is distributed under an OSI compliant licence 
   The short story is that you are free to use this code as you wish
   as long as the appropriate credit to authors is given in a convenient
   place in your application and in the associated documentation.
   
   ABCp uses '|re2C|. See '<http://re2c.sourceforge.net> for details.
 ..
 
 .* How to read this file
 
 You should start from the abcNextFunction.
 
*/

#define GLOBAL

#include "abcp.h"

/* Just checked, it does not harm the UTF-8 compliancy */
#define SOL '\001'
#define EOL '\002'

void abcClose(abcScanner *s);
abcScanner *abcOpen(char *filename,USHORT bufsize);
int abcNextToken(abcScanner *s);

#ifdef DLL

BOOL WINAPI __declspec(dllexport) LibMain(HINSTANCE hDLLInst, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            break;
            
        case DLL_PROCESS_DETACH:
            break;
            
        case DLL_THREAD_ATTACH:
            break;
            
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}

#endif

static char *abcTokName[]={
  "T_FIRST",
  "T_UNKNOWN",   "T_NONE",         "T_EOF",       "T_COMMENT",   "T_EMPTYLINE",
  "T_EXTFIELD",  "T_FIELD",        "T_NOTE",      "T_WSPACE",    "T_BAR",
  "T_INFIELD",   "T_TEXT",         "T_ENDLINE",   "T_CONTINUE",  "T_DECOR",
  "T_REST",      "T_INVREST",      "T_MULTIREST", "T_SPACER",    "T_NPLET",
  "T_OPENSLUR",  "T_CLOSESLUR",    "T_DOTRIGHT",  "T_DOTLEFT",   "T_CHORDSTART",
  "T_CHORDEND",  "T_CHORD",        "T_REPEAT",    "T_GRACEAPP",  "T_GRACEACC",
  "T_GRACEEND",  "T_TIE",          "T_STRING",    "T_STRINGUNF", "T_ANNOTATION",
  "T_BREAK",     "T_OVERLAY",      "T_STARTLINE", "T_FIELDB",    "T_PRAGMA",
  "T_LYR_SYLL",  "T_LYR_BLANK",    "T_LYR_BAR",   "T_LYR_SPACE", "T_LYR_CONT",
  "T_LYR_VERSE", "T_OPENSLUR_DOT", "T_TIE_DOT",   "T_DUPMESURE", "T_DECOR_BLANK",
  "T_BSPACE",
  "T_LAST"
};

static char *abcStName[]={
/*  0 */ "S_EOF", 
/*  1 */ "S_ERROR",
/*  2 */ "S_LIMBO",
/*  3 */ "S_NONE",
/*  4 */ "S_TUNE",
/*  5 */ "S_FIELD",
/*  6 */ "S_EXTFIELD",
/*  7 */ "S_INFIELD"
};

/*
** Buffer limit
*/

#define MINBUFSIZE     1024
#define MAXBUFSIZE  5242880 



/*
 .* Macros
*/

/* To ease my paranoia about dynamic memory allocation
*/
#define m_guard(x)      (x)->guard=0xF00D
#define m_unguard(x)    (x)->guard=0x0BAD
#define m_guarded(x)    ((x) && ((x)->guard == 0xF00D))

/*                       if (*(x)->cursor == '\001') (x)->cursor++;\ */
 
/*
When a Match is found, the RETURN macro performs the following actions:

 1) The token field is set to the token 
 2) The "start of line char" ('\001') is skipped
 3) The length of token is computed
 4) The tokstr field is initialized to point to the start of the
    string that matched.
 5) The cursor is advanced right after the matched string
 6) The newline character, if present, is deleted
 7) The marker is set
 8) The first character of the next string to match is saved
    in the last char of the buffer.
 9) The first character of the next string is replaced by '\0' so
    that s->tokstr is a properly null terminated string.
    The saved char is to be restored next time the abcNextToken()
    is called.
10) The length of the string matched is returned.
    
*/


#define RETURN(x,t)   {(x)->token=t;\
                      if (*((x)->cursor) == SOL) (x)->cursor = (x)->cursor +1;\
                      (x)->toklen = YYCURSOR - (x)->cursor;\
                      (x)->tokstr = (x)->cursor;\
                      (x)->cursor = YYCURSOR;\
                      (x)->lastch = *YYCURSOR;\
                      if (*((x)->cursor - 1) == '\n') *((x)->cursor - 1) = '\0';\
                      (x)->marker = marker;\
                      *((x)->cursor) = '\0';\
                      (x)->pack[0]='\0';\
                      return (x)->toklen;}

#define m_linestart(x)  ((x)->cursor == (x)->buffer)
#define m_lineempty(x)  (*((x)->cursor) == '\0')
#define m_resetbuf(x)   {(x)->buffer[0]='\0';  \
                         (x)->buffer[1]='\0';  \
                         (x)->limit=(x)->buffer; \
                         (x)->cursor=(x)->limit; \
                         (x)->marker=(x)->cursor; \
                         (x)->tokstr=(x)->limit; \
                         (x)->lastch ='\0'; \
                         (x)->toklen=0;}

#define m_eof(x)  {m_resetbuf(x); \
                   (x)->token=T_EOF;\
                   (x)->state=S_EOF;}

#define m_column(x) ((x)->tokstr - (x)->buffer)

/*
** The scanning routines
**   If we are parsing a string, s->nextln points at the beginning
** of next line.
**
**   To correctly handle logical continuations, the buffer might
** be filled with more than 1 line. A '\n' will indicate a continuation.

** WARNING: this scanner does not support comments after continued lines! 

*/

static void abcGetLine(abcScanner *s)
{
  YYCTYPE *t=NULL;
  YYCTYPE *b=NULL;
  int max=s->bufsize;
  int cont=1;
  
  if (m_guarded(s) && (s->state != S_EOF)) {
    m_resetbuf(s);
    s->buffer[0] = SOL;
    b=s->buffer+1;
    if (s->file) {
      do {
        t=fgets(b,max,s->file);
        cont=0;
        if (t) {
          while (*t) t++;
          while ((t>b) && isspace(t[-1])) t--;
          if (t[-1]=='\\') {
            s->line++;
            t[-1]='\n';
            cont=1;
          }
          *t='\0';
          max -= t-b;
          b=t;
        }
      } while (t && cont);
      *b++=EOL; *b='\0';
      /*printf("*\t[%s]\n",s->buffer);*/

    }
    else if (s->nextln && *(s->nextln))  {
      /*printf("+%s\n",s->nextln);*/
      t=s->buffer+1;
      do {
        cont =0 ;
        while (*(s->nextln) && (*(s->nextln) != '\n'))
          *t++ = *(s->nextln)++;
        *t++ = *(s->nextln)++;
        /*if (*(s->nextln) != '\0') (s->nextln)++;*/
        while ((t > (s->buffer +1)) && isspace(t[-1]))
            t--;
        if (t[-1]=='\\') {
          s->line++;
          t[-1]='\n';
          cont=1;
        }
      } while (cont && *(s->nextln));
      *t++=EOL; *t='\0';
    }
    if (t) {
      s->line++;
      s->cursor=s->buffer;
      t=s->buffer; while (*t) t++;
      s->limit=t;
      s->marker=s->cursor;
    }
    else
      m_eof(s);
  }
}

#define P(x,y) abcN##x(y->pack,(char *)abcString(y))

static void abcNparse(abcScanner *s)
{
  int t; 
  int a;
  
  t=abcToken(s);

  switch (t) {
    case T_REST:
    case T_NOTE:     P(Note,s);          break;
    case T_DECOR:    P(Decoration,s);    break;
    case T_TIE:    
    case T_OPENSLUR: P(SlurTie,s);       break;
    case T_BAR: P(Bar,s); break;
    case T_FIELDB:
      a=abcState(s);
      if (a & S_CFIELD) {
        switch (a & 0xFF ) {
          case 'K' : P(Key,s);    break;
          case 'V' : P(Voice,s);  break;
          case 'M' : P(Meter,s);  break;
          case 'L' : P(Length,s); break;
          case 'Q' : P(Tempo,s);  break;

          case 'A' :
          case 'O' :
          case 'C' :
          case 'D' :
          case 'Z' : P(list,s);   break;

          default:   P(string,s); break;
        }              
      }
      break;
    default: s->pack[0]='?';s->pack[1]='\0'; 
  }
}

/*!re2c
any=[\003-\377];
EOS=[\000];
SOL=[\001];
EOL=[\002];
NWS=[\041-\177];
WS=[\040\011];
NL=[\012\015]+;
L	= [A-Za-z];
D = [0-9];

BA1 = "|" | "[" | ":" ;
BA2 = "|" | "]" | ":" ;
BAR = ".|" | "|" | BA1 BA2+ ;

MIN =[\055];


A1 =  ("_" | "^" ) (D | "/")* | "__" | "^^" | "="  ;

ACC =  A1 | "(" A1 ")";
      
N=  ACC? [A-Ga-g] ("," | "'")* (D | "/")*;

DEC=[~.uvTHLMPSOJ] | "\053" (any\[\053\040\011])+ "\053" | "\041" (any\[\040\011\041])+ "\041" ;

Q=[\042];
NQ=any\Q;

ANN  =Q [@<>^_] NQ* Q;
CHRD =Q [A-G] NQ* Q;
STR  =Q NQ* Q;
BS   =[\134];

BRK  =[\041];
*/

static int abcNT(abcScanner *s)
{
  YYCTYPE *cursor, *limit, *marker;
  cursor = s->cursor;
  limit  = s->limit;
  marker = s->marker;
  
  /*!re2c

  EOS { return -1;}
  
  SOL WS* "%%" WS* {
      s->nextstate=S_EXTFIELD | (getextfield(&YYCURSOR) & 0x0FFF);
      s->cursor=YYCURSOR;
      RETURN(s,T_EXTFIELD);
  }

  SOL WS* L [:] {
      s->cursor=YYCURSOR-2;
      s->nextstate =  S_FIELD | *(s->cursor);
      RETURN(s,T_FIELD);
  }

  WS* [%] {
      s->cursor=YYCURSOR;
      YYCURSOR=YYLIMIT-1;
      RETURN(s,T_COMMENT);
  }

  WS* [#] {
      s->cursor=YYCURSOR;
      YYCURSOR=YYLIMIT-1;
      RETURN(s,T_PRAGMA);
  }

  SOL WS* EOL {
      s->cursor++;
      s->nextstate=S_LIMBO;
      YYCURSOR=YYLIMIT-1;
      RETURN(s,T_EMPTYLINE);
  }
  
  WS* EOL {
      if (s->state & S_ANYFIELD) s->nextstate=S_TUNE;
      YYCURSOR[-1]='\0';
      RETURN(s,T_ENDLINE);
  }
  
  [&]  { RETURN(s,T_OVERLAY); }
    
  any { return -1;}
  
  */
}

static int abcNT_FIELD_H(abcScanner *s)
{
  YYCTYPE *cursor, *limit, *marker;
  
  cursor = s->cursor;
  limit  = s->limit;
  marker = s->marker;
  
  /*!re2c
  
  SOL WS* L [:] { return -1; }
  SOL WS* "%%"  { return -1; }
  SOL WS* EOL   { return -1; }
  EOS           { return -1; }
  EOL           { YYCURSOR[-1]='\0';
                  YYCURSOR=YYLIMIT;
                  RETURN(s,T_ENDLINE);
                }
  any           { YYCURSOR=YYLIMIT-1;
                  RETURN(s,T_FIELDB);
                }
  
  */

  
}

static int abcNT_FIELD_w(abcScanner *s)
{
  YYCTYPE *cursor, *limit, *marker;
  
  cursor = s->cursor;
  limit  = s->limit;
  marker = s->marker;

note:    
  /*!re2c
    SOL              { s->cursor++; goto note; }
    
    WS+              { RETURN(s,T_LYR_SPACE); }

    (L | "\\" NWS | [(),.?!'~])+"-"?
                     { RETURN(s,T_LYR_SYLL); }
    
    [*]              { RETURN(s,T_LYR_BLANK); }

    MIN              { RETURN(s,T_LYR_SYLL); }
    
    [_]              { RETURN(s,T_LYR_CONT); }

    [|]              { RETURN(s,T_LYR_BAR); }
    
    "]"              { if (s->state & S_INFIELD) { 
                         s->nextstate=S_TUNE;
                         RETURN(s,T_NONE);
                       }
                       RETURN(s,T_UNKNOWN);
                     }
                     
    NL               { RETURN(s,T_CONTINUE); }
    
    EOL              { return -1; }
    
    any              { RETURN(s,T_LYR_SYLL); }
    
  */
  
}

static int abcNT_FIELD_s(abcScanner *s)
{
  YYCTYPE *cursor, *limit, *marker;
  
  cursor = s->cursor;
  limit  = s->limit;
  marker = s->marker;

  STATE(symbol) {
    /*!re2c
      SOL                  { s->cursor++; GOTO(symbol); }
      
      WS+                  { RETURN(s,T_WSPACE); }
      
      [|]                  { RETURN(s,T_BAR); }
    
      DEC                  { RETURN(s,T_DECOR); }
    
      [*]                  { RETURN(s,T_DECOR_BLANK); }
      
      CHRD                 { RETURN(s,T_CHORD); }
    
      ANN                  { RETURN(s,T_ANNOTATION); }
      
      STR                  { RETURN(s,T_STRING); }
      
      BRK                  { RETURN(s,T_BREAK); }
 
      "]"                  { if (s->state & S_INFIELD) { 
                               s->nextstate=S_TUNE;
                               RETURN(s,T_NONE);
                             }
                             RETURN(s,T_UNKNOWN);
                           }
                             
      EOL                  { return -1; }  

      NL                   { RETURN(s,T_CONTINUE); }
          
      any                  { while (*YYCURSOR > EOL &&
                                    !isspace(*YYCURSOR))
                               YYCURSOR++;
                             RETURN(s,T_UNKNOWN);
                           }    
    */
  } 
}
/*
    "[" L [:] (any\[\135])* "]"
                         { RETURN(s,T_INFIELD); }
*/

static int abcNT_TUNE(abcScanner *s)
{

  YYCTYPE *cursor, *limit, *marker;
  YYCTYPE *p,*q;
  
  cursor = s->cursor;
  limit  = s->limit;
  marker = s->marker;

  

  STATE(tune) { 
    /*!re2c
      
      SOL                  { s->cursor++; GOTO(tune); }
      
      EOL                  { RETURN(s,T_ENDLINE); }
      
      "`"                  { RETURN(s,T_BSPACE); }
      
      "[" L [:]            { s->cursor++;
                             s->nextstate = S_INFIELD | *(s->cursor);
                             RETURN(s,T_INFIELD); }
      NL WS* L [:]         { p=s->cursor;
                             q=p+1; skipspace(q);
                             while (*q > '\002')
                               *p++=*q++;
                             *p++=']'; *p++='\n'; *p='\0';
                             YYLIMIT=p;
                             YYCURSOR=s->cursor+2;       
                             s->nextstate = S_INFIELD | *(s->cursor);
                             RETURN(s,T_INFIELD); }
           
      WS+                  { RETURN(s,T_WSPACE); }
    
      N                    { RETURN(s,T_NOTE); }
    
      [z] (D | [/])*       { RETURN(s,T_REST); }
    
      [x] (D | [/])*       { RETURN(s,T_INVREST); }
    
      [Z] D*               { RETURN(s,T_MULTIREST); }
    
      [y]                  { RETURN(s,T_SPACER); }
    
      BAR                  { RETURN(s,T_BAR); }
    
      DEC                  { RETURN(s,T_DECOR); }
    
      [(] D ([:] D?)*      { RETURN(s,T_NPLET); }
    
      "."? "(" [',]?       { RETURN(s,T_OPENSLUR); }
    
      [)]                  { RETURN(s,T_CLOSESLUR); }
    
      [<]+                 { RETURN(s,T_DOTRIGHT); }
    
      [>]+                 { RETURN(s,T_DOTLEFT); }
        
      "."? "-" [',]?       { RETURN(s,T_TIE); }
    
      "[%" D* "]"          { RETURN(s,T_DUPMESURE); }
      
      "["? D (D | "," | "-")*
                           { RETURN(s,T_REPEAT); }
      
      "["                  { RETURN(s,T_CHORDSTART); }
      
      "]"                  { RETURN(s,T_CHORDEND); }
      
      CHRD                 { RETURN(s,T_CHORD); }
    
      ANN                  { RETURN(s,T_ANNOTATION); }
      
      STR                  { RETURN(s,T_STRING); }
    
      "{/"                 { RETURN(s,T_GRACEACC); }
      [{]                  { RETURN(s,T_GRACEAPP); }
      [}]                  { RETURN(s,T_GRACEEND); }
      
      [\041]               { RETURN(s,T_BREAK); }

     
      NL                   { RETURN(s,T_CONTINUE); }
    
      any                  { return -1; }  
    */
  }
}


/*
** This is the main function. It recognize a new token in the buffer,
** sets the scanner internals appropriately and returns the length
** of the token.
*/

int ABCAPI abcNextToken(abcScanner *s)
{

  YYCTYPE *cursor, *limit, *marker;
  int res=-1;
  int chk;

  /* Avoid calls past the end of file */  
  if (s->state == S_EOF) return -1;

  /* Reset the character saved if any */
  if (s->lastch) *(s->cursor) = s->lastch;

  /* Change to a new state if required */
  if (s->nextstate != S_NONE) {
    s->state=s->nextstate;
    s->nextstate = S_NONE;
  }

  /* Get a new line */  
  if (m_lineempty(s)) abcGetLine(s);

  /* Line is still empty? Must be the end of file!! */  
  if (m_lineempty(s)) {
    m_eof(s);
    return -1;
  }

  cursor = s->cursor;
  limit  = s->limit;
  marker = s->marker;

  /* Look for lines in the history field (H:) */
  if (s->state == (S_FIELD | 'H'))  res=abcNT_FIELD_H(s);
  if (res >= 0) return res;
  
  /* Check for abcTok valid regardless the state*/
  res=abcNT(s);
  if (res >= 0) return res;

  /* If we are in the "limbo" (before o between
  ** songs) consider any line as simple text.
  */
  if (s->state == S_LIMBO) {
    YYCURSOR=YYLIMIT;
    RETURN(s,T_TEXT);
  }

  if (s->state & S_CFIELD) {
    chk = s->state & 0xFF;
    /* Look for syllables in a lyrics line (w:) */
    if (chk ==  'w')  res=abcNT_FIELD_w(s);
    if (res >= 0) return res;
    
    /* Look for symbols in a symbol line (s:) */
    if ((chk == 's') || (chk == 's'))  res=abcNT_FIELD_s(s);
    if (res >= 0) return res;
  }
  
  /* Return the chars up to "]" as content for the fields */
  if (s->state & S_INFIELD) {
    while (*YYCURSOR && (*YYCURSOR != ']')) {
      YYCURSOR++;
      if (*YYCURSOR == '\\' && YYCURSOR[1]) YYCURSOR++;
    }
    if (*YYCURSOR == ']') {
      *YYCURSOR++='\0';
      s->nextstate=S_TUNE;
    }
    RETURN(s,T_FIELDB);
  }
  /**/
  /* Return the entire line as content for the field but stop
     if a comment is found!
  */
  if (s->state & (S_EXTFIELD | S_FIELD)) {
    int instring=0;
    int infield=1;
    
    while (infield) {
      switch(*YYCURSOR) {
        case '\\': if (YYCURSOR[1]) YYCURSOR += 2; break;
        case '"' : instring ^=1; YYCURSOR++; break;
        case '%' : infield=instring; break;
        default:   YYCURSOR++;
      }
      if (infield) infield = (YYCURSOR < YYLIMIT-1);
    }
    
    RETURN(s,T_FIELDB);
  }

  /* Get notes and such from the tune */  
  if (s->state == S_TUNE) res=abcNT_TUNE(s);

  /* Nothing recognized! Report as "unkonwn" */  
  if (res == -1) {
    YYCURSOR=s->cursor+1;
    RETURN(s,T_UNKNOWN);
  }
  
  return res;
}

/*
** Scanner creation routines
*/

void ABCAPI abcClose(abcScanner *s)
{
   if (m_guarded(s)) {
     if (s->file)   fclose(s->file);
     s->file=NULL;
     m_unguard(s);
     free(s);
   }
}

/*
  The scanner does a single memory allocation. The buffer is split in 
  different areas. Is there any danger of trashing those areas? YES!
  We should be very careful!
                                     
   ___bufsize__     __len(fname)__      
  /            \   /              \     
  +------//-----+-+------//--------+-+
  |             |0|                |0|
  +------//-----+-+------//--------+-+
   line/string         filename         
   to be parsed   
  
   _____________bufsize___________    
  /                               \   
  +---------------//---------------+-+
  |                                |0|
  +---------------//---------------+-+
   line/string     
   to be parsed   
                  
*/

static abcScanner *abcNew(ULONG bufsize)
{
  abcScanner *s=NULL;
  ULONG realsize;

  if (bufsize < MINBUFSIZE) bufsize=MINBUFSIZE;
  if (bufsize > MAXBUFSIZE) bufsize=MAXBUFSIZE;
  
  s=malloc( sizeof(abcScanner) + bufsize+16);
  if (s) {
    m_unguard(s);
    s->bufsize=bufsize;
    memset(s->buffer,0,bufsize+16);
    s->line = 0;
    s->state = S_LIMBO;
    s->nextstate = S_NONE;
    s->token = T_NONE;
    s->file = NULL;
    s->filename=NULL;
    s->tokstr=NULL;
    m_guard(s);
    m_resetbuf(s);
    return (s);
  }
  if (s) free(s);
  return (NULL);
}

abcScanner * ABCAPI abcFileScanner(char *filename,ULONG bufsize)
{
  abcScanner *s=NULL;
  
  if (filename != NULL) {
    s=abcNew(bufsize + strlen(filename)+1);
    if (s) {
      s->file=fopen(filename,"r");
      if (s->file) {
        s->bufsize -= strlen(filename)+1;
        s->filename=s->buffer+s->bufsize+1;
        strcpy(s->filename,filename);
      }
      else {
        abcClose(s);
        s=NULL;
      }
    }
  } 
  return(s);
}

abcScanner * ABCAPI abcStringScanner(char *tune)
{
  abcScanner *s=NULL;
  char *b;
  
  if (tune != NULL) {
    s=abcNew(strlen(tune) + 16 );
    /*printf("+\t[%s]\n",tune);*/
    if (s) {
      b=s->buffer+4;
      s->nextln=b;
      s->limit=s->nextln-1;
      while (*tune) 
        *b++ = *tune++;
      *b = '\0';
      s->line=1;
    }
    /*printf("-\t[%s]\n",s->buffer);
    printf("-\t[%s]\n",s->nextln);*/
  } 
  return(s);
}

static int abcScan(abcScanner *as,abcHandler handler)
{
   if (as) {
    while (as->state != S_EOF) {
      abcNextToken(as);
      switch(abcToken(as)) {
        case T_FIELD: 
        case T_INFIELD: 
        case T_NONE:  break;
        
        default: if (handler) {
                   if (handler(as) > 0)
                     m_eof(as);
                 }
                 else {
                   printf("%s\t\t", abcTokenName(as->token));
                   printf("[%s]\n", as->tokstr);
                 }
      }
    }
    abcClose(as);
    return 0;
  }
  return 1; 
}

int ABCAPI abcScanFile(char *filename,abcHandler handler)
{
  abcScanner *as;
    
  as=abcFileScanner(filename,1024);
  return(abcScan(as,handler));
}


int ABCAPI abcScanString(char *buffer,abcHandler handler)
{
  abcScanner *as;
    
  as=abcStringScanner(buffer);
  return(abcScan(as,handler));
}


const char * ABCAPI abcTokenName(int n)
{
  return abcTokName[((n>T_FIRST && n<T_LAST)?n:T_UNKNOWN)];
}

const char * ABCAPI abcStateName(int s)
{
  static char name[80];
  
  name[0]='\0';
  
  if (s == S_EOF)          return (abcStName[0]);
  else if (s == S_ERROR)   return (abcStName[1]);
  else if (s == S_LIMBO)   return (abcStName[2]);
  else if (s == S_NONE)    return (abcStName[3]);
  else if (s == S_TUNE)    return (abcStName[4]);
  else if (s & S_FIELD)    strcpy(name,abcStName[5]);
  else if (s & S_EXTFIELD) strcpy(name,abcStName[6]);
  else if (s & S_INFIELD)  strcpy(name,abcStName[7]);
  
  if (s & S_CFIELD) {
    char *l=name;
    while (*l) l++;
    sprintf(l,"_%c",s & 0xFF);
  }
  else if (s & S_EXTFIELD) {
    char *l=name;
    while (*l) l++;
    sprintf(l,"_%03X",s & 0x0FFF);
  }
  return(name);
}

int ABCAPI abcToken(abcScanner *s)
{ return(s->token); }

int ABCAPI abcState(abcScanner *s)
{ return(s->state); }

const char * ABCAPI abcString(abcScanner *s)
{ return(s->tokstr); }

const abcPacked ABCAPI abcParsedString(abcScanner *s)
{
  if (s->pack[0]=='\0') abcNparse(s);
  return(s->pack);
}

const char * ABCAPI abcFilename(abcScanner *s)
{ return(s->filename); }

int ABCAPI abcLine(abcScanner *s)
{ return(s->line); }

int ABCAPI abcColumn(abcScanner *s)
{ return(m_column(s)); }


