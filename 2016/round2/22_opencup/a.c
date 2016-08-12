/* UESTC Summer Training Petrozavodsk Summer-2015. Moscow Subregional 2010. */
/* Problem A, by Abreto. */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI  3.14159265358979

int n = 0, r = 0;
int a[1024] = {0};
double S = 0.0;

int compar(const void *a, const void *b)
{
  return ( (*((int*)a)) - (*((int*)b)) );
}

int main(void)
{
  int i = 0;

  scanf("%d %d", &n, &r);
  for(i = 0;i < n;++i)
    scanf("%d", &(a[i]));

  qsort(a, n, sizeof(int), compar);

  S = r*r;
  for(i = 1;i < n;++i)
  {
    int d = a[i] - a[i-1];
    if( d <= r )
    {
      double costheta = (double)(d)/(double)(2*r);
      double cos2theta = (double)2 * costheta * costheta - (double)1;
      double twicetheta = acos(cos2theta);
    }
  }

  return 0;
}
