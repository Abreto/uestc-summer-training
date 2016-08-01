/* UESTC 2016 Summer Training #9 Div.2. Problem H, by Abreto, 201607201523. */
#include <stdio.h>
#include <string.h>

int N = 0;
char target[32] = {0};
int ltarget = 0;
int cubes[256][128] = {0};
int ncubes[256] = {0};
int used[128] = {0};
int ok = 0;

void dfs(int c)
{
  if( ok ) return;
  if( c == ltarget )
  {
    ok = 1;
    return;
  }
  else
  {
    int i = 0;
    for(i = 0;i < ncubes[target[c]];++i)
      if( ok )
        return;
      else if( 0 == used[cubes[target[c]][i]] )
      {
        used[cubes[target[c]][i]] = 1;
        dfs(c+1);
        used[cubes[target[c]][i]] = 0;
      }
  }
}

int main(void)
{
  int i = 0;

  scanf("%s %d\n", target, &N);
  for(i = 0;i < N;++i)
    while(1)
    {
      char c = 0;
      scanf("%c", &c);
      if( '\n' == c )
        break;
      if( 'a' <= c && c <= 'z' )
      {
        cubes[c][ncubes[c]++] = i;
      }
    }
  ltarget = strlen(target);
  if( ltarget > N )
  {
    printf("NO\n");
    return 0;
  }

  for(i = 0;i < ncubes[target[0]];++i)
  {
    if( ok ) break;
    used[cubes[target[0]][i]] = 1;
    dfs(1);
    used[cubes[target[0]][i]] = 0;
  }

  printf("%s\n", ok?"YES":"NO");
  return 0;
}
