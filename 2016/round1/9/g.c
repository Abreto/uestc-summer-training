/* UESTC 2016 Summer Training #9 Div.2. Problem E, by Abreto, 201607201633. */
#include <stdio.h>
#include <string.h>

int n = 0;
char str[100002] = {0};

int main(void)
{
  int i = -1;
  int ncount0 = 0, ncount1 = 0;

  scanf("%s", str);
  while( '\0' != str[++i] )
    switch( str[i] )
    {
    case '0':
      ncount0++;
      break;
    case '1':
      ncount1++;
      break;
    }

  printf("%d\n", ncount0<ncount1?ncount0:ncount1);
  return 0;
}
