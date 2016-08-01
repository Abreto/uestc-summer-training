/* UESTC 2016 Summer Training #2 Div.2.  Problem B. by Abreto, 201607121523. */
#include <stdio.h>

#define SGN(x)  (((x)>0)?1:0)

typedef struct _spell
{
  char type;
  int attr[6];
}spell, *p_spell;

int N = 0;
spell spells[64];

int is_in_spell(int i, int j)
{
  int k = 0;
  int x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0;
  int tmp = 0;
  for(k = 0;k < N;++k)
    switch (spells[k].type)
    {
      case 'T':
        x1 = spells[k].attr[0] - i;
        y1 = spells[k].attr[1] - j;
        x2 = spells[k].attr[2] - i;
        y2 = spells[k].attr[3] - j;
        x3 = spells[k].attr[4] - i;
        y3 = spells[k].attr[5] - j;
        tmp = SGN(x1*x2+y1*y2) + SGN(x2*x3+y2*y3) + SGN(x1*x3+y1*y3);
        
        break;
      case 'S':
        break;
      case 'C':
        break;
    }
}

int main(void)
{
  int T = 0;

  scanf("%d\n", &T);
  while (T--)
  {
    int i = 0, j = 0;
    int people_saved = 0;

    scanf("%d\n", &N);
    for(i = 0;i < N;++i)
    {
      scanf("%c", &(spells[i].type));
      switch (spells[i].type)
      {
        case 'T':
          scanf("%d %d %d %d %d %d", &(spells[i].attr[0]), &(spells[i].attr[1]), &(spells[i].attr[2]), &(spells[i].attr[3]), &(spells[i].attr[4]), &(spells[i].attr[5]));
          break;
        case 'S':
          scanf("%d %d %d", &(spells[i].attr[0]), &(spells[i].attr[1]), &(spells[i].attr[2]));
          break;
        case 'C':
          scanf("%d %d %d", &(spells[i].attr[0]), &(spells[i].attr[1]), &(spells[i].attr[2]));
          break;
      }
    }

    for(i = 1;i <= 50;++i)
      for (j = 1; j <= 50; j++)
      {
        people_saved += is_in_spell(i,j);
      }

    printf("%d\n", people_saved);
  }

  return 0;
}
