/* UESTC Summer Training #23. Problem H. by Abreto.*/
#include <stdio.h>

#define NOSOLUTION    printf("0\n");return 0
#define SUCCESS_EXIT  return 0

int gcd(int m, int n)
{
  if( 0 != n )
    return gcd(n, m%n);
  else
    return m;
}

int main(void)
{
  int i = 0;
  int N = 0, K = 0, P = 0;
  int winner = 0, over = 0;

  scanf("%d %d %d", &N, &K, &P);

  if( P < 0 || P > 100 )
  {
    NOSOLUTION;
  }

  if( 0 == P )
  {
    printf("1\n%d", K);
    for(i = 0;i < N-1;++i)
      printf(" 0");
    printf("\n");
    SUCCESS_EXIT;
  }
  else if(100 == P)
  {
    printf("1\n0");
    for(i = 0;i < N-1;++i)
      printf(" %d", K);
    printf("\n");
    SUCCESS_EXIT;
  }
  else if(P >= 50)
  {
    NOSOLUTION;
  }

  winner = 100 - P*2;
  {
    int x = gcd(winner, 100);
    winner = winner/x;
    over = 100/x;
    P = (over - winner)/2;
  }

  for(i = N/over + (((N%over)!=0)?1:0);i*over <= N*K;++i)
  {
    int total = i * over;
    int win = i * winner;
    int rest = total - win;
    if( win < 1 || win > K || rest < N-1 || rest > (N-1)*K )
      continue;
    else
    {
      int ave = rest / (N-1);
      int del = rest % (N-1);
      int j = 0;
      printf("1\n%d", win);
      for(j = 0;j < N-1;++j)
        printf(" %d", ave + ((del>0)?(--del,1):0));
      printf("\n");
      SUCCESS_EXIT;
    }
  }

  NOSOLUTION;
}
