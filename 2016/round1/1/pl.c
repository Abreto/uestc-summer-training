/* UESTC 2016 Summer Training #1 Div.2.  Problem L. by Abreto, 201607111543. */
#include <stdio.h>
#define MAXN 32

#define reverse(x)  (('+'==(x))?('-'):('+'))

int N = 0;
char op[MAXN] = {0};
int A[MAXN] = {0};
int n_modifies = -1;
int test[MAXN] = {0};

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

int bfs(int depth, int start, int n)
{
  int i = 0, t = -1;
  if( depth == n )
  {
    test[n] ++;
    if( 0 == calc() )
    {
      n_modifies = depth;
      return depth;
    }
    else
      return -1;
  }
  for(i = start+1;i<(N-n+depth);++i)
  {
    op[i] = reverse(op[i]);
    t = bfs(depth+1, i, n);
    if(t > 0)
      return t;
    op[i] = reverse(op[i]);
  }
  return t;
}

int bfs_driver(int n)
{
  int i = 0, t = -1;
  for(i = 1;i < (N-n);++i)
  {
    op[i] = reverse(op[i]);
    t = bfs(1, i, n);
    if( t > 0 )
      return t;
    op[i] = reverse(op[i]);
  }
  return t;
}

int main(void)
{
  int i = 0;

  scanf("%d\n", &N);
  scanf("%d", &(A[0]));
  for(i = 1;i < N;++i)
    scanf(" %c %d", &(op[i]), &(A[i]));

  if( 0 == calc() )
  {
    n_modifies = 0;
    goto print_result;
  }

  for(i = 1;i < N;++i)
  {
    int t = -1;
    /* reverse i operators. */
    t = bfs_driver(i);
    if( t > 0 )
      goto print_result;
  }

print_result:
  if( n_modifies >= 0 )
    printf("%d\n", n_modifies);
  else
    printf("-1\n");
  return 0;
}
