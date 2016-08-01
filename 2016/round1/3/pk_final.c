/* UESTC 2016 Summer Training #3 Div.2.  Problem K. by Abreto, 201607131348. */
#include <stdio.h>

#define MAXD 512

int N = 0, K = 0;
char flag[MAXD][MAXD] = {{0}};

int main(void)
{
  int i = 0, j = 0;

  scanf("%d %d", &N, &K);

  for(i = 0;i < N;++i)
    for(j = 0;j < N;++j)
      if( K > 0 )
      {
        flag[i][j] = '*';
        --K;
      }
      else
        flag[i][j] = '.';

  for(i = 0;i < N;++i)
    for(j = 0;j < N;++j)
    {
      /* in a sub square. */
      int r = 0, c = 0;
      for(r = 0;r < N;++r)
        for(c = 0;c < N;++c)
          flag[i*N+r][j*N+c] = flag[ (r+j)%N ][ (c+i)%N ];
    }

  for(i = 0;i < N*N;++i)
  {
    for(j = 0;j < N*N;++j)
      printf("%c", flag[i][j]);
    printf("\n");
  }
  return 0;
}
