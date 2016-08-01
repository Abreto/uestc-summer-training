/* UESTC 2016 Summer Training #3 Div.2.  Problem B. by Abreto, 201607131243. */
#include <stdio.h>

#define FILE_IN "input.txt"
#define FILE_OUT  "output.txt"
#define MAXD  1024

int n = 0, m = 0;
char picture[MAXD][MAXD] = {{0}};

int check(int x, int y)
{
  if( (x<0) || (y<0) || (x>=n) || (y>=m) )
    return 0;
  else if( '-' == picture[x][y] )
    return 1;
  else return 0;
}

int main(void)
{
  int i = 0, j = 0;
  int n_coastline_cells = 0;

  freopen(FILE_IN, "r", stdin);
  freopen(FILE_OUT, "w+", stdout);

  scanf("%d %d\n", &n, &m);
  for(i = 0;i < n;++i)
    scanf("%s", picture[i]);

  for(i = 0;i < n;++i)
    for(j = 0;j < m;++j)
      if( '+' == picture[i][j] )
      {
        if( check(i-1,j) )
          n_coastline_cells++;
        else if(check(i,j-1))
          n_coastline_cells++;
        else if (check(i,j+1))
          n_coastline_cells++;
        else if(check(i+1,j))
          n_coastline_cells++;
      }

  printf("%d\n", n_coastline_cells);
  return 0;
}
