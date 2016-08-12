#include <stdio.h>

int v[128] = {0};
int sv[128] = {0};
int minv[4] = {0};
int minw = 1<<31;

void dfs(int level, int s)
{
  if( 4 == level )
  {
    ;
  }
  else
  {
    int i = 0;
    for(i = s;i < 53-(4-level);++i)
    {
      v[i] = 1;
      dfs(level+1, i+1);
      v[i] = 0;
    }
  }
}

int main(void)
{
  int i = 0, x = 0;

  for(i = 0;i < 4;++i)
  {
    scanf("%d", &x);
    v[x] = 1;
  }
  for(i = 1;i < 53;++i)
    sv[i] = sv[i-1] + v[i];

  v[53] = 1;
  dfs(1, 2);

  printf("%d %d %d %d\n", minv[0], minv[1], minv[2], minv[3]);
  return 0;
}
