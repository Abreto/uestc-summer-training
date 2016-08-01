/* UESTC 2016 Summer Training #2 Div.2.  Problem J. by Abreto, 201607121523. */
#include <stdio.h>
#include <string.h>
#define MAXN  512

int R = 0, C = 0;
char gird[MAXN][MAXN]  = {{0}};
int the_year_invaded[MAXN][MAXN] = {{0}};
int this_year = 0;

int invade(char color, int r, int c)
{
  if( '#' == gird[r][c] )
    return 0;
  else if( '*' == gird[r][c] )
    return 0;
  else if( '.' == gird[r][c] )
  {
    gird[r][c] = color;
    the_year_invaded[r][c] = this_year;
    return 1;
  }
  else if( color == gird[r][c] )
  {
    int invaded = 0;
    if( the_year_invaded[r][c] != this_year-1 )
      return 0;
    if( (r-1) >= 0 )  invaded += invade(color, r-1, c);
    if( (c-1) >= 0 )  invaded += invade(color, r, c-1);
    if( (c+1) < C ) invaded += invade(color, r, c+1);
    if( (r+1) < R ) invaded += invade(color, r+1, c);
    return invaded;
  }
  else
  {
    if( the_year_invaded[r][c] == this_year )
    {
      gird[r][c] = '*';
      return 0;
    }
  }
}

void simulate(void)
{
  int i = 0, j = 0;
  int n_changes = 1;

  memset(the_year_invaded, 0 ,sizeof(the_year_invaded));
  this_year = 0;

  while(n_changes != 0)
  {
    n_changes = 0;
    this_year++;
    for(i = 0;i < R;++i)
      for(j = 0;j < C;++j)
        if( ('a'<=gird[i][j]) && (gird[i][j]<='z') && (the_year_invaded[i][j] == this_year-1) )
          n_changes += invade(gird[i][j], i, j);
  }
}

int main(void)
{
  int T = 0;

  scanf("%d\n", &T);
  while(T--)
  {
    int i = 0, j = 0;

    scanf("%d %d\n", &R, &C);
    for(i = 0;i < R;++i)
      scanf("%s\n", gird[i]);

    simulate();

    for(i = 0;i < R;++i)
    {
      for(j = 0;j < C;++j)
        printf("%c", gird[i][j]);
      printf("\n");
    }
    printf("\n");
  }

  return 0;
}
