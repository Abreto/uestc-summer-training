/* UESTC 2016 Summer Training #5 Div.2. Problem I, by Abreto, 201607151641. */
#include <stdio.h>
#include <string.h>

#define MAXN  128

int n = 0;
char lines[MAXN][MAXN] = {{0}};
int count_left[MAXN] = {0};
int count_right[MAXN]= {0};
int have_started_with_left = 0;
int have_ended_with_right = 0;
int total_left = 0;
int total_right = 0;
int stack[MAXN] = {0};
int top_stack = 0;

int main(void)
{
  int i = 0, j = 0;;

  scanf("%d", &n);
  for(i = 0;i < n;++i)
  {
    int len = 0;
    scanf("%s", lines[i]);
    top_stack = 0;
    len = strlen(lines[i]);
    for(j = 0;j < len;++j)
    {
      if( '(' == lines[i][j] )
        stack[top_stack++] = j;
      else if( ')' == lines[i][j] )
        if( top_stack > 0 )
        {
          lines[i][stack[top_stack-1]] = 0;
          lines[i][j] = 0;
          top_stack--;
        }
    }
    top_stack = 0;
    for(j = 0;j < len;++j)
      if( lines[i][j] > 0 )
      {
        switch (lines[i][j])
        {
          case '(':
            count_left[i]++;
            break;
          case ')':
            count_right[i]++;
            break;
        }
        lines[i][top_stack++] = lines[i][j];
      }
    lines[i][top_stack] = 0;
    if( '(' == lines[i][0] )
      have_started_with_left = 1;
    else if( ')' == lines[i][top_stack-1] )
      have_ended_with_right = 1;
    total_left += count_left[i];
    total_right += count_right[i];
  }

  if( total_right != total_left )
  {
    printf("No\n");
  }
  else if( 0 == total_left )
    printf("Yes\n");
  else if( have_started_with_left && have_ended_with_right )
  {
    printf("Yes\n");
  }
  else
    printf("No\n");

  return 0;
}
