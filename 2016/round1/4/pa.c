/* UESTC 2016 Summer Training #4 Div.2. Problem A, by Abreto, 201607141256. */
#include <stdio.h>

#define MAXN  128

int n = 0, m = 0;
int courses[MAXN][MAXN] = {{0}};
int n_set[5] ={0};
int min_size = MAXN;
int min_i = 0, min_j = 0;

int main(void)
{
  int i = 0, j = 0;

  scanf("%d %d", &n, &m);
  for(i = 0;i < n;++i)
    for(j = 0;j < m;++j)
      scanf("%d", &(courses[i+1][j+1]));

  for(i = 1;i <= m;++i)
    for(j = i+1;j <= m;++j)
    {
      int i_prog = 0;
      int maxset = 0;

      n_set[1] = n_set[2] = n_set[3] = n_set[4] = 0;
      for(i_prog = 1;i_prog<=n;++i_prog)
      {
        if( (1 == courses[i_prog][i]) && (1 == courses[i_prog][j]) )
        {
          n_set[1]++;
          if( n_set[1] > maxset ) maxset = n_set[1];
        }
        else if( (1 == courses[i_prog][i]) && (0 == courses[i_prog][j]) )
        {
          n_set[2]++;
          if( n_set[2] > maxset ) maxset = n_set[2];
        }
        else if( (0 == courses[i_prog][i]) && (1 == courses[i_prog][j]) )
        {
          n_set[3]++;
          if( n_set[3] > maxset ) maxset = n_set[3];
        }
        else if( (0 == courses[i_prog][i]) && (0 == courses[i_prog][j]) )
        {
          n_set[4]++;
          if( n_set[4] > maxset ) maxset = n_set[4];
        }

        if( maxset >= min_size )  goto next_condition;
      }

      if( maxset < min_size )
      {
        min_size = maxset;
        min_i = i;
        min_j = j;
      }

next_condition:
      ;
    }

  printf("%d\n%d %d\n", min_size, min_i, min_j);
  return 0;
}
