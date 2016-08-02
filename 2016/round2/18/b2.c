/* UESTC Summer Training #18 Div.2. Problem B. */
#include <stdio.h>
#include <string.h>

char origin[32] = {'0',0};
int l = 0;

void inc(int i)
{
  while( i >= 0 )
  {
    if( 'F' == origin[i] )
    {
      origin[i] = '0';
      i--;
    }
    else
    {
      if( '9' == origin[i] )
        origin[i] = 'A';
      else
        origin[i]++;
      break;
    }
  }
}

int check(void)
{
  int i = 0;
  int used[128] = {0};
  int nused = 0;
  for(i = (origin[0]>'0')?(0):(1);i < l;++i)
    if( 1 == used[origin[i]] )
      return 0;
    else
      used[origin[i]] = 1;
    return 1;
}

int main(void)
{
  scanf("%s", origin+1);
  l = strlen(origin);
  inc(l-1);
  while( !check() ) inc(l-1);
  printf("%s\n", (origin[0]>'0')?(origin):(origin+1));
  return 0;
}
