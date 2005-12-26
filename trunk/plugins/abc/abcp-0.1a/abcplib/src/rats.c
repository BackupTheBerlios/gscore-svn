/* A simple rational numbers handling.
   Assumes ULONG has at least 32 bits space */

#include "abcp.h"
   
RATIONAL RAT_CMP(RATIONAL r, RATIONAL s) 
{ 
  int x;
  x=RAT_NUM(r)*RAT_DEN(s) - (RAT_NUM(s)*RAT_DEN(r));
  return (x == 0? 0 : (x>0? 1: -1));
}

static int gcd(int n, int m)
{
  int t;
  
  if (n<m) { t=n; n=m; m=t; }
  
  while (m>0) {
    t = m;  m = n%m;  n = t;
  }
  return n;
}


RATIONAL RAT_SIMPLIFY(RATIONAL r)
{
  int a,b,t;
  a=RAT_NUM(r);
  b=RAT_DEN(r);

  t=gcd(a,b);
  return (RAT(a/t,b/t));
}
