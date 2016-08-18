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
    ll height = sqrt(R2 - i*i);
    ll tmp = 0;
    npoints += height;
    //if( npoints > TOMOD ) npoints %= TOMOD;
    tmp = height * height;
    tmp += (height * (height+1)/2);
    tmp %= TOMOD;
    tmp *= i;
    tmp %= TOMOD;
    nsolutions += (tmp*4) % TOMOD;
    /* cross four */
    tmp = sqrt(R2 - height*height);
    nsolutions += (tmp*height*height)%TOMOD;
  }
}

int main(void)
{
  scanf("%lld", &R);
  R2 = R*R;
  calc();
  printf("%lld\n", nsolutions%TOMOD);
  return 0;
}
