/* UESTC 2016 Summer Training #1 Div.2.  Problem F. by Abreto, 201607111349 */
#include <stdio.h>
#define MAXN  100024

int main(void)
{
  int i = 0;
  int N = 0, M = 0, Q = 0;
  int A = 0, B = 0;
  int places_the_student_is_in[MAXN] = {0};
  int n_students_in_the_places[MAXN] = {0};
  int n_citis_not_covered = 0;

  scanf("%d %d %d\n", &N, &M, &Q);
  for(i = 0;i < N;++i)
  {
    scanf("%d", &A);
    places_the_student_is_in[i+1] = A;
    n_students_in_the_places[A] ++;
  }

  /* count the cities which are not covered. */
  for(i = 0;i < M;++i)
    if( 0 == n_students_in_the_places[i+1] )
      n_citis_not_covered++;

  for(i = 0;i < Q;++i)
  {
    int tmp = 0;
    scanf("%d %d", &A, &B); /* move the Ath student to the Bth city. */
    tmp = places_the_student_is_in[A];  /* tmp is the city which A was in. */
    n_students_in_the_places[tmp] --;
    if( 0 == n_students_in_the_places[tmp] )
      n_citis_not_covered++;
    places_the_student_is_in[A] = B;
    if( 0 == n_students_in_the_places[B] )
      n_citis_not_covered --;
    n_students_in_the_places[B] ++;

    printf("%d\n", n_citis_not_covered);
  }

  return 0;
}
