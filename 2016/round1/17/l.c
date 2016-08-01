/* UESTC 2016 Summer Training #17 Div.2. Problem L, by Abreto, 20160728. */
#include <stdio.h>

int main(void)
{
  int X = 0, Y = 0;
  int C = 0;

  scanf("%d %d %d", &X, &Y, &C);
  if( X + Y < C )
    printf("Impossible\n");
  else
  {
    if( X > C )
      X = C;
    while(X > -1)
    {
      int B = C - X;
      if( 0 <= B && B <= Y )
      {
        printf("%d %d\n", X, B);
        break;
      }
      --X;
    }
  }

  return 0;
}
