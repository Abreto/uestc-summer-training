/* UESTC Summer Training #22. Problem A. by Abreto.*/
#include <stdio.h>
#include <stdlib.h>

#define INPUTFILE   "cookies.in"
#define OUTPUTFILE  "cookies.out"
#define MAXN  32

typedef long long int ll;

int n = 0, m = 0;
int g[MAXN] = {0};
int order[MAXN] = {0};
ll sum[MAXN] = {0}; /* sum[i+1] = sum[i] + g[i]; */
int cs[MAXN] = {0};
int output[MAXN] = {0};
ll curtotalg = 0;

int comparg(const void *a, const void *b)
{
  return ( (g[*((int*)a)]) - (g[*((int*)b)]) );
}

int average_assign(void)
{
  int init = m / n;
  int i = 0;
  int rest = m - init*n;

  for(i = 0;i < n;++i)
    cs[i] = init;

  if( 0 == rest )
  {
    curtotalg = 0;
    return 1;
  }
  else
  {
    for(i = 0;i < rest;++i)
      cs[n-i-1] += 1;
    curtotalg = (sum[n-rest]) * (ll)(rest);
    return 0;
  }
}

void prepare_output_array(void)
{
  int i = 0;
  for(i = 0;i < n;++i)
    output[order[i]] = cs[i];
}

void update(int l, int r)
{
#ifdef LOCALDEBUG
  printf("Now, I want to update [%d,%d]\n",l, r);
#endif
  if( l >= r )
    return;
  if( 1 == cs[l] )
    update(l+1, r);
  else
  {
    ll delta = 0;
    if( cs[l] == cs[l+1] )
      delta += (ll)(g[order[l]]) * (ll)(r-l);
    delta += (sum[r] - sum[l+1]);
    delta -= (ll)(n-r-1) * (ll)(g[order[r]]);
    if( delta < 0 )
    {
      curtotalg += delta;
      cs[l]--; cs[r]++;
      update(l, r-1);
    }
  }
}

void handle(void)
{
  if( 0 == average_assign() )
  {
    int i = 0;
    while(cs[i] == cs[i+1]) ++i;
    update(0, i);
  }
  prepare_output_array();
}

int main(void)
{
  int i = 0;

#ifndef LOCALDEBUG
  freopen(INPUTFILE, "r", stdin);
  freopen(OUTPUTFILE, "w+", stdout);
#endif

  scanf("%d %d", &n, &m);
  for(i = 0;i < n;++i)
  {
    scanf("%d", &(g[i]));
    order[i] = i;
  }
  qsort(order, n, sizeof(int), comparg);
  for(i = 0;i < n;++i)
    sum[i+1] = sum[i] + g[order[i]];

#ifdef LOCALDEBUG
{
  for(i = 0;i < n;++i)
    printf("%d ", g[order[i]]);
  printf("\n");
}
#endif

  handle();

  printf("%lld\n%d", curtotalg, output[0]);
  for(i = 1;i < n;++i)
    printf(" %d", output[i]);
  printf("\n");
  return 0;
}
