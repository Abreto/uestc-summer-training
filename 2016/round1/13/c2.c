/* UESTC 2016 Summer Training #13 Div.2. Problem C, by Abreto, 20160725. */
#include <stdio.h>

typedef long long int ll;

int main(void)
{
  int T = 0, K = 0;
  ll N = 0;

  scanf("%d", &T);
  while(T--)
  {
    ll yu = 0;
    scanf("%lld %d", &N, &K);
    yu = (N%100);
    N -= yu;
    while(K--)
    {
      yu = yu<<1;
      if( yu >= 100 )
      {
        N += 100;
        yu -= 100;
      }
    }
    printf("%lld\n", N+yu);
  }

  return 0;
}
