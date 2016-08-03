/* UESTC Summer Training #19. Problem H. */
#include <stdio.h>

#define OPPSITE(x)  (1-(x))

int main(void)
{
  int i = 0, T = 0;

  scanf("%d", &T);
  for(i = 0;i < T;++i)
  {
    int j = 0;
    int N = 0, M = 0, K = 0;
    char mem[2048] = {0};
    char cur = 0;
    char prev = -1;
    int nprev = 0;
    char winner = 0;
    int n[2] = {0,0}; /* 0 for A, 1 for B */

    scanf("%d %d %d", &N, &M, &K);
    scanf("%s", mem);
    for(j = 0;j < 2*N;++j)
    {
      int cmin = 0, cmax = 0;
      int omin = 0, omax = 0;
      int rmin = 0, rmax = 0;
      cur = mem[j]-'A';
      if( cur == prev ) nprev++;
      else {prev = cur;nprev = 1;}
      (n[cur])++;
      cmin = n[cur] - nprev + 1; cmax = K*n[cur];
      omin = n[OPPSITE(cur)]; omax = K*omin;
      rmin = M - omax; rmax = M - omin;
      if( cmin <= rmin && rmax <= cmax )
      {
        winner = 'A' + cur;
        break;
      }
    }
    printf("Case #%d: %c\n", i+1, winner);
  }

  return 0;
}
