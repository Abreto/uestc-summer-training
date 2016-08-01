/* UESTC 2016 Summer Training #12 Div.2. Problem B, by Abreto, 20160724. */
#include <stdio.h>
#include <string.h>

#define MIN(a, b) ( ((a)<(b)) ? (a) : (b) )

int n = 0, m = 0;
char treegird[128][128] = {{0}};
int ring[128][128] = {{0}};
int ifringlessthan10 = 1;
int visited[128][128] = {{0}};
const int dir[4][2] = {
  {0, -1},
  {-1, 0},
  {0, +1},
  {+1, 0}
};

int getd(int x)
{
  if( 0 == x )
    return 0;
  else if( x < 10 )
    return 1;
  else if( x < 100 )
    return 2;
  else
    return 3;
}

void output(int digit)
{
  int i = 0, j = 0;
  for(i = 1;i <= n;++i)
  {
    for(j = 1;j <= m;++j)
    {
      int k = 0;
      for(k = 0;k < digit-getd(ring[i][j]);++k)
        printf(".");
      if( ring[i][j] > 0 )
        printf("%d", ring[i][j]);
    }
    printf("\n");
  }
}

void modify(int i, int j)
{
  int k = 0;
  for(k = 0;k < 4;++k)
  {
    int newi = i + dir[k][0];
    int newj = j + dir[k][1];
    if( visited[newi][newj] && (ring[newi][newj]-1) > ring[i][j] )
    {
      ring[newi][newj] = ring[i][j] + 1;
      modify(newi, newj);
    }
  }
}


int main(void)
{
  int i = 0, j = 0;

  while( EOF != scanf("%d %d", &n, &m))
  {
    memset(treegird, 0, sizeof(treegird));
    memset(ring, 0, sizeof(ring));
    memset(visited, 0, sizeof(visited));
    for(i = 1;i <= n;++i)
    {
      scanf("%s", treegird[i]);
      for(j = 0;j < m; ++j)
      {
        switch( treegird[i][j] )
        {
        case '.':
          ring[i][j+1] = 0;
          break;
        case 'T':
          ring[i][j+1] = MIN(ring[i][j], ring[i-1][j+1]) + 1;
          break;
        }
        visited[i][j+1] = 1;
        modify(i, j+1);
      }
      ring[i][j+1] = 0;
      modify(i, j+1);
    }
    /* n+1 line; */
    for(j = 1;j <= n;++j)
    {
      ring[i][j] = 0;
      modify(i, j);
    }

    ifringlessthan10 = 1;
    for(i = 1;i <= n;++i)
      for(j = 1;j <= m;++j)
        if( ring[i][j] >= 10 )
        {
          ifringlessthan10 = 0;
          goto to_print;
        }

to_print:
    if( ifringlessthan10 )
      output(2);
    else
      output(3);
  }

  return 0;
}
