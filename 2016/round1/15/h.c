/* UESTC 2016 Summer Training #15 Div.2. Problem H, by Abreto, 20160727. */
#include <stdio.h>

#define ABS(x)  (((x)>0)?(x):(-(x)))

#define MAXM  100002

int m = 0;
int slope_just_moved[MAXM] = {0};
int delta[MAXM] = {0};
int slope_i[MAXM] = {0};
int mina = 2e9;
int ansi = -1, ansj = -1;

int main(void)
{
  int i = 0;
  int n = 0;

  scanf("%d", &n);
  scanf("%d", &m);
  scanf("%d", &(slope_just_moved[0]));
  for(i = 1;i <= m;++i)
  {
    scanf("%d", &(slope_just_moved[i]));
    delta[i] = slope_just_moved[i] - slope_just_moved[i-1];
  }
  for(i = 1;i <= n;++i)
  {
    int j = 0, k = 0, l = 1;
    int mn = 0;
    int cura = 0;

    scanf("%d", &mn);
    scanf("%d", &(slope_i[0]));
    for(k = 1;k <= mn;++k)
    {
      scanf("%d", &(slope_i[k]));
    }
    for(j = 0;j < mn;)
    {
      int del = 0, nowa = 0;
      del = slope_i[j+l] - slope_i[j+l-1];
      nowa = delta[l] - del;
      if( nowa == cura )
      {
        l++;
        if( l > m )
        {
          if( ABS(cura) < ABS(mina) )
          {
            mina = cura;
            ansi = i;
            ansj = j;
            j++;
            l=1;
          }
        }
      }
      else
      {
        cura = nowa;
        j = j+l; l=1;
      }
    }
  }

  printf("%d %d %d", mina, ansi, ansj);
  return 0;
}
