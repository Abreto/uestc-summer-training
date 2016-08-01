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
    while(K--)
    {
      N += (N%100);
      printf("%lld\n", N);
    }
    printf("%lld\n", N);
  }

  return 0;
}
