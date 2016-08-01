/* UESTC 2016 Summer Training #17 Div.2. Problem B, by Abreto, 20160728. */
#include <stdio.h>

typedef unsigned long long int ll;

int main(void)
{
  int T = 0;
  int n = 0, k = 0;
  int teams[10010] = {0};
  ll nmatches = 0;

  scanf("%d", &T);
  while(T--)
  {
    int i = 0;
    int base = 0;
    scanf("%d %d", &n, &k);
    base = n/k;
    for(i = 0;i < k;++i)
    {
      teams[i] = base;
    }
    base = n % k;
    for(i = 0;i < base;++i)
    {
      teams[i]++;
    }
    base = n;
    for(nmatches = 0, i = 0;i < k;++i)
    {
      base -= teams[i];
      nmatches += (ll)(teams[i]) * (ll)(base);
    }

    printf("%llu\n", nmatches);
  }

  return 0;
}
