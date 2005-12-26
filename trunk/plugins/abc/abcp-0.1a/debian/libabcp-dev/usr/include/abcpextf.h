/* table for the mapping for the perfect hash */

typedef  unsigned long long  ub8;
typedef  unsigned long  int  ub4;
typedef  unsigned short int  ub2;
typedef  unsigned       char ub1;

#define PHASH phash
#define PHASHNKEYS 81  /* How many keys were hashed */

ub4  lookup( ub1 *k, ub4 length, ub4 level );
void checksum( ub1 *k, ub4 length, ub4 *state);
ub2 shash(ub1 *str);


#ifndef STATIC
#define STATIC
#endif

/* small adjustments to _a_ to make values distinct */
static ub1 tab[] = {
0,70,0,0,1,10,28,61,0,0,10,0,4,10,0,28,
0,1,0,32,0,1,47,0,0,85,0,61,0,0,0,16,
108,1,0,0,0,119,1,47,108,0,119,101,47,76,1,0,
34,60,0,1,70,76,0,79,70,112,108,100,95,0,10,61,
};

/* The hash function */
STATIC ub4 phash(key, len)
char *key;
int   len;
{
  ub4 rsl, val = lookup(key, len, 0x9e3779b9);
  rsl = ((val>>26)^tab[val&0x3f]);
  return rsl;
}

static ub4 codes[]={
/*      */ 0x00000000 };
#define code(s) codes[phash(s,strlen(s))]
