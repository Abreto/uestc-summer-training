/* UESTC 2016 Summer Training #5 Div.2. Problem K, by Abreto, 201607151525. */
#include <stdio.h>

int main(void)
{
  int players = 0;
  int games[12] = {5,20,12,2,1,4,6,1,4,4,1,0};

  scanf("%d", &players);
  printf("%d\n", games[players]);

  return 0;
}
