/* UESTC 2016 Summer Training #5 Div.2. Problem A, by Abreto, 201607151259. */
#include <cstdio>
#include <map>
#include <vector>
#include <queue>

#define MAXN  100024

using namespace std;

int N = 0;
map<int, vector<int> > connected;
int parent[MAXN] = {0, -1, 0};
int haveapple[MAXN] = {0};
int totalapples[MAXN] = {0};

int main(void)
{
  int i = 0;
  int M = 0;

  scanf("%d", &N);
  for(i = 1;i < N;++i)
  {
    int u = 0, v = 0;
    scanf("%d %d", &u, &v);
    connected[u].push_back(v);
    connected[v].push_back(u);
    /*parent[v] = u;*/
  }

  /* build tree */
  {
    queue<int> q;
    q.push(1);
    while( !q.empty() )
    {
      int v = q.front();
      q.pop();

      for(vector<int>::iterator child = connected[v].begin();child != connected[v].end(); ++child)
        if( 0 == parent[*child] )
        {
          parent[*child] = v;
          q.push(*child);
        }
    }
  }
  /* initalize */
  for(i = N;i > 1;i--)
  {
    int v = i;
    haveapple[v] = 1;
    totalapples[v] ++;
    totalapples[parent[v]] += totalapples[v];
    /*while( v > 0 )
    {
      totalapples[v] ++;
      v = parent[v];
    }*/
  }
  haveapple[1] = 1;
  totalapples[1]++;

  scanf("%d\n", &M);
  while(M--)
  {
    char com = ' ';
    int x = 0;

    scanf("%c %d\n", &com, &x);
    if( 'Q' == com )
    {
      printf("%d\n", totalapples[x]);
    }
    else if( 'C' == com )
    {
      int newstate = (haveapple[x]) ? 0 : 1;
      int delta = newstate - haveapple[x];
      haveapple[x] += delta;
      while( x > 0 )
      {
        totalapples[x] += delta;
        x = parent[x];
      }
    }
  }

  return 0;
}
