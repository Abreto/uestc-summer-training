/* UESTC Summer Training Southern Subregional 2013. */
/* Problem I, by Abreto. */
#include <stdio.h>

#define MAXN 300001

int n = 0;
int ps[MAXN] = {0};
int pe[MAXN] = {0};
int np = 0;

int s = 0;
int l = 0, r = 0;

int d[MAXN] = {0};

int main(void)
{
  int i = 0;

  scanf("%d", &n);
  for(i = 0;i < n;++i)
  {
    scanf("%d", &(d[i]));

    if( 0 == l && 0 == r )
    {
      r = d[i];
      l = 1;
      s = i+1;

      if( 1 == r )
        r = 0;
    }
    else if( l > 0 && 0 == r )
    {
      l++;
      if( l > d[i] )
      {
        l = 0;
        ps[np] = s;
        pe[np] = i;
        np++;
      }
    }
    else if( r > 0 && 0 == l )
    {
      r--;
      if( 0 == r )
      {
        r = 0;
        ps[np] = i;
        pe[np] = s;
        np++;
      }
    }
    else if( l > 0 && r > 0 )
    {
      l++;
      r--;

      if( r > d[i] )
        r = d[i];
    }
  }

  printf("%d\n", np);
  for(i = 0;i < np;++i)
    printf("%d %d\n", ps[i], pe[i]);
  return 0;
}
