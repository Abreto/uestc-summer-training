/* UESTC 2016 Summer Training #4 Div.2. Problem C, by Abreto, 201607141641. */
#include <stdio.h>

#define MAXN  512

const int directions[4][2] = {
  {-1,0},
  {0,-1},
  {0,1},
  {1,0}
};

int n = 0, m = 0;
char warehouse[MAXN][MAXN]  = {{0}};
char visited[MAXN][MAXN] = {{0}};
int n_solutions = 0;
int withstop = 0;

int valied(int i, int j)
{
  if( (i<0) || (i>=n) || (j<0) || (j>=m) )
    return 0;
  if( '#' == warehouse[i][j] )
    return 0;
  return 1;
}

void dfs(int r, int c)
{
  int i = 0, countout = 0;
  if( n_solutions > 1 )
    return;
  if( (r<0) || (r>=n) || (c<0) || (c>=m) )
    return;
  if( '2' == warehouse[r][c] )
  {
    n_solutions++;
    return;
  }
  if( '#' == warehouse[r][c] )
    return;
  if( visited[r][c] )
    return;
  visited[r][c] = 1;
  for(i = 0;i < 4;++i)
  {
    if( valied(r+directions[i][0],c+directions[i][1]) )
      countout++;
    dfs(r+directions[i][0], c+directions[i][1]);
    if ( n_solutions > 1 )
      return;
  }
  if( (countout > 2) && ('1' != warehouse[r][c] || '2' != warehouse[r][c]) )  withstop = 1;
}

int main(void)
{
  int i = 0, j = 0;

  scanf("%d %d", &n, &m);
  for(i = 0;i < n;++i)
    scanf("%s\n", warehouse[i]);

  for(i = 0;i < n;++i)
    for(j = 0;j < m;++j)
      if( '1' == warehouse[i][j] )
      {
        dfs(i, j);
        goto die;
      }

die:
  if( n_solutions > 1 ) printf("YES\n");
  else if( 1 == n_solutions && 1 == withstop )  printf("YES\n");
  else printf("NO\n");
  return 0;
}
