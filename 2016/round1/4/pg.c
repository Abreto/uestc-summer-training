/* UESTC 2016 Summer Training #4 Div.2. Problem G, by Abreto, 2016071424. */
#include <stdio.h>
#include <math.h>

int main(void)
{
  int inner = 0;
  int x[10] = {0}, y[10] = {0};
  double distance = 0.0;

  scanf("%d %d %d %d", &(x[0]), &(y[0]), &(x[1]), &(y[1])); /* 0 p1, 1p2 */
  scanf("%d %d %d %d", &(x[2]), &(y[2]), &(x[3]), &(y[3])); /* 2 v1, 3v2 */

  /* u=v2-v1 */x[4] = x[3] - x[2]; y[4] = y[3] - y[2];
  /* v5=P1P2 */x[5] = x[1] - x[0]; y[5] = y[1] - y[0];
  /* u·v5: */inner = x[4] * x[5] + y[4] * y[5];

  if( inner >= 0 )
  {
    x[6] = x[0] - x[1];
    y[6] = y[0] - y[1];
    distance = sqrt(x[6]*x[6]+y[6]*y[6]);
  }
  else
  {
    int outter = 0;
    double len = 0.0;
    /* P1u=P1P2+u */x[6] = x[5] + x[4]; y[6] = y[5] + y[4];
    /* p1u×p1p2: */outter = x[6]*y[5] - x[5]*y[6];
    outter = (outter<0)?(-outter):outter;
    len = sqrt(x[4]*x[4] + y[4]*y[4]);
    distance = ((double)outter) / len;
  }

  printf("%.15lf\n", distance);
  return 0;
}
