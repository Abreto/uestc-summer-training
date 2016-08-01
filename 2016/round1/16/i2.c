/* UESTC 2016 Summer Training #16 Div.2. Problem I, by Abreto, 20160727. */
#include <stdio.h>

#define TOMOD 9901

typedef unsigned long long int ll;

int a = 0, b = 0;
int factors[128] = {0};
int nfactors = 0;
int factorn[128] = {0};
int S = 1;

ll fastmod(ll base, ll exp, ll tomod)
{
  if( 1 == exp )
    return (base % tomod);
  else
  {
    ll tmp = fastmod(base, exp/2, tomod);
    ll half = tmp/2;
    ll ans = (tmp*half)%tomod;
    ans += (tmp*(tmp-half))%tomod;
    if( 0 == exp % 2 )
      return ans;
    else
      return (ans*base)%tomod;
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
      a /= i;
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
    ll sn = 0;
    sn = fastmod(factors[i], factorn[i]+1, ((ll)TOMOD)*(ll)(factors[i]-1));
    sn = (sn-1)%(((ll)TOMOD)*(ll)(factors[i]-1));
    sn /= (ll)(factors[i]-1);
    S = (S*sn)%TOMOD;
  }
  printf("%d\n", S);
  return 0;
}
