/* UESTC 2016 Summer Training #3 Div.2.  Problem A. by Abreto, 201607131508. */
#include <stdio.h>

#define MAXN  16

int N = 0, M = 0;
int bits[MAXN] = {0};
int code[MAXN] = {0};

int main(void)
{
  int i = 0;

  scanf("%d %d", &N, &M);
  for(i = 0;i < N;++i)
    scanf("%d", &(bits[i]));
  for(i = 0;i < M;++i)
    scanf("%d", &(code[i]));
  ;

  return 0;
}
