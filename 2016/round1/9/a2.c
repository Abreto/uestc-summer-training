/* UESTC 2016 Summer Training #9 Div.2. Problem A, by Abreto, 201607201238. */
#include <stdio.h>
#include <string.h>

/*#define MAXN  100002*/
#define MAXN 128

typedef long long int ll;

ll sum = 0;
char A[MAXN] = {0};

int subseq(int start, int end)
{
  if( end == start + 1 )
    return 1;
  else if( end == start + 3 )
    return 2;
  else if( end == start + 5 )
  {
    char third = A[start+2];
    switch (third) {
      case '(':
        return 3;
        break;
      case ')':
        sum += 6;
        return 3;
        break;
    }
  }
  else
  {
    int i = 0, j  = 0;
    int subseqs = 1;
    int topsubseqs[MAXN] = {0};
    int ntopsubseq = 0;
    int stack[MAXN] = {0};
    int stack_top = 0;
    int npairs = 0;
    int sumi[MAXN] = {0}; /* t[0..i] = sumi[i+1]; */

    for(i = start+1;i < end;++i)
    {
      if( '(' == A[i] )
      {
        stack[stack_top++] = i;
      }
      else if( ')' == A[i] )
      {
        stack_top--;
        if( 0 == stack_top )
        {
          topsubseqs[ntopsubseq] = subseq(stack[0], i);
          sumi[ntopsubseq+1] = sumi[ntopsubseq] + topsubseqs[ntopsubseq];
          subseqs += topsubseqs[ntopsubseq];
          ntopsubseq++;
        }
      }
    }

    for(i = 0;i < ntopsubseq-1;++i)
      npairs += topsubseqs[i] * (sumi[ntopsubseq] - sumi[i+1]);

    sum += (ll)npairs * (ll)(end-start+1);

    return subseqs;
  }
}

int main(void)
{
  scanf("%s", A);
  subseq(0, strlen(A)-1);
  printf("%lld\n", sum);
  return 0;
}
