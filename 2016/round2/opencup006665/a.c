/* UESTC Summer Training Western Subregional 2013. */
/* Problem A, by Abreto. */
#include <stdio.h>

#define MAXN  500002

int N = 0;
int a[MAXN] = {0};
int Q = 0;

int count(int l, int r)
{
  int i = 0;
  int noccurtimes[1024] = {0};
  for(i = l;i <= r;++i)
    noccurtimes[a[i]]++;
  for(i = 1;i < 1001;++i)
    if( 1 == (noccurtimes[i] % 2) )
      noccurtimes[0]++;
  return noccurtimes[0];
}

int main(void)
{
  int i = 0;

  scanf("%d %d", &N, &Q);
  for(i = 1;i <= N;++i)
    scanf("%d", &(a[i]));

  while(Q--)
  {
    char com[3] = {0};
    int x = 0, y = 0;

    scanf("%s %d %d", com, &x, &y);

    switch (com[0])
    {
      case 'S':
        a[x] = y;
        break;
      case 'Q':
        printf("%d\n", count(x,y));
        break;
    }
  }

  return 0;
}
