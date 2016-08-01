/* UESTC 2016 Summer Training #1 Div.2.  Problem C. by Abreto, 201607111310. */
#include <stdio.h>

int main(void)
{
  int N = 0;
  int A = 0, B = 0;
  int n_unused_chairs = 0;
  int i = 0;

  scanf("%d\n", &N);
  for(i = 0;i < N;++i)
  {
    scanf("%d %d\n", &A, &B);
    n_unused_chairs += (B-A);
  }

  printf("%d\n", n_unused_chairs);
  return 0;
}
