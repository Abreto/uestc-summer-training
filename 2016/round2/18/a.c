/* UESTC Summer Training #18 Div.2. Problem A. */
#include <stdio.h>

#define MAXN  10024

int N = 0;
int nkeys[MAXN] = {0};
int nfields = 0;

int main(void)
{
  int i = 0, j = 0;
  int t = 0;

  scanf("%d", &N);
  for(i = 0;i < N;++i)
  {
    scanf("%d", &t);
    nkeys[t] ++;
    if( t > j )
      j = t;
  }

  i = 1;
  while( i <= j )
  {
    if( 0 == nkeys[i] )
      i++;
    else if( 0 == nkeys[j] )
      j--;
    else
    {
      if( nkeys[j] > 1 )
      {
        
      }
    }
  }

  return 0;
}
