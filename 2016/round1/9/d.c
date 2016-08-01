/* UESTC 2016 Summer Training #9 Div.2. Problem D, by Abreto, 201607201238. */
#include <stdio.h>
#include <stdlib.h>

#define MAXN  16

int N = 0;
int sticks = 0;
int len[MAXN] = {0};
int used[MAXN] = {0};
int maxtris = 0;

int comp(const void *a, const void *b)
{
  return ( (*((int*)a)) - (*((int*)b)) );
}

void dfs(int tris)
{
  if( sticks < 3 )
  {
    if( tris > maxtris )
      maxtris = tris;
    return;
  }
  else
  {
    int i = 0;
    int bottom = 0;
    int upper = 0;
    int a = -1, b = -1;
    int count = 0;
    int tiri = 0;
    for( i = 0;i < N && count < 2;++i )
      if( 0 == used[i] )
      {
        if( 0 > a )
          a = i;
        else if(0 > b)
          b = i;
        count++;
      }
    bottom = len[b] - len[a];
    upper = len[a] + len[b];
    used[a] = 1;
    used[b] = 1;
    sticks -= 2;
    for(i;i < N && len[i] < upper;++i)
      if( len[i] > bottom )
      {
        tiri = 1;
        used[i] = 1;
        sticks--;
        dfs(tris+1);
        sticks++;
        used[i] = 0;
      }
    tris += tiri;
    if( tris > maxtris )
      maxtris = tris;
    used[a] = 0;
    used[b] = 0;
    sticks += 2;
  }
}

int main(void)
{
  int i = 0;

  scanf("%d", &N);
  sticks = N;
  for(i = 0;i < N;++i)
    scanf("%d", &(len[i]));

  qsort(len, N, sizeof(int), comp);
  dfs(0);

  printf("%d\n", maxtris);
  return 0;
}
