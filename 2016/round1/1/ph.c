/* UESTC 2016 Summer Training #1 Div.2.  Problem H. by Abreto, 201607111510. */
#include <stdio.h>

#define calc_total(a,b,c,d,e) ((a)+((b)*5)+((c)*10)+((d)*20)+((e)*50))
#define get_type(x) ( (0==(x)) ? (1) :    ( (1==(x)) ? (5) :        ( (2==(x)) ? (10) :            ((3==(x))?(20):(50))        )    ))

int result = 1;

int change_total = 0;
int n_notes[5] = {0}; /* 0 for 1, 1 for 5, 2 for 10, 3 for 20, 4 for 50. */

int N = 0;

int main(void)
{
  int i = 0, j = 0;
  int K = 0, F1 = 0, F2 = 0, F3 = 0, F4 = 0, F5 = 0;

  scanf("%d\n", &N);
  for(i = 0;i < N;++i)
  {
    int give = 0, change_to_return = 0;
    scanf("%d %d %d %d %d %d\n", &K, &F1, &F2, &F3, &F4, &F5);
    give = calc_total(F1,F2,F3,F4,F5);
    if( give == K )
      goto next_student;
    change_to_return = give - K;
    if( change_to_return > change_total )
    {
      result = 0;
      goto print_result;
    }

    for(j = 4;j >= 0;--j)
    {
      int t = get_type(j);
      if( 0 == n_notes[j] )
        continue;
      if( 0 == change_to_return )
        break;
      while (change_to_return >= t)
      {
        if( 0 == n_notes[j] ) goto next_type;
        change_to_return -= t;
        n_notes[j]--;
      }
next_type:
      ;
    }

    if( change_to_return )
    {
      result = 0;
      goto print_result;
    }

next_student:
    n_notes[0] += F1;
    n_notes[1] += F2;
    n_notes[2] += F3;
    n_notes[3] += F4;
    n_notes[4] += F5;
    change_total = calc_total(n_notes[0],n_notes[1],n_notes[2],n_notes[3],n_notes[4]);
  }

print_result:
  printf("%s\n", (result)?("yes"):("no"));
  return 0;
}
