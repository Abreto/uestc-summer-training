/* UESTC Summer Training #18 Div.2. Problem B. */
#include <stdio.h>
#include <string.h>

const char digit[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D',
'E','F'};

char origin[32] = {'0',0};
int l = 0;

int inc(int i)
{
  int count = 0;
  while( i >= 0 )
  {
    if( 'F' == origin[i] )
    {
      count++;
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
  return count;
}

void handle(int togenerate)
{
  int i = 0;
  int used[128] = {0};
  int nused = 0;
  for(i = (origin[0]>'0')?(0):(1);i < togenerate;++i)
    if( 1 == used[origin[i]] )
    {
      handle(i+1-inc(i));
      nused++;
      break;
    }
    else
      used[origin[i]] = 1;
  if( 0 == nused )
    if( togenerate < l )
    {
      int count = 0;
      for(i = 0;i < 16 && count < (l-togenerate);++i)
        if( 0 == used[digit[i]] )
        {
          origin[togenerate+count] = digit[i];
          ++count;
        }
    }
}

int main(void)
{
  scanf("%s", origin+1);
  l = strlen(origin);
  inc(l-1);
  handle(l);
  printf("%s\n", (origin[0]>'0')?(origin):(origin+1));
  return 0;
}
