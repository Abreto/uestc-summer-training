/* UESTC Summer Training #19. Problem F. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN  100001

typedef struct _interval
{
  int l;
  int r;
}interval, *p_interval;

int intcompar(const void * a, const void * b)
{
  p_interval pa = (p_interval)a;
  p_interval pb = (p_interval)b;
  if( pa->r != pb->r )
    return ( (pa->r) - (pb->r) );
  else
    return ( (pb->l) - (pa->l) );
}

int N = 0;
interval ints[MAXN];
interval final[MAXN];
int nfinal = 0;
char had[1000001] = {0};
char needanother[1000001] = {0};
int maxlen = 0;
int sum[1000001] = {0};
int nswords = 0;

int main(void)
{
  int i = 0,T = 0;
  int j = 0;

  scanf("%d", &T);
  for(i = 0;i < T;++i)
  {
    int A = 0, B = 0, C = 0;

    memset(had, 0, sizeof(had));
    memset(needanother, 0, sizeof(had));
    maxlen = 0;
    nfinal = 0;
    scanf("%d", &N);
    for(j = 0;j < N;++j)
    {
      scanf("%d %d %d", &A, &(ints[j].l), &(ints[j].r));
      if( ints[j].l <= A && A <= ints[j].r )  needanother[A] = 1;
      had[A] = 1;
      if(A > maxlen) maxlen = A;
      if(ints[j].r > maxlen) maxlen = ints[j].r;
    }

    qsort(ints, N, sizeof(interval), intcompar);
    for(j = 0;j < N;)
    {
      int k = j+1;
      int maxl = ints[j].l;
      while( (k < N) && ints[k].l <= ints[j].r )
      {
        if( ints[k].l > maxl )  maxl = ints[k].l;
        k++;
      }
      final[nfinal].l = maxl;
      final[nfinal].r = ints[j].r;
      ++nfinal;
      j = k;
    }

    for(j = 1;j <= maxlen;++j)
      sum[j] = sum[j-1] + had[j];
    nswords = sum[maxlen];
    for(j = 0;j < nfinal;++j)
      if( 0 == (sum[final[j].r] - sum[final[j].l-1]) )
        nswords++;
      else if( 1 == ((sum[final[j].r] - sum[final[j].l-1])) )
      {
        int k = 0;int needa = 0;
        for(k = final[j].l;k <= final[j].r;++k)
          if( 1 == had[k] && 1 == needanother[k] )
          {
            needa = 1;
            break;
          }
        nswords += needa;
      }

    printf("Case #%d: %d\n", i+1, nswords);
  }

  return 0;
}
