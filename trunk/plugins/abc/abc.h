/* abc.h - header file shared by abc2midi, abc2abc and yaps */
/* Copyright James Allwright 2000 */
/* may be copied under the terms of the GNU public license */

#ifndef _ABC_H_
#define _ABC_H_

#include <glib.h>

/* define types of abc object */
typedef enum {
/* types of bar sign */
SINGLE_BAR,
DOUBLE_BAR,
BAR_REP,
REP_BAR,
PLAY_ON_REP,
REP1,
REP2,
/* BAR1 = SINGLE_BAR + REP1 */
/* REP_BAR2 = REP_BAR + REP2 */
BAR1,
REP_BAR2,
DOUBLE_REP,
THICK_THIN,
THIN_THICK,
/* other things */
PART,
TEMPO,
TIME,
KEY,
REST,
TUPLE,
/* CHORD replaced by CHORDON and CHORDOFF */
NOTE,
NONOTE,
OLDTIE,
TEXT,
SLUR_ON,
SLUR_OFF,
TIE,
CLOSE_TIE,
TITLE,
CHANNEL,
TRANSPOSE,
RTRANSPOSE,
GRACEON,
GRACEOFF,
SETGRACE,
SETC,
GCHORD,
GCHORDON,
GCHORDOFF,
VOICE,
CHORDON,
CHORDOFF,
DRUMON,
DRUMOFF,
SLUR_TIE,
TNOTE,
/* broken rhythm */
LT,
GT,
DYNAMIC,
LINENUM,
MUSICLINE,
MUSICSTOP,
WORDLINE,
WORDSTOP,
INSTRUCTION,
NOBEAM,
CHORDNOTE,
CLEF,
PRGINTLINE,
NEWPAGE,
LEFT_TEXT,
CENTRE_TEXT,
VSKIP
} featuretype;

/* note decorations */
#define DECSIZE 9
extern gchar decorations[];
#define STACCATO 0
#define TENUTO 1
#define LOUD 2
#define ROLL 3
#define FERMATA 4
#define ORNAMENT 5
#define TRILL 6
#define BOWUP 7
#define BOWDOWN 8

/* The vstring routines provide a simple way to handle */
/* arbitrary length strings */
struct vstring {
gint len;
gint limit;
gchar* st;
};
#ifndef KANDR
/* vstring routines */
extern void initvstring(struct vstring* s);
extern void extendvstring(struct vstring* s);
extern void addch(gchar ch, struct vstring* s);
extern void addtext(gchar* text, struct vstring* s);
extern void clearvstring(struct vstring* s);
extern void freevstring(struct vstring* s);
/* error-handling routines */
extern void event_error(gchar *s);
extern void event_fatal_error(gchar *s);
extern void event_warning(gchar *s);
#else
/* vstring routines */
extern void initvstring();
extern void extendvstring();
extern void addch();
extern void addtext();
extern void clearvstring();
extern void freevstring();
/* error-handling routines */
extern void event_error();
extern void event_fatal_error();
extern void event_warning();
#endif

#endif
