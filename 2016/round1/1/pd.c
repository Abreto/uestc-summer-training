/* UESTC 2016 Summer Training #1 Div.2.  Problem D. by Abreto, 201607111742. */
#include <stdio.h>
#define MAXN  100024

typedef struct _table
{
  int i;
  int size;
  int available;
}table, *p_table;

void table_cp(table a, p_table b)
{
  b->i = a.i;
  b->size = a.size;
  b->available = a.available;
}

int N = 0, Q = 0;
table tables[MAXN]; /* increasing. */
int top_tables = 0;
int map_i_index[MAXN];

void insert(table x)
{
  int j = 0, k = 0;
  for(j = 0;j < top_tables;++j)
  {
    if( (tables[j].size == x.size) && (tables[j].i > x.i) )
      break;
    if( (tables[j].size > x.size) )
      break;
  }
  for(k = top_tables;k > j;k--)
  {
      table_cp(tables[k-1], &(tables[k]));
  }
  tables[j].i = x.i;
  tables[j].size = x.size;
  tables[j].available = x.available;
  map_i_index[x.i] = j;
  top_tables++;
}

int main(void)
{
  int i = 0, j = 0, k = 0;
  int t = 0;
  char event[8] = " "; int T = 0;

  scanf("%d %d\n", &N, &Q);
  for(i = 0;i < N;++i)
  {
    table tmp;
    scanf("%d", &t);
    tmp.i = i+1;
    tmp.size = t;
    tmp.available = 1;
    insert(tmp);
  }

  for(i = 0;i < Q;++i)
  {
    scanf("%s %d", event, &T);
    switch (event[0]) {
      case 'i':
        for(j = 0;j < top_tables;++j)
          if( (1 == tables[j].available) && (tables[j].size >= T) )
            break;
        if( j == top_tables )
          printf("-1\n");
        else
        {
          printf("%d\n", tables[j].i);
          tables[j].available = 0;
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
