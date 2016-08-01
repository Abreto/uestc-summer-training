/* UESTC 2016 Summer Training #11 Div.2. Problem A, by Abreto, 201607221426. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int m = 0, n = 0;
char attraction[64][64] = {{0}};  /* raw index starts from 1, but col from 0. */
int order[64] = {0};
int countmat[64][64] = {{0}};
int maxsize = 0;

int compar(const void *a, const void *b)
{
  return strcmp( attraction[*((int*)b)] , attraction[*((int*)a)] );
}

void load_input(void)
{
  int i = 0, j = 0;
  scanf("%d %d", &m, &n);
  for(i = 1;i <= m;++i)
  {
    order[i] = i;
    scanf("%s", attraction[i]);
  }
  qsort(order+1, m, sizeof(int), compar);
#ifdef DEBUGGING
{
  for(i = 0;i <= m;++i)
    printf("order[%d]:%d, %s\n", i, order[i], attraction[order[i]]);
}
#endif
}

void handle(void)
{
  int i = 0,j = 0;
  for(i = 1;i <= m;++i)
  {
    int rioi = order[i], riopi = order[i-1];
    int nsame[64] = {0};
    int nmem = 0;
    for(j = 0;j < n;++j)
    {
      if( attraction[rioi][j] == attraction[riopi][j] )
        countmat[rioi][j] = countmat[riopi][j] + 1;
      else
        countmat[rioi][j] = 1;

      if( '1' == attraction[rioi][j]  )
        (nsame[countmat[rioi][j]])++;

      if( nsame[countmat[rioi][j]] > 0 && (nmem = nsame[countmat[rioi][j]] + countmat[rioi][j]) > maxsize )
        maxsize = nmem;
    }
#ifdef DEBUGGING
{
  for(j = 0;j < 10;++j)
    printf("%d,", nsame[j]);
  printf("\n");
}
#endif
  }
#ifdef DEBUGGING
{
  for(i = 0;i <= m;++i)
  {
    for(j = 0;j < n;++j)
      printf("%d ", countmat[order[i]][j]);
    printf("\n");
  }
}
#endif
}

int main(void)
{
  int i = 0, T = 0;

  scanf("%d", &T);
  for(i = 0;i < T;++i)
  {
    maxsize = 0;
    load_input();
    handle();
    printf("Case %d: %d\n", i+1, maxsize);
  }

  return 0;
}
