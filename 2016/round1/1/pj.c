/* UESTC 2016 Summer Training #1 Div.2.  Problem J. by Abreto, 201607111437. */
#include <stdio.h>

#define MAXN  128

int N = 0;
char state[MAXN] = {0};
int n_child[MAXN] = {0};
int child_list[MAXN][MAXN] = {{0}};

void print_spaces(int nest)
{
  int i = 0;
  for(i = 0;i < nest;++i)
    printf("  ");
}

void print_object(int i, int nest)
{
  print_spaces(nest);
  if (0 == n_child[i])
  {
    printf("  object%d\n", i);
  }
  else if ( '+' == state[i] )
  {
    printf("+ object%d\n", i);
  }
  else
  {
    int j = 0;
    printf("- object%d\n", i);
    for(j = 0;j < n_child[i];++j)
      print_object(child_list[i][j], nest+1);
  }
}

int main(void)
{
  int i = 0, j = 0;

  scanf("%d", &N);
  for(i = 0;i < N+1;++i)
  {
    scanf("\n%c %d", &(state[i]), &(n_child[i]));
    for(j = 0;j < n_child[i];++j)
    {
      scanf("%d", &(child_list[i][j]));
    }
  }

  /* print project */
  if( 0 == n_child[0] )
  {
    printf("  project\n");
  }
  else if ( '+' == state[0] )
  {
    printf("+ project\n");
  }
  else
  {
    printf("- project\n");
    for(i = 0;i < n_child[0];++i)
      print_object(child_list[0][i], 1);
  }

  return 0;
}
