/* Generated by re2c 0.5 on Fri Dec 31 13:56:17 2004 */
#line 1 "abcpmeter.re"

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


#line 55



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
    
  {
	YYCTYPE yych;
	unsigned int yyaccept;
	goto yy0;
yy1:	++YYCURSOR;
yy0:
	if((YYLIMIT - YYCURSOR) < 4) YYFILL(4);
	yych = *YYCURSOR;
	if(yych <= 'c'){
		if(yych <= 'B'){
			if(yych >= '\001')	goto yy8;
			goto yy2;
		} else {
			if(yych <= 'C')	goto yy3;
			if(yych <= 'b')	goto yy8;
			goto yy3;
		}
	} else {
		if(yych <= 'f'){
			if(yych <= 'e')	goto yy8;
			goto yy7;
		} else {
			if(yych == 'n')	goto yy5;
			goto yy8;
		}
	}
yy2:	YYCURSOR = YYMARKER;
	switch(yyaccept){
	case 0:	goto yy6;
	}
yy3:	yych = *++YYCURSOR;
	if(yych == '|')	goto yy15;
	goto yy4;
yy4:
#line 90
	{ d=4; nlen=1; GOTO(gotmeter); }
yy5:	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych == 'o')	goto yy13;
	goto yy6;
yy6:
#line 93
	{YYCURSOR-- ; GOTO(numerator); }
yy7:	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	if(yych == 'r')	goto yy9;
	goto yy6;
yy8:	yych = *++YYCURSOR;
	goto yy6;
yy9:	yych = *++YYCURSOR;
	if(yych != 'e')	goto yy2;
	goto yy10;
yy10:	yych = *++YYCURSOR;
	if(yych != 'e')	goto yy2;
	goto yy11;
yy11:	yych = *++YYCURSOR;
	goto yy12;
yy12:
#line 92
	{ d=1; nlen=4; GOTO(gotmeter); }
yy13:	yych = *++YYCURSOR;
	if(yych != 'n')	goto yy2;
	goto yy14;
yy14:	yych = *++YYCURSOR;
	if(yych == 'e')	goto yy11;
	goto yy2;
yy15:	yych = *++YYCURSOR;
	goto yy16;
yy16:
#line 91
	{ d=2; nlen=2; GOTO(gotmeter); }
}
#line 95

     
  STATE(numerator) { 
    YYSTART=YYCURSOR;
    m=0;
  
    STATE(num) {
      {
	YYCTYPE yych;
	unsigned int yyaccept;
	goto yy17;
yy18:	++YYCURSOR;
yy17:
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= ' '){
		if(yych <= '\n'){
			if(yych <= '\000')	goto yy29;
			if(yych <= '\b')	goto yy31;
			goto yy19;
		} else {
			if(yych == '\r')	goto yy19;
			if(yych <= '\037')	goto yy31;
			goto yy19;
		}
	} else {
		if(yych <= '+'){
			if(yych == ')')	goto yy25;
			if(yych <= '*')	goto yy31;
			goto yy23;
		} else {
			if(yych <= '.')	goto yy31;
			if(yych <= '/')	goto yy27;
			if(yych <= '9')	goto yy21;
			goto yy31;
		}
	}
yy19:	yych = *++YYCURSOR;
	goto yy34;
yy20:
#line 103
	{ GOTO(num); }
yy21:	yych = *++YYCURSOR;
	goto yy22;
yy22:
#line 104
	{ m = m*10 + (YYCURSOR[-1] - '0');
                        YYEND=YYCURSOR; GOTO(num);
                      }
yy23:	yych = *++YYCURSOR;
	goto yy24;
yy24:
#line 107
	{ n += m; m=0;    GOTO(num); }
yy25:	yych = *++YYCURSOR;
	goto yy26;
yy26:
#line 108
	{ pak[2] |= 4;    GOTO(skipslash); }
yy27:	yych = *++YYCURSOR;
	goto yy28;
yy28:
#line 109
	{                 GOTO(denominator); }
yy29:	yych = *++YYCURSOR;
	goto yy30;
yy30:
#line 111
	{ YYCURSOR--;     GOTO(denominator); }
yy31:	yych = *++YYCURSOR;
	goto yy32;
yy32:
#line 113
	{ setperr(pak,1); GOTO(got); }
yy33:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy34;
yy34:	if(yych <= '\f'){
		if(yych <= '\b')	goto yy20;
		if(yych <= '\n')	goto yy33;
		goto yy20;
	} else {
		if(yych <= '\r')	goto yy33;
		if(yych == ' ')	goto yy33;
		goto yy20;
	}
}
#line 114

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
  
      {
	YYCTYPE yych;
	unsigned int yyaccept;
	goto yy35;
yy36:	++YYCURSOR;
yy35:
	if((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if(yych <= '\r'){
		if(yych <= '\b'){
			if(yych <= '\000')	goto yy39;
			goto yy42;
		} else {
			if(yych <= '\n')	goto yy41;
			if(yych <= '\f')	goto yy42;
			goto yy41;
		}
	} else {
		if(yych <= ' '){
			if(yych <= '\037')	goto yy42;
			goto yy41;
		} else {
			if(yych <= '/')	goto yy42;
			if(yych >= ':')	goto yy42;
			goto yy37;
		}
	}
yy37:	yych = *++YYCURSOR;
	goto yy38;
yy38:
#line 139
	{ m = m*10 + (YYCURSOR[-1] - '0');
                         GOTO(den);
                       }
yy39:	yych = *++YYCURSOR;
	goto yy40;
yy40:
#line 142
	{ GOTO(gotden); }
yy41:	yych = *++YYCURSOR;
	goto yy45;
yy42:	yych = *++YYCURSOR;
	goto yy43;
yy43:
#line 144
	{ setperr(pak,2); GOTO(got); }
yy44:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	goto yy45;
yy45:	if(yych <= '\f'){
		if(yych <= '\b')	goto yy40;
		if(yych <= '\n')	goto yy44;
		goto yy40;
	} else {
		if(yych <= '\r')	goto yy44;
		if(yych == ' ')	goto yy44;
		goto yy40;
	}
}
#line 145

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
