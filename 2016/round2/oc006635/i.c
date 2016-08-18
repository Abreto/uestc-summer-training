/* UESTC Summer Training Southern Subregional 2013. */
/* Problem I, by Abreto. */
#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (((a)<(b))?(a):(b))

#define MAXN  5002

int n = 0, a = 0, b = 0;
int t[MAXN] = {0};
int w[MAXN] = {0};
int watts[4][MAXN] = {{0}};
int ncomputers[4] = {0};

int sockets[3][MAXN] = {{0}};
int nsockets[3] = {0};
int privatepoints[4] = {0};

int nplugedc = 0;
int totalwatts = 0;

int compar(const void *a, const void *b)
{
  return ( (w[*((int*)a)]) - (w[*((int*)b)]) );
}

int main(void)
{
  int i = 0, j = 0;

  scanf("%d %d %d", &n, &a, &b);
  for(i = 1;i <= n;++i)
  {
    scanf("%d %d", &(t[i]), &(w[i]));
    watts[t[i]][ncomputers[t[i]]] = i;
    ncomputers[t[i]] ++;
  }

  /* sort them */
  for(i = 1;i < 4;++i)
    qsort(watts[i], ncomputers[i], sizeof(int), compar);

  /* assign sockets */
  for(i = 1;i < 3;++i)
  {
    int lim = ((i == 1) ? a : b);
    nsockets[i] = MIN(ncomputers[i], lim);
    for(j = 0;j < nsockets[i];++j)
    {
      sockets[i][j] = watts[i][j];
      nplugedc ++;
      totalwatts += w[watts[i][j]];
    }
    privatepoints[i] = nsockets[i]-1; /* 0..pp[i] */
  }

  privatepoints[3] = 0;  /* computers assigned */
  /* assign rest sockets with type 3 */
  for(i = 1;i < 3;++i)
  {
    int lim = ((i == 1) ? a : b);
    while( nsockets[i] < lim && privatepoints[3] < ncomputers[3] )
    {
      sockets[i][nsockets[i]] = watts[3][privatepoints[3]];
      totalwatts += w[watts[3][privatepoints[3]]];
      nplugedc ++;
      nsockets[i] = nsockets[i]+1;
      privatepoints[3] ++;
    }
  }

  /* replace */
  while( (privatepoints[1] > -1 || privatepoints[2] > -1) && ( privatepoints[3] < ncomputers[3] ) )
  {
    int toreplacetype = -1;
    int toreplace = -1;
    if( privatepoints[1] > -1 && privatepoints[2] > -1 )
    {
      if( w[sockets[1][privatepoints[1]]] > w[sockets[2][privatepoints[2]]] )
      {
        toreplace = privatepoints[1];
        toreplacetype = 1;
      }
      else
      {
        toreplace = privatepoints[2];
        toreplacetype = 2;
      }
    }
    else if (privatepoints[1] > -1)
    {
      toreplace = privatepoints[1];
      toreplacetype = 1;
    }
    else if ( privatepoints[2] > -1 )
    {
      toreplace = privatepoints[2];
      toreplacetype = 2;
    }

    if( toreplace > -1 )
    {
      int cur = watts[3][privatepoints[3]];
      int tor = sockets[toreplacetype][toreplace];
      if( w[cur] < w[tor] )
      {
        totalwatts -= w[tor];
        totalwatts += w[cur];
        sockets[toreplacetype][toreplace] = cur;
        privatepoints[toreplacetype] --;
        privatepoints[3]++;
      }
      else
      {
        break;
      }
    }
    else
      break;
  }

  printf("%d %d\n", nplugedc, totalwatts);
  for(i = 0;i < nsockets[1];++i)
    printf("%d %d\n", sockets[1][i], i+1);
  for(i = 0;i < nsockets[2];++i)
    printf("%d %d\n", sockets[2][i], a+i+1);
  return 0;
}
