/* UESTC Summer Training #18 Div.2. Problem I. */
#include <stdio.h>

int n = 0;
int sets[201][10001] = {{0}};
int shown[201][201] = {{0}};
int niset[201][201] = {{0}};
int maxa = 0;

int main(void)
{
  int i = 0, j = 0;

  scanf("%d", &n);
  for(i = 1;i <= n;++i)
  {
    int x = 0, y = 0, k = 0;
    int a = 0;
    int nint = 0;
    scanf("%d %d %d", &x, &y, &k);
    if( y < x )
    {
      x = x^y;
      y = x^y;
      x = x^y;
    }
    for(j = 0;j < k;++j)
    {
      scanf("%d", &a);
      if( a > maxa ) maxa = a;
      sets[x][a] = sets[y][a] = 1;
    }
    for(j = 1;j <= maxa;++j)
      if( 1 == sets[x][j] && 1 == sets[y][j] )
        nint++;
    niset[x][y] = k;
    shown[x][y] = 1;
    if( nint > k )
    {
      printf("No\n");
      return 0;
    }
  }

  for(i = 1;i <= n;++i)
    for(j = i+1;j <= n;++j)
      if( 1 == shown[i][j] )
      {
        int k = 0;
        int nint = 0;
        for(k = 1;k <= maxa;++k)
          if( 1 == sets[i][k] && 1 == sets[j][k] )
            nint++;
        if( nint != niset[i][j] )
        {
          printf("No\n");
          return 0;
        }
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
