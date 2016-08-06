/* UESTC Summer Training Petrozavodsk Summer-2015. Petr Mitrichev Contest 13. */
/* Problem B */
#include <stdio.h>

#define MAXN  1000002
#define FILE_IN "baum.in"
#define FILE_OUT  "baum.out"

typedef long long int ll;

int n = 0;
int nover2 = 0;
int rest = 0;
ll values[MAXN] = {0};
ll sum[MAXN] = {0};  /* values[i] = sum[i] - sum[i-1]; */

ll ansa = 0, ansb = 0;
ll mindelta = 10000000000000000;

int main(void)
{
  int i = 0;

#ifndef LOCALDEBUG
  freopen(FILE_IN, "r", stdin);
  freopen(FILE_OUT, "w+", stdout);
#endif

  scanf("%d", &n); nover2 = n / 2; rest = n % 2;
  for(i = 0;i < n;++i)
  {
    scanf("%lld", &(values[i+1]));
    sum[i+1] = sum[i] + values[i+1];
  }

  for(i = 1;i <= nover2;++i)
  {
    ll a = sum[i+nover2-1+rest] - sum[i-1];
    ll b = sum[n] - a;
    int delta = 0;
    if( a < b )
    {
      a = a^b;
      b = a^b;
      a = a^b;
    }
    delta = a - b;
    if( delta < mindelta )
    {
      mindelta = delta;
      ansa = a;
      ansb = b;
    }
    else if( delta == mindelta && a > ansa )
    {
      ansa = a;
      ansb = b;
    }
  }
  if( rest )
    for(i = 1;i <= nover2+1;++i)
    {
      ll a = sum[i+nover2-1] - sum[i-1];
      ll b = sum[n] - a;
      int delta = 0;
      if( a < b )
      {
        a = a^b;
        b = a^b;
        a = a^b;
      }
      delta = a - b;
      if( delta < mindelta )
      {
        mindelta = delta;
        ansa = a;
        ansb = b;
      }
      else if( delta == mindelta && a > ansa )
      {
        ansa = a;
        ansb = b;
      }
    }

  printf("%lld %lld\n", ansa, ansb);
  return 0;
}
