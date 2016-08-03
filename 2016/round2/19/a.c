/* UESTC Summer Training #19. Problem A. */
#include <stdio.h>
#include <stdlib.h>

int compar(const void *a ,const void *b)
{
  return ( (*((int*)a)) - (*((int*)b)) );
}

int main(void)
{
  int i = 0, T = 0;
  int nums[128] = {0};
  int nclusters = 0;

  scanf("%d", &T);
  for(i = 0;i < T;++i)
  {
    int j = 0;
    int N = 0, K = 0;
    scanf("%d %d", &N, &K);
    for(j = 0;j < N;++j)
      scanf("%d", &(nums[j]));
    qsort(nums, N, sizeof(int), compar);
    nclusters = 1;
    for(j = 1;j < N;++j)
      if( nums[j] - nums[j-1] > K )
        nclusters++;

    printf("Case #%d: %d\n", i+1, nclusters);
  }

  return 0;
}
