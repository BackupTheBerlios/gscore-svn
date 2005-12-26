
#include "abcp.h"

/*
  I also considered suggestions given in the following message:
  http://www.mail-archive.com/abcusers@argyll.wisemagic.com/msg05924.html

  012345
  DEGGNN
    \___ "   " means "unknown"

-- BEGIN DECORATIONS  
    - 1 dynamics signs
       0101 pppp pianissississimo
       0102 ppp  pianississimo
       0103 pp   pianissimo
       0104 p    piano
       0105 mp   mezzopiano
       0106 mf   mezzoforte
       0107 f    forte
       0108 ff   fortissimo
       0109 fff  fortississimo
       010A ffff fortissississimo
       010B fp   fortepiano
       010C sfz  fz sforzando
       010D rfz  rf rinforzando
       010E sfp  sforzandopiano 
       010F niente n
       0110 sffff  subitoffff subitofortissississimo
       0111 sfff   subitofff  subitofortississimo
       0112 sff    subitoff   subitofortissimo
       0113 sf     subitof    subitoforte
       0114 smf    subitomf   subitomezzoforte
       0115 smp    subitomp   subitomezzopiano
       0116 sp     subitop    subitopiano
       0117 spp    subitopp   subitopianissimo
       0118 sppp   subitoppp  subitopianississimo
       0119 spppp  subitopppp subitopianissississimo
       011A crescendo(  <(
       011B crescendo)  <)
       011C diminuendo( >(
       011D diminuendo) >)
       011E glissando(  g(
       011F glissando)  g)
       0120 glissando   g     
        
     -2 Fingering
       0201 1
       0202 2
       0203 3
       0204 4
       0205 5
       0206 arpeggio
       0207 arpeggioup
       0208 arpeggiodown
       0209 arrow
       020A arrowup
       020B arrowdown
       020C noarpeggio 
       020D H.O. hammeringon
       020E P.O. pulloff
       020F SL.  sliding
       0210 W.   wham
        
     -A Articulation
       0A01 accent   >   L    emphasis
       0A02 marcato
       0A03 staccatissimo
       0A04 staccato .
       0A05 tenuto
       0A06 portato
       0A07 upbow
       0A08 downbow
       0A09 flageolet
       0A0A thumb
       0A0B lheel
       0A0C rheel
       0A0D ltoe
       0A0E rtoe
       0A0F open
       0A10 stopped
       0A11 turn
       0A12 reverseturn  invertedturn
       0A13 trill        tr   T
       0A14 prall
       0A15 mordent      lowermordent  M
       0A16 prallprall
       0A17 prallmordent
       0A18 upprall
       0A19 downprall
       0A1A upmordent    uppermordent P  pralltriller
       0A1B downmordent  
       0A1C pralldown
       0A1D prallup
       0A1E lineprall
       0A1F signumcongruentiae
       0A20 slide J
       0A21 turnx
       0A22 reverseturnx   invertedturnx
       0A23 trill(    tr(
       0A24 trill)    tr)
       0A25 roll ~ irishroll
        
    - 3 percussions
       0301 gong
       0302 triangle
       0303 halfopenhihat
       0304 hardstick
       0305 softstick
       0306 metalstick
       0307 rubberstick
       0308 trianglestick
       0309 wirebrush
       030A woodstick
       030B tinklebell
       030C agogo
       030D steeldrums
       030E woodblock
       030F taikodrum
       0310 melodictom
       0311 synthdrum
       0312 reversecymbal
       0323 acousticbassdrum
       0324 bassdrum1
       0325 sidestick
       0326 acousticsnare             snare
       0327 handclap
       0328 electricsnare
       0329 lowfloortom
       032A closedhihat               hihat
       032B highfloortom  
       032C pedalhihat
       032D lowtom
       032E openhihat
       032F lowmidtom
       0330 himidtom
       0331 crashcymbal1              cymbal
       0332 hightom
       0333 ridecymbal1
       0334 chinesecymbal
       0335 ridebell
       0336 tambourine
       0337 splashcymbal
       0338 cowbell
       0339 crashcymbal2
       033A vibraslap
       033B ridecymbal2
       033C hibongo
       033D lowbongo
       033E mutehiconga
       033F openhiconga
       0340 lowconga
       0341 hightimbale
       0342 lowtimbale
       0343 highagogo
       0344 lowagogo
       0345 cabasa
       0346 maracas
       0347 shortwhistle
       0348 longwhistle
       0349 shortguiro
       034A longguiro
       034B claves
       034C hiwoodblock
       034D lowwoodblock
       034E mutecuica
       034F opencuica
       0350 mutetriangle
       0351 opentriangle        
         
    - 4 pedal
        
       0401 damppedal ped 
       0402 sostpedal mped
       0404 softpedal lped
       
       0421 damppedal) ped) 
       0422 sostpedal) mped)
       0424 softpedal) lped)
       
       0411 damppedal( ped( 
       0412 sostpedal( mped( 
       0414 softpedal( lped( 

    - 5 pause
       0501 breath ,
       0502 fermata      hold       H
       0503 shortfermata
       0504 longfermata
       0505 verylongfermata
       0506 generalpause G.P.
       0507 caesura pause rr //
       0508 reversefermata invertedfermata ufermata udfermata
       0509 grandpause
                        
    - 6 misc
       0601 segno   S
       0602 coda    O
       0603 D.S.
       0604 D.C. 
       0605 dacoda
       0606 dacapo
       0607 dalsegno
       0608 fine
       0609 varcoda
       060A shortphrase
       060B mediumphrase
       060C longphrase
       060D 8va(
       060E 8va)
       060F 8vab(
       0610 8vab)
       0611 beamon
       0612 gmark
       0613 invisible
       
-- END DECORATIONS  
   
*/

#include "abcpdecor.h"

     
char * abcNDecoration(char *pak, char *str)
{
  char *t=NULL;
  char c;
  ub4 m,d;
  
  YYCTYPE *YYCURSOR;

  if (str==NULL || pak==NULL) return NULL;
  
  YYCURSOR=str; while (isspace(*YYCURSOR)) YYCURSOR++;
  
             /*012345*/
  setpack(pak,"DEGGNN");

  c=*YYCURSOR;
  if (c == '+' || c == '!') {
    t=++YYCURSOR;
    while (*t && *t != c) t++;
    if (*t) *t='\0';
    else t=NULL;
  }
  
  m=code(YYCURSOR);
  d=shash(YYCURSOR);
  
  if (d == (m & 0xFFFF)) {
    sethex2(pak+2,m >> 16);
  }
  
  if (t) *t=c;
  return pak;
}

