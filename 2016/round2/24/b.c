/* UESTC Summer Training #25. Problem H. by Abreto.*/
#include <stdio.h>

typedef long long int ll;

typedef struct __rationalnumber
{
  ll up;
  ll down;
}rationalnumber, *p_rationalnumber;

ll gcd(ll m, ll n)
{
  if( 0 == n )
    return m;
  else
    return gcd(n, m%n);
}

rationalnumber reduce(rationalnumber x)
{
  ll com = gcd(x.up, x.down);
  x.up /= com;
  x.down /= com;
  return x;
}

rationalnumber dot(rationalnumber r1, rationalnumber r2)
{
  rationalnumber r1.up *= rationalnumber r2.up;
  rationalnumber r1.down *= rationalnumber r2.down;
  r1 = reduce(r1);
  return r1;
}

int n = 0, k = 0;

int main(void)
{
  return 0;
}
