/* UESTC Summer Training #18 Div.2. Problem I. */
#include <cstdio>
#include <vector>

#define EXIT  {printf("No\n");return 0;}

using namespace std;

int n = 0;
int sets[201][10001] = {{0}};
int queried[201][201] = {{0}};
vector<int> query[201][201];
int maxa = 0;

int main(void)
{
  int i = 0, j = 0;

  scanf("%d", &n);
  for(i = 0;i < n;++i)
  {
    int x = 0, y = 0, k = 0;
    int a = 0;
    scanf("%d %d %d", &x, &y, &k);
    if( y < x ) {int t = x;x = y;y = t;}
    for(j = 0;j < k;++j)
    {
      scanf("%d", &a);
      if(a > maxa) maxa = a;
      sets[x][a] = sets[y][a] = 1;
      query[x][y].push_back(a);
    }
    queried[x][y] = 1;
  }

  for(i = 1;i <= n;++i)
    for(j = i+1;j <= n;++j)
      if( 1 == queried[i][j] )
      {
        int nint = 0;
        int k = 0;
        for(k = 1;k <= maxa;++k)
          if( (1 == sets[i][k]) && (1 == sets[j][k]) )
          {
            nint++;
            if( nint > query[i][j].size() )
              EXIT;
          }
        if( nint < query[i][j].size() ) EXIT;
        for(k = 0;k < query[i][j].size();++i)
          if( (1 != sets[i][query[i][j][k]]) || (1 != sets[j][query[i][j][k]]) )
            EXIT;
      }

  printf("Yes\n");
  for(i = 1;i <= n;++i)
  {
    int nele = 0;
    for(j = 1;j <= maxa;++j)
      if( 1 == sets[i][j] )
        nele++;
    printf("%d", nele);
    for(j = 1;j <= maxa;++j)
      if( 1 == sets[i][j] )
        printf(" %d", j);
    printf("\n");
  }
  return 0;
}
