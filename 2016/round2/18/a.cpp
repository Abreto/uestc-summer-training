/* UESTC Summer Training #18 Div.2. Problem A. */
#include <cstdio>
#include <queue>
#include <map>

#define MIN(a, b) ( ((a)<(b))?(a):(b) )
#define MAXN  10024

using namespace std;

int N = 0;
int nfields = 0;
priority_queue<int> keys;


int main(void)
{
  int i = 0;
  int t = 0;
  int k[3] = {0};

  scanf("%d", &N);
  for(i = 0;i < N;++i)
  {
    scanf("%d", &t);
    keys.push(t);
  }

  while( keys.size() > 2 )
  {
    for(i = 0;i < 3;++i)
    {
      k[i] = keys.top();
      keys.pop();
    }
    nfields++;
    for(i = 0;i < 3;++i)
    {
      if( (--k[i]) > 0 )
        keys.push(k[i]);
    }
  }
  if( 2 == keys.size() )
  {
    k[0] = keys.top(); keys.pop();
    k[1] = keys.top(); keys.pop();
    nfields += MIN( (k[0]+k[1])/3 , MIN(k[0],k[1]) );
  }


  printf("%d\n", nfields);
  return 0;
}
