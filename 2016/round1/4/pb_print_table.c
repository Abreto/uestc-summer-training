/* UESTC 2016 Summer Training #4 Div.2. Problem B, by Abreto, 201607141256. */
/* FILE: print table */
#include <stdio.h>

#define MAXD  1000000024

char days[MAXD];

int main(void)
{
  int i = 0;
  int N = 0;
  int l = 0, r = 0;
  int ans = 0;

  scanf("%d %d", &l, &r);
  for(i = 2;i < r;++i)
  {
    int d = 0;int count = 0;
    int blank = 0;

    count = i-1;
    for(d = 1;d <= r;++d)
    {
      if( 0 == days[d] )
      {
        if( count ) count--;
        else
        {
          days[d] = i;
          count = i-1;
        }
        blank++;
      }
    }

    if( blank < i )
      break;
  }

  /*printf("char table[%d] = {0", N+1);
  for(i = 1;i <= N;++i)
    printf(", %d", days[i]);
  printf("};\n");*/
  for(i = l;i <= r;++i)
    if( 0 == days[i] )
      ans++;
  printf("%d\n", ans);
  return 0;
}
