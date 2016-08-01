/* UESTC 2016 Summer Training #9 Div.2. Problem I, by Abreto, 201607201428. */
#include <stdio.h>
#include <string.h>

int ok = 0;
int len[3] = {0};
char num[3][128] = {{0}};
int order[3] = {0, 1, 2};

int cmp(int i, int j) /* return 1 if num[i] < num[j], 0 if num[i] == num[j] */
{
  if( ( len[i] < len[j] ) )
    return 1;
  else if( len[i] > len[j] )
    return -1;
  else
  {
    int k = 0;
    for(k = 0;k < len[i];++k)
      if( num[i][k] < num[j][k] )
        return 1;
      else if( num[i][k] > num[j][k] )
        return -1;
    return 0;
  }
}

void sort(void)
{
  int i = 0, j = 0;
  for(i = 0;i < 2;++i)
    for(j = 2;j > i;--j)
      if( 1 == cmp(order[j], order[j-1]) )
      {
        int t = 0;
        t = order[j];
        order[j] = order[j-1];
        order[j-1] = t;
      }
}

int check()
{
  if( len[order[2]] > (len[order[1]]+1) && len[order[2]] > (len[order[0]]+1) )
    return 0;
  else
  {
    int i = 0;
    int flag = 0;
    for(i = 0;i < len[order[2]];++i)
    {
      int t = 0;

      if( i < len[order[0]] )
        t += num[order[0]][len[order[0]]-i-1];
      if( i < len[order[1]] )
        t += num[order[1]][len[order[1]]-i-1];

      t += flag;
      flag = t / 10;
      t %= 10;

      if( t != num[order[2]][len[order[2]]-i-1] )
        return 0;
    }
    return 1;
  }
}

int main(void)
{
  int i = 0, j = 0;

  for(i = 0;i < 3;++i)
  {
    scanf("%s", num[i]);
    len[i] = strlen(num[i]);
    for(j = 0;j < len[i];++j)
      num[i][j] = num[i][j] - '0';
    if( 1 == len[i] && 0 == num[i][0] )
      ok = 1;
  }

  if( ok )
  {
    printf("YES\n");
    return 0;
  }
  sort();
  {
    int oorder[3] = {order[0], order[1], order[2]};
    if( check() )
    {
      printf("YES\n");
      return 0;
    }
    order[1] = oorder[0];
    if( check() )
    {
      printf("YES\n");
      return 0;
    }
    order[1] = oorder[1];
    order[0] = oorder[1];
    if( check() )
    {
      printf("YES\n");
      return 0;
    }
    order[0] = oorder[0];
    order[1] = oorder[0];
    order[2] = oorder[1];
    if( check() )
    {
      printf("YES\n");
      return 0;
    }
  }

  printf("NO\n");
  return 0;
}
