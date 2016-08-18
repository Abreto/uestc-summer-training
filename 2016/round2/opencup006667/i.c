/* UESTC Summer Training Western Subregional 2015. */
/* Problem I, by Abreto. */
#include <stdio.h>
#include <math.h>

#define TOMOD 1000002015

typedef long long int ll;

ll R = 0, R2 = 0;
ll npoints = 0; /* border not included */
ll nsolutions = 0;

void calc(void)
{
  ll i = 0;
  for(i = 1;i < R;++i)
  {
    ll height = sqrtl(R2 - i*i);
    ll tmp = 0;
    npoints += height;
    //if( npoints > TOMOD ) npoints %= TOMOD;
    tmp = height * height;
#ifdef LOCALDEBUG
  printf("tmp:%lld\n", tmp);
#endif
    tmp += (height * (height+1)/2);
    tmp %= TOMOD;
#ifdef LOCALDEBUG
  printf("tmp:%lld\n", tmp);
#endif
    tmp *= i;
#ifdef LOCALDEBUG
  printf("tmp:%lld\n", tmp);
#endif
    tmp %= TOMOD;
#ifdef LOCALDEBUG
  printf("tmp:%lld\n", tmp);
#endif
    nsolutions += (tmp*4) % TOMOD;
  }
  /* cross four */
  #ifdef LOCALDEBUG2
    printf("%lunpoints:%lld\n", sizeof(ll),(npoints%TOMOD)*(npoints%TOMOD));
  #endif
  npoints %= TOMOD;
  nsolutions += npoints * npoints % TOMOD;
}

int main(void)
{
  scanf("%lld", &R);
  R2 = R*R;
  calc();
  printf("%lld\n", nsolutions%TOMOD);
  return 0;
}
