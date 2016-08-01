/* UESTC 2016 Summer Training #6 Div.2. Problem C, by Abreto, 201607161529. */
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int N = 0;
int ans[20048] = {0};
int maxans = 0;
vector<vector<int> > graph(20048);
int visited[20048] = {0};

void dfs(int root, int current)
{
  if( current < root )
    return;
  else
  {
    int i = 0;
    int nout = 0;
    visited[current] = 1;
    for(i = 0;i < graph[current].size();++i)
    {
      if( 0 == visited[graph[current][i]] )
      {
        dfs(root, graph[current][i]);
        nout++;
      }
    }
    if( nout > 0 )
    {
      ans[current] ++;
      if( ans[current] > maxans )
        maxans = ans[current];
    }
    visited[current] = 0;
  }
}

int  count(void)
{
  int i = 0;

  scanf("%d", &N);
  maxans = 0;
  memset(ans, 0, (N+1)*sizeof(int));
  for(i = 0;i < N;++i)
  {
    int a = 0, b = 0;
    scanf("%d %d", &a, &b);
    if( a < b )
      graph[a].push_back(b);
    else
      graph[b].push_back(a);
  }
  for(i = 1;i <= N;++i)
  {
    int j = 0;
    for(j = 0;j < graph[i].size();++j)
    {
      visited[i] = 1;
      dfs(i, j);
      visited[i] = 0;
    }
  }
  return maxans;
}

int main(void)
{
  int i = 0;
  int T = 0;

  scanf("%d", &T);
  for(i = 0;i < T;++i)
    printf("Case #%d: %d\n", i+1, count());

  return 0;
}
