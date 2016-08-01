/* UESTC 2016 Summer Training #13 Div.2. Problem C, by Abreto, 20160725. */
#include <stdio.h>

#define LOOPLENGTH  20

typedef long long int ll;

int main(void)
{
  int T = 0, K = 0;
  ll N = 0;

  scanf("%d", &T);
  while(T--)
  {
    ll yu = 0;
    ll toadd = 0;
    scanf("%lld %d", &N, &K);
    while( (4 != (yu=(N%100))) && (K--) )
      N += yu;
    toadd = K / LOOPLENGTH;
    N += 1000 * toadd;
    K -= toadd * LOOPLENGTH;
    while( (K>0) && (K--) )
      N += (N%100);
    printf("%lld\n", N);
  }

  return 0;
}
