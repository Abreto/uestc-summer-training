/* UESTC 2016 Summer Training #16 Div.2. Problem I, by Abreto, 20160727. */
#include <stdio.h>

#define TOMOD 9901

typedef long long int ll;

int a = 0, b = 0;
int factors[128] = {0};
int nfactors = 0;
int factorn[128] = {0};
int S = 1;

ll fastmod(int base, int exp, ll tomod)
{
  if( 1 == exp )
    return (base % tomod);
  else
  {
    ll tmp = fastmod(base, exp/2, tomod);
    tmp = (tmp*tmp)%tomod;
    if( 0 == exp % 2 )
      return tmp;
    else
      return (tmp*base)%tomod;
  }
}

int main(void)
{
  int i = 0;

  scanf("%d %d", &a, &b);
  if( 0 == (a%2) )
  {
    factors[nfactors] = 2;
    factorn[nfactors] = 1;
    a /= 2;
    while( 0 == (a%2) )
    {
      a /= 2;
      factorn[nfactors]++;
    }
    factorn[nfactors] *= b;
    ++nfactors;
  }
  for(i = 3;i <= a;i+=2)
    if( 0 == (a%i) )
    {
      factors[nfactors] = i;
      factorn[nfactors] = 1;
      a /= 2;
      while( 0 == (a%i) )
      {
        a /= i;
        factorn[nfactors]++;
      }
      factorn[nfactors] *= b;
      ++nfactors;
    }

#ifdef DEBUGGING
  printf("1");
  for(i = 0;i < nfactors;++i)
    printf("*%d^%d", factors[i], factorn[i]);
  printf("\n");
#endif

  for(i = 0;i < nfactors;++i)
  {
    int j = 0;
    ll pn = 1;
    ll sn = 1;
    for(j = 0;j < factorn[i];++j)
    {
      pn = (pn*factors[i])%TOMOD;
      sn = (sn+pn)%TOMOD;
    }
    S = (S*sn)%TOMOD;
  }
  printf("%d\n", S);
  return 0;
}
