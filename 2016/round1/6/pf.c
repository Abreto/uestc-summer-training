/* UESTC 2016 Summer Training #6 Div.2. Problem F, by Abreto, 201607161249. */
#include <stdio.h>
#include <string.h>

char line[50012] = {0};

int count()
{
  int i = 0, j = 0;
  int len = strlen(line);
  int midlen = len/2;
  int ans = 0;

  i = 0;j = len-1;
  while(i <= j)
    if( line[i] == line[j] )
    {
      ans += (2 - (i==j));
      i++; --j;
    }
    else
    {
      int k = 0;
      for(k = i+1;k < midlen;++k)
        if( line[k] == line[j] )
          if( 0 == strncmp(line+i, line+j-(k-i), k-i+1) )
          {
            ans += 2;
            j = j - (k-i) -1;
            i = k + 1;
            goto next_bit;
          }
      ans++;
      j = j - (k-i) - 1;
      i = k + 1;
next_bit:
      ;
    }
    return ans;
}

int main(void)
{
  int i = 0;
  int N = 0;

  scanf("%d\n", &N);
  for(i = 0;i < N;++i)
  {
    scanf("%s\n", line);
    printf("Case #%d: %d\n", i+1, count());
  }

  return 0;
}
