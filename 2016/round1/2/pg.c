/* UESTC 2016 Summer Training #2 Div.2.  Problem G. by Abreto, 201607121255. */
#include <stdio.h>
#include <string.h>

int main(void)
{
  int i = 0, T = 0;
  int N = 0;
  char corridor[64] = " ";
  int possible = 1;

  scanf("%d\n", &T);
  while(T--)
  {
    scanf("%s\n", corridor);
    N = strlen(corridor);
    possible = 1;
    for(i = 0;i < N;++i)
      if( 'D' == corridor[i] )
      {
        possible = 0;
        break;
      }

    printf("%s\n", (possible)?"Possible":"You shall not pass!");
  }


  return 0;
}
