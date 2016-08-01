/* UESTC 2016 Summer Training #1 Div.2.  Problem D. by Abreto, 201607111750. */
#include <stdio.h>
#define MAXN  100024

typedef struct _table
{
  int i;
  int size;
  int available;
}table, *p_table;

int N = 0, Q = 0;
table tables[MAXN]; /* increasing. */
int map_i_index[MAXN];
int top_tables = 0;

int main(void)
{
  int i = 0, j = 0, k = 0;
  int t = 0;
  char event[8] = " "; int T = 0;

  scanf("%d %d\n", &N, &Q);
  for(i = 0;i < N;++i)
  {
    scanf("%d", &t);
    tables[top_tables].i = i+1;
    tables[top_tables].size = t;
    tables[top_tables].available = 1;
    map_i_index[i+1] = top_tables;
    top_tables++;
  }

  for(i = 0;i < Q;++i)
  {
    int min_x = MAXN, min_x_index = 0;
    scanf("%s %d", event, &T);
    switch (event[0]) {
      case 'i':
        min_x = MAXN;
        for(j = 0;j < top_tables;++j)
          if( (1 == tables[j].available) && (tables[j].size >= T) )
          {
            if( tables[j].size < min_x )
            {
              min_x = tables[j].size;
              min_x_index = j;
            }
          }
        if( min_x == MAXN )
          printf("-1\n");
        else
        {
          printf("%d\n", tables[min_x_index].i);
          tables[min_x_index].available = 0;
        }
        break;
      case 'o':
        j = map_i_index[T];
        tables[j].available = 1;
        break;
    }
  }

  return 0;
}
