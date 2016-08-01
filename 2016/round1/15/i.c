/* UESTC 2016 Summer Training #15 Div.2. Problem I, by Abreto, 20160727. */
#include <stdio.h>

typedef long long int ll;

int main(void)
{
  int b = 0;
  int c = 0, d = 0;
  int k = 0, p = 0;
  ll delta = 0;
  double trans = 0.0;

  scanf("%d", &b);
  scanf("%d %d", &c, &d);
  scanf("%d %d", &k, &p);

  delta = (k*(k+1)) / 2;
  delta *= (ll)d;
  delta += (ll)k*(ll)c;
  delta *= (ll)p;
  trans = ((double)delta) / ((double)100);
  trans -= (double)b;

  if( (trans - 0.0) > 1e-6 )
    printf("Cash\n%.2lf\n", trans);
  else
    printf("Insurance\n%.2lf\n", -trans);

  return 0;
}
