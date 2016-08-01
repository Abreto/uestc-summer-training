#include <stdio.h>

int onetod(int d)
{
  int i = 2;
  int ndays = d;
  while(ndays >= i)
  {
    ndays -= ndays/i;
    i++;
  }
  return ndays;
}

int main(void)
{
  int l = 0, r = 0;

  scanf("%d %d", &l, &r);
  printf("%d\n", onetod(r)-onetod(l));

  return 0;
}
