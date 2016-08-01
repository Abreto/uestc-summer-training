/* UESTC 2016 Summer Training #3 Div.2.  Problem C. by Abreto, 201607131613. */
#include <stdio.h>
#include <string.h>

#define FILE_IN "input.txt"
#define FILE_OUT  "output.txt"

/*16515072*/

int digits[1024] = {1};
int count[10] = {0};
int n_digits = 1;


int main(void)
{
  int x = 0, n = 0;

  /*freopen(FILE_IN, "r", stdin);
  freopen(FILE_OUT, "w+", stdout);*/

  scanf("%d", &n);
  for(x = 1;x < n;++x)
  {
    int i = 0;
    int high = 0;
    int t = 0;
    int need_sorting = 0;

    memset(count, 0, sizeof(count));
    for(i = 0;i < n_digits;++i)
    {
      t = (digits[i] * 2) + high;
      digits[i] = t % 10;
      high = t / 10;
      ++count[digits[i]];
      if( (0==need_sorting) && (i > 0) && (digits[i]>digits[i-1]) )  need_sorting = 1;
    }
    if( high )
    {
      digits[n_digits++] = high;
      ++count[high];
      if( (0==need_sorting) && (digits[i]>digits[i-1]) )  need_sorting = 1;
    }

    if( need_sorting )
    {
      high = 0;
      for(i = 9;i > 0;--i)
      {
        while( count[i] > 0 )
        {
          digits[high++] = i;
          --count[i];
        }
      }
      n_digits = high;
    }

    for(i = n_digits;i > 0;i--)
      printf("%d", digits[i-1]);
    printf("\n");
  }

  return 0;
}
