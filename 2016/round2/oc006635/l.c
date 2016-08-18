/* UESTC Summer Training Southern Subregional 2013. */
/* Problem L, by Abreto. */
#include <stdio.h>

#define MIN(a,b)  (((a)<(b))?(a):(b))

int n = 0, d = 0;
int a = 0, b = 0;
int state = -1;  /* 1 for inc, 0 for dec */
int ncon = 0;
int prev = 0;
int shares = 0;

int main(void)
{
  int i = 0;

  scanf("%d %d %d %d", &n, &d, &a, &b);
  scanf("%d", &prev);
  for(i = 1;i < n;++i)
  {
    int price = 0;

    scanf("%d", &price);
    if( price == prev )
    {
      state = -1;
      ncon = 0;
    }
    else if ( price > prev )
    {
      int limitshare = 0;
      int sharetobuy = 0;
      if( 1 != state )
      {
        state = 1;
        ncon = 1;
      }
      else
        ncon++;

      limitshare = ncon * a;
      sharetobuy = MIN(limitshare, d/price);
      d -= sharetobuy * price;
      shares += sharetobuy;
    }
    else if(price < prev)
    {
      int limitshare = 0;
      int sharetosell = 0;

      if( 0 != state )
      {
        state = 0;
        ncon = 1;
      }
      else
        ncon++;

      limitshare = ncon * b;
      sharetosell = MIN(limitshare, shares);
      d += sharetosell * price;
      shares -= sharetosell;
    }

    prev = price;
  }

  printf("%d %d\n", d, shares);
  return 0;
}
