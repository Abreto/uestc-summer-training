/* UESTC 2016 Summer Training #8 Div.2. Problem C, by Abreto, 201607191514. */
#include <stdio.h>

#define MAXN  1024

int n = 0, m = 0;
int si[MAXN] = {0};
int sums[MAXN] = {0};

int strim = 0;

int handle(int start, int end, int res)
{
  int bomb = 0; /* put in [bomb,bomb+1] */
  int maxdelta = 0, maxb = 0;
  int maxsum = 0;

  if( start == end || 0 == res )
    return 0;

  for( bomb = start; bomb < end;++bomb )
  {
    int left = sums[bomb] - sums[start-1];
    int nowdelta = left*right;
    int right = sums[end] - sums[bomb];
    if( nowdelta > maxdelta )
    {
      maxdelta = nowdelta;
      maxb = bomb;
    }
  }
  if( res > 1 )
    for(bomb = 0;bomb <= maxb-start && bomb < res;++bomb)  /* bomb: bombs put to left */
    {
      if( (end-bomb-1) >= (res-bomb) )
      {
        int t1 = handle(start, maxb, bomb);
        int t2 = handle(maxb+1, end, res-bomb-1);
        int t3 = t1 + t2;
        if( t3 > maxsum )
          maxsum = t3;
      }
    }

  return (maxdelta+maxsum);
}

int main(void)
{

  while(1)
  {
    scanf("%d %d", &n, &m);
    if( 0 == n && 0 == m )
      break;
    else
    {
      int i = 0;
      sums[0] = 0;
      for(i = 1;i <= n;++i)
      {
        scanf("%d", &(si[i]));
        sums[i] = si[i] + sums[i-1];
      }
      strim = 0;
      for(i = 1;i <= n;++i)
        strim += si[i] * (sums[n] - sums[i]);
      printf("%d\n", strim-handle(1, n, m));
    }
  }

  return 0;
}
