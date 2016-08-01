/* UESTC 2016 Summer Training #6 Div.2. Problem G, by Abreto, 201607161529. */
#include <stdio.h>

int current_time = 0;

typedef struct _patient
{
  int s;
  int r;
}patient, *p_patient;
int pcomp(patient p1, patient p2)
{
  int s1 = p1.s - p2.s;
  int s2 = current_time * (p2.r - p1.r);
  if( s1 < s2 )
    return 1;
  else if ( s1 == s2 && p1.r < p2.r )
    return 1;
  else if ( p1.s == p2.s && p1.r == p2.r )
    return 1;
  else
    return 0;
}


void solve(int casei)
{
  int N = 0;
  char eventtype = ' ';
  patient patients[100000];
  int deleted[100000] = {0};
  int nowpatents = 0;
  printf("Case #%d:\n", casei);

  scanf("%d\n", &N);
  while(N--)
  {
    scanf("%c ", &eventtype);
    if( 'P' == eventtype )
    {
      int t0 = 0, s0 = 0, r = 0;
      patient newp;
      scanf("%d %d %d\n", &t0, &s0, &r);
      newp.s = s0 - r*t0;
      newp.r = r;
      patients[nowpatents++] = newp;
    }
    else if( 'A' == eventtype )
    {
      int i = 0;
      int t = 0;
      int maxi[100000] = {0};
      int nmax = 0;
      int newpatients = 0;
      scanf("%d\n", &t);
      current_time = t;
      for(i = 0;i < nowpatents;++i)
        if( 0 == deleted[i] )
        {
          patients[newpatients] = patients[i];
          deleted[newpatients] = 0;
          if( 0 == nmax )
          {
            maxi[0] = newpatients;
            ++nmax;
          }
          else if( pcomp(patients[maxi[0]], patients[newpatients]) )
          {
            maxi[0] = newpatients;
            nmax = 1;
          }
          else if( patients[maxi[0]].s == patients[newpatients].s && patients[maxi[0]].r == patients[newpatients].r )
          {
            maxi[nmax++] = newpatients;
          }

          newpatients++;
        }
      for(i = 0;i < nmax;++i)
      {
        printf("%d %d\n", patients[maxi[i]].s+(patients[maxi[i]].r)*t, patients[maxi[i]].r);
        deleted[maxi[i]] = 1;
      }
      nowpatents = newpatients;
    }
  }
}

int main(void)
{
  int i = 0;
  int T = 0;

  scanf("%d", &T);
  for(i = 0;i < T;++i)
  {
    solve(i+1);
  }

  return 0;
}
