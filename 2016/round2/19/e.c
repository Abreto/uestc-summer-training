/* UESTC Summer Training #19. Problem E. */
#include <stdio.h>
#include <string.h>

#define MAXN  20002

int N = 0, K = 0;
int parent[MAXN] = {0};
char passed[MAXN] = {0};

int main(void)
{
  int i = 0, T = 0;

  scanf("%d", &T);
  #ifdef DEBUGGING
  {
    printf("T[%d]\n", T);
  }
  #endif
  for(i = 0;i < T;++i)
  {
    int j = 0;
    scanf("%d %d", &N, &K);
    memset(parent, 0, (N+1)*sizeof(int));
    for(j = 1;j <= N;++j)
      scanf("%d", &(parent[j]));

    printf("Case #%d:\n", i+1);
    for(j = 0;j < K;++j)
    {
      char line[128] = {0};
      char command = 0;
      int op1 = 0, op2 = 0;

      scanf("%s", line);
      command = line[0];
      scanf("%d", &op1);
#ifdef DEBUGGING
  printf("[%d]%c,%d\n", j, command, op1);
#endif
      if( 'C' == command )
      {
        parent[op1] = 0;
      }
      else
      {
        int k = 0;
        int ok = 0;
        scanf("%d", &op2);
        memset(passed, 0, (N+1)*sizeof(int));
        k = op1;
        while( k > 0 )
        {
          passed[k] = 1;
          k = parent[k];
        }
        k = op2;
        while( k > 0 )
        {
          if( 1 == passed[k] )
          {
            ok = 1;
            break;
          }
          k = parent[k];
        }

        printf("%s\n", ok?"YES":"NO");
      }
    }
    #ifdef DEBUGGING
    {
      printf("i[%d],%d,%d\n", i,i<T,T);
    }
    #endif
  }

  return 0;
}
