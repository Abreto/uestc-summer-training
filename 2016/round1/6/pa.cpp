/* UESTC 2016 Summer Training #6 Div.2. Problem A, by Abreto, 201607161315. */
#include <cstdio>
#include <cstdlib>
#include <queue>

#define MAXN  128

using namespace std;

int N = 0, M = 0;
int A[MAXN] = {0};

int compar_int(const void *a, const void *b)
{
  return ( (*((int*)a)) - (*((int*)b)) );
}

int solve(void)
{
  int i = 0;
  int ans = 0;
  priority_queue<int> deltas;

  if( N == M )
    return 0;

  qsort(A, N, sizeof(int), compar_int);
  for(i = 1; i < N;++i)
  {
    int d = A[i] - A[i-1];
    ans += d;
    deltas.push(d);
  }

  for(i = 1;i < M;++i)
  {
    int d = deltas.top();
    ans -= d;
    deltas.pop();
  }

  return ans;
}

int main(void)
{
  int i = 0;
  int T = 0;

  scanf("%d", &T);
  for(i = 0;i < T;++i)
  {
    int j = 0;
    scanf("%d %d", &N, &M);

    for(j = 0;j < N;++j)
      scanf("%d", &(A[j]));

    printf("Case #%d: %d\n", i+1, solve());
  }

  return 0;
}
