/* UESTC 2016 Summer Training #2 Div.2.  Problem A. by Abreto, 201607121246. */
#include <stdio.h>
#define MAXR  512

#define MIN(a,b)  (((a)<(b))?(a):(b))

int R = 0, C = 0;
int magrids[MAXR][MAXR] = {{0}};


int main(void)
{
  int T = 0;

  scanf("%d", &T);
  while(T--)
  {
    int i = 0, j = 0, k = 0;
    int s = 0;
    scanf("%d %d", &R, &C);
    for(i = 0;i < R;++i)
      for(j = 0;j < C;++j)
        scanf("%d", &(magrids[i+1][j+1]));

    magrids[R][C] = 1;
    for(s = R+C-1;s > 1;--s)
    {
      int start_row = ( (s-1) > R ) ? R : (s-1);
      int end_row = ( (s-C) < 0 ) ? 1 : (s-C);
      for(i = start_row;i >= end_row;i--)
      {
        j = s-i;
        if( i == R )  /* the bottom */
        {
          magrids[i][j] = (-magrids[i][j]) + magrids[i][j+1];
        }
        else if ( j == C )  /* the right */
        {
          magrids[i][j] = (-magrids[i][j]) + magrids[i+1][j];
        }
        else
        {
          magrids[i][j] = (-magrids[i][j]) + MIN(magrids[i+1][j],magrids[i][j+1]);
        }
        if( magrids[i][j] < 1 )
          magrids[i][j] = 1;
      }
    }

    printf("%d\n", magrids[1][1]);
  }

  return 0;
}
