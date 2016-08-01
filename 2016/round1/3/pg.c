/* UESTC 2016 Summer Training #3 Div.2.  Problem G. by Abreto, 201607131211. */
#include <stdio.h>
#include <math.h>

int A = 0;

int main(void)
{
  int N = 0;

  while( EOF != scanf("%d\n", &N) )
  {
    int i = 0;
    int res = 1;
    double t = 0;

    for(i = 0;i < N;++i)
    {
      scanf("%d ", &A);
      if( 0 == res )
        continue;

      t = sqrt(A);
      if( t != (double)((int)t) )
        res = 0;
    }

    printf("%s\n", res?"Yes":"No");
  }

  return 0;
}
