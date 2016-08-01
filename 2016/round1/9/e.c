/* UESTC 2016 Summer Training #9 Div.2. Problem E, by Abreto, 201607201623. */
#include <stdio.h>

#define MAXN  128

typedef long long int ll;

int n = 0;
ll A[MAXN][MAXN] = {{0}};
ll fixedsum = 0;
ll sumi[MAXN] = {0};

int main(void)
{
  int i = 0, j = 0;

  scanf("%d", &n);
  for(i = 0;i < n;++i)
    for(j = 0;j < n;++j)
    {
      scanf("%lld", &(A[i][j]));
      sumi[i] += (ll)(A[i][j]);
    }

  /* calc fixedsum: */
  {
    ll secdiag = 0;
    for(i = 0;i < n;++i)
      secdiag += A[i][n-i-1];
    if( 0 == n%2 )
      fixedsum = secdiag;
    else
    {
      ll nfixds = -sumi[n/2];
      for(i = 0;i < n;++i)
        nfixds += sumi[i];
      nfixds += secdiag;
      fixedsum = nfixds / (n-1);
    }
  }

  for(i = 0;i < n;++i)
  {
    if( 0 == i )
      printf("%lld", fixedsum - sumi[0]);
    else
      printf("%lld", A[i][0]);
    for(j = 1;j < n;++j)
      if( i == j )
       printf(" %lld", fixedsum - sumi[i]);
      else
        printf(" %lld", A[i][j]);
    printf("\n");
  }

  return 0;
}
