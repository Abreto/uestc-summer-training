/* UESTC 2016 Summer Training #3 Div.2.  Problem C. by Abreto, 201607131211. */
#include <stdio.h>
#include <stdlib.h>


int digits[16515072] = {1};
int n_digits = 1;

int compare(const void *a, const void *b)
{
  return ( *((int *)b) - *((int *)a) );
}

void generate(void)
{
  int i = 0;
  int high = 0;
  for(i = 0;i < n_digits;++i)
  {
    int t = (digits[i] * 2) + high;
    digits[i] = t % 10;
    high = t / 10;
  }
  if( high )
    digits[n_digits++] = high;
  qsort(digits, n_digits, sizeof(int), compare);
}

int main(void)
{
  int i = 0, n = 0;

  scanf("%d", &n);
  for(i = 1;i < n;++i)
    generate();

  for(i = n_digits;i > 0;i--)
    printf("%d", digits[i-1]);
  printf("\n");
  return 0;
}
