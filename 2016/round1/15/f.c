/* UESTC 2016 Summer Training #15 Div.2. Problem F, by Abreto, 20160727. */
#include <stdio.h>

int main(void)
{
  int i = 0;
  int l = 0, r = 0;
  int restdays = 0;

  scanf("%d %d", &l, &r);
  --l;
  for(i = 2;(i <= l) || (i <= r);++i)
  {
    if( i <= l )
      l -= (l / i);
    if( i <= r )
      r -= (r / i);
  }

  printf("%d\n", r-l);
  return 0;
}
