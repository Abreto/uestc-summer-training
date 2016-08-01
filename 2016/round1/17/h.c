/* UESTC 2016 Summer Training #17 Div.2. Problem L, by Abreto, 20160728. */
#include <stdio.h>

const char nums[4][4] = {"16", "06", "68", "88"};

int main(void)
{
  int n = 0;

  scanf("%d", &n);
  if( n > 4 )
    printf("Glupenky Pierre\n");
  else
  {
    int i = 0;
    printf("%s", nums[0]);
    for(i = 1;i < n;++i)
      printf(" %s", nums[i]);
    printf("\n");
  }

  return 0;
}
