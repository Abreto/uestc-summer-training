/* UESTC 2016 Summer Training #8 Div.2. Problem A, by Abreto, 201607191326. */
#include <stdio.h>

#define SGN(x)  (((x)<0)?1:0)

int main(void)
{
  int N = 0, T1 = 0, T2 = 0, T3 = 0;

  while(1)
  {
    scanf("%d %d %d %d", &N, &T1, &T2, &T3);
    if( 0 == N && 0 == T1 && 0 == T2 && 0 == T3 )
      break;
    else
    {
      int commonticks = 3*N;
      double average = 0.0;
      commonticks += T2-T1 + N*SGN(T2-T1);
      commonticks += T2-T3 + N*SGN(T2-T3);
      average = (double)commonticks + ((double)(N-1))/((double)2);
      printf("%.3lf\n", average);
    }
  }

  return 0;
}
