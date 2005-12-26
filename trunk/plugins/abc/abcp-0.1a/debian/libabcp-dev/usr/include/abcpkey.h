/* table for the mapping for the perfect hash */

typedef  unsigned long long  ub8;
typedef  unsigned long  int  ub4;
typedef  unsigned short int  ub2;
typedef  unsigned       char ub1;

#define PHASH phash
#define PHASHNKEYS 0  /* How many keys were hashed */

ub4  lookup( ub1 *k, ub4 length, ub4 level );
void checksum( ub1 *k, ub4 length, ub4 *state);
ub2 shash(ub1 *str);


#ifndef STATIC
#define STATIC
#endif

/* The hash function */
STATIC ub4 phash(key, len)
char *key;
int   len;
{
  ub4 rsl = 0;
  return rsl;
}

static ub4 codes[]={ 
/*      */ 0x00000000 }; 
#define code(s) codes[phash(s,strlen(s))] 
