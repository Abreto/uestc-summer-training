/* UESTC 2016 Summer Training #3 Div.2.  Problem K. by Abreto, 201607131348. */
#include <stdio.h>

#define MAXN  512

int N = 0, K = 0;
char flag[MAXN][MAXN] = {{0}};
int solutions = 0;
int blue_in_a_col[MAXN] = {0};
int blue_in_a_sub[32][32] = {0};

void put_blue_to(int i, int j)
{
  flag[i][j] = '*';
  blue_in_a_col[j]++;
  blue_in_a_sub[i/N][j/N]++;
}

void remove_blue_from(int i, int j)
{
  flag[i][j] = '.';
  blue_in_a_col[j]--;
  blue_in_a_sub[i/N][j/N]--;
}

void dfs(int row, int col, int blue_to_put_this_row)
{
  if( solutions ) return;

  if( blue_to_put_this_row )
  {
    int i = 0;

    while( (col < N*N) && ((blue_in_a_col[col] >= K)||(blue_in_a_sub[row/N][col/N] >= K)) ) col++;
    if( col > (N*N - blue_to_put_this_row) )  /*  no solutions */
      return;

    /* put a blue in (row,col) */
    put_blue_to(row,col);

    for(i = col+1;i < (N*N - blue_to_put_this_row + 2);++i)
    {
      dfs(row, i, blue_to_put_this_row-1);
      if(solutions) return;
    }

    remove_blue_from(row,col);
  }
  else if (row < N*N-1) /* fill next row */
  {
    int i = 0;

    while( (i < N*N) && ((blue_in_a_col[i] >= K)||(blue_in_a_sub[(row+1)/N][i/N] >= K)) ) i++;
    if( i > (N*N - blue_to_put_this_row) )  /*  no solutions */
      return;
    for(;i < (N*N-K+1);++i)
    {
      dfs(row+1, i, K);
      if(solutions) return;
    }
  }
  else    /*  rows, cols filled. */
  {
    int i = 0, j = 0;
    int ok = 1;
    /* check */
    for(i = 0;i < N;++i)
      for(j = 0;j < N;++j)
        if( K != blue_in_a_sub[i][j] )
        {
          ok = 0;
          goto checked;
        }
checked:
    if( ok )
    {
      solutions++;
      for(i = 0;i < N*N;++i)
      {
        for(j = 0;j < N*N;++j)
          if( '*' == flag[i][j] )
            printf("*");
          else
            printf(".");
        printf("\n");
      }
    }
  }
}

void dfs_driver(void)
{
  int i = 0;
  for(i = 0;i < (N*N-K+1);++i)
  {
    dfs(0, i, K);
    if(solutions) return;
  }
}

int main(void)
{
  scanf("%d %d", &N, &K);

  dfs_driver();

  if( 0 == solutions )
    printf("NO SOLUTION\n");
  return 0;
}
