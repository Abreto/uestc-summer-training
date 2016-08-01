/* UESTC 2016 Summer Training #7 Div.2. Problem I, by Abreto, 201607181314. */
#include <stdio.h>

int main(void)
{
  int i = 0;
  int n = 0 , k = 0;
  int balli = 0;
  int balls[128] = {0};
  int n_every_colour = 0;
  int repainted = 0;

  scanf("%d %d", &n, &k);
  n_every_colour = n/k;
  for(i = 0;i < n;++i)
  {
    scanf("%d", &balli);
    balls[balli]++;
  }

  for(i = 1;i <= k;++i)
    if( balls[i] > n_every_colour )
      repainted += (balls[i] - n_every_colour);

  printf("%d\n", repainted);
  return 0;
}
