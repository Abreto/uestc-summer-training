/* UESTC 2016 Summer Training #8 Div.2. Problem H, by Abreto, 201607191403. */
#include <stdio.h>

int n = 0;
int coefficient[10] = {0};
int bases[10] = {1, 2, 6, 30, 210, 2310, 30030, 510510, 9699690, 223092870};
int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void print(int i)
{
  if( i > 0 )
  {
    int x = 0;
    for(x = 0;x < i;++x)
      printf("*%d", primes[x]);
  }
}

int main(void)
{
  while(1)
  {
    scanf("%d", &n);
    if( 0 ==  n ) break;
    else
    {
      int i = 0;
      int n2 = n;
      for(i = 9;i >= 0;--i)
      {
        coefficient[i] = 0;
        if( n2 >= bases[i] )
        {
          coefficient[i] = n2 / bases[i];
          n2 -= coefficient[i] * bases[i];
        }
      }

      printf("%d = ", n);
      for(i = 0;i < 10;++i)
        if( coefficient[i] > 0 )
        {
          printf("%d", coefficient[i]);
          print(i);
          break;
        }
      for(i++;i<10;++i)
        if( coefficient[i] > 0 )
        {
          printf(" + %d", coefficient[i]);
          print(i);
        }
      printf("\n");
    }
  }

  return 0;
}
