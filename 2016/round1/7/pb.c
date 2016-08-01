/* UESTC 2016 Summer Training #7 Div.2. Problem B, by Abreto, 201607181428. */
#include <stdio.h>
#include <stdlib.h>

#define MAXCAKE 4096

typedef long long int ll;
typedef struct _cake
{
  int a;
  int b;
}cake, *p_cake;

int cake_compar(const void *a, const void *b)
{
  return ( ((p_cake)b)->a - ((p_cake)a)->a );
}

int n = 0;
cake cakes[MAXCAKE];
ll maxV = 0;
int maxv_a = 0, maxv_b = 0;

void dfs(int cakei, int a, int b, int layers)
{
  ll nowV = (ll)a * (ll)b * (ll)layers;

  if( nowV > maxV )
  {
    maxV = nowV;
    maxv_a = a;
    maxv_b = b;
  }

  if( n == cakei )
    return;

  if( cakes[cakei].b <= b )
  {
    int newa = cakes[cakei].a;
    int newb = cakes[cakei].b;
    ll definitely_lose = (ll)layers * ( (ll)a * (ll)b - (ll)newa * (ll)newb );
    ll possibly_add = ((ll)n - (ll)layers) * (ll)newa * (ll)newb;
    if( (nowV - definitely_lose + possibly_add) > maxV )
      dfs(cakei+1, newa, newb, layers+1);
    dfs(cakei+1, a, b, layers);
  }
  else
  {
    int newa = cakes[cakei].a;
    ll definitely_lose = ((ll)a - (ll)newa) * (ll)b * (ll)layers;
    ll possibly_add = (ll)newa * (ll)b * (ll)(n-layers);
    if( (nowV - definitely_lose + possibly_add) > maxV )
      dfs(cakei+1, newa, b, layers+1);
    dfs(cakei+1, a, b, layers);
  }
}

int main(void)
{
  int i = 0;

  scanf("%d", &n);
  for(i = 0;i < n;++i)
  {
    int a = 0, b = 0;
    scanf("%d %d", &a, &b);
    if( b < a )
    {
      b = a^b;
      a = a^b;
      b = a^b;
    }
    cakes[i].a = a;
    cakes[i].b = b;
  }
  qsort(cakes, n, sizeof(cake), cake_compar);

  for(i = 0;i < n;++i)
  {
    ll mv = (ll)(cakes[i].a) * (ll)(cakes[i].b) * (ll)(n-i);
    if( mv > maxV )
      dfs(i+1, cakes[i].a, cakes[i].b, 1);
  }

  printf("%lld\n%d %d\n", maxV, maxv_b, maxv_a);
  return 0;
}
