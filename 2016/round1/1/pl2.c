/* UESTC 2016 Summer Training #1 Div.2.  Problem L. by Abreto, 201607111611. */
#include <stdio.h>
#define MAXN 32
#define MAXINT  2147483647

#define BIT(x,i)  ((x)&(1<<(i-1)))
#define reverse(x)  (('+'==(x))?('-'):('+'))

int N = 0;
char op[MAXN] = {0};
int A[MAXN] = {0};
int min_n_modifies = MAXINT;

int calc(void)
{
  int i = 0;
  int sum = A[0];
  for(i = 1;i < N;++i)
    switch (op[i]) {
      case '+':
        sum += A[i];
        break;
      case '-':
        sum -= A[i];
        break;
    }
    return sum;
}

int main(void)
{
  int i = 0;
  int subset = 0;

  scanf("%d\n", &N);
  scanf("%d", &(A[0]));
  for(i = 1;i < N;++i)
    scanf(" %c %d", &(op[i]), &(A[i]));

  if( 0 == calc() )
  {
    printf("0\n");
    goto die;
  }

  for(subset = 1;subset < (1<<(N-1));++subset)
  {
    int n_modifies = 0;
    /* reverse */
    for(i = 1;i < N;++i)
    {
      if( BIT(subset,i) )
      {
        n_modifies++;
        op[i] = reverse(op[i]);
      }
    }

    if( n_modifies > min_n_modifies )
      goto next_subset;

    if( (0 == calc()) &&(n_modifies < min_n_modifies) )
      min_n_modifies = n_modifies;

next_subset:
    /* restore */
    for(i = 1;i < N;++i)
    {
      if(BIT(subset,i))
        op[i] = reverse(op[i]);
    }
  }

  if( min_n_modifies < MAXINT )
    printf("%d\n", min_n_modifies);
  else
    printf("-1\n");
die:;
  return 0;
}
