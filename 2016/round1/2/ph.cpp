/* UESTC 2016 Summer Training #2 Div.2.  Problem H. by Abreto, 201607121523. */
#include <cstdio>
#include <set>

#define TOMOD 1000000007
#define DOMOD(x)  ((x)%TOMOD)

using namespace std;

int N = 0;
int numbers[100024] = {0};
int max = 0, min = 0;
set<int> min_index, max_index;
int ansa = 0, ansb = 0;

void calc()
{
  int i = 0;
  int right[100024] = {0};

  if( ((min_index.count(0)!=0)&&(max_index.count(1)!=0)) || () )
  for(i = 2;i < N;++i)
  {
    ;
  }

}

int main(void)
{
  int T = 0;

  scanf("%d\n", &T);
  while(T--)
  {
    int i = 0;

    scanf("%d\n", &N);
    scanf("%d", &(numbers[0]));
    min = max = numbers[0];
    for(i = 1;i < N;++i)
    {
      scanf("%d", &(numbers[i]));
      if( numbers[i] < min )  min = numbers[i];
      else if (numbers[i] > max) max = numbers[i];
    }

    min_index.clear(); max_index.clear();
    for(i = 0;i < N;++i)
    {
      if( min == numbers[i] ) min_index.insert(i);
      else if (max == numbers[i]) max_index.insert(i);
    }

    calca();
    calcb();

    printf("%d %d\n", ansa, ansb);
  }

  return 0;
}
