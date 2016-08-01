/* UESTC 2016 Summer Training #7 Div.2. Problem J, by Abreto, 201607181624. */
#include <stdio.h>

const int direction[4][2] = {
  {0, 1}, /*R*/
  {1, 0}, /*D*/
  {0, -1}, /*L*/
  {-1, 0} /*U*/
};
int w = 0, h = 0;
char room[16][16] = {{0}};
int n_cleaned_cells = 0;
int visited[16][16] = {{0}};
int visited_dir[16][16][4] = {{{0}}};

void dfs(int i, int j, int dir)
{
  int k = 0;
  if( 1 == visited_dir[i][j][dir] )
    return;
  visited_dir[i][j][dir] = 1;
  if( 0 == visited[i][j] )
  {
    visited[i][j] = 1;
    n_cleaned_cells++;
  }
  /* move */
  {
    int curdir = dir;
    int nexti = i + direction[curdir][0];
    int nextj = j + direction[curdir][1];

    if( nexti < 0 || nextj < 0 || nexti >= w || nextj >= h )
      dfs(i, j, (dir+1)%4);
    else if( '*' == room[nexti][nextj] )
      dfs(i, j, (dir+1)%4);
    else
      dfs(nexti, nextj, dir);
  }
}

void clean(void)
{
  int i = 0, j = 0;

  for(i = 0;i < w;++i)
    for(j = 0;j < h;++j)
      if( 'A' <= room[i][j] && 'Z' >= room[i][j] )
      {
        int dir = 0;
        switch (room[i][j]) {
          case 'U':
            dir++;
          case 'L':
            dir++;
          case 'D':
            dir++;
          case 'R':
            break;
        }
        room[i][j] = '.';
        dfs(i, j, dir);
      }

}

int main(void)
{
  int i = 0;

  scanf("%d %d\n", &w, &h);
  for(i = 0;i < w;++i)
    scanf("%s\n", room[i]);

  clean();

  printf("%d\n", n_cleaned_cells);
  return 0;
}
