/* UESTC 2016 Summer Training #6 Div.2. Problem G, by Abreto, 201607161450. */
#include <cstdio>
#include <queue>

using namespace std;

int current_time = 0;

class patient
{
public:
  int s;
  int r;
  patient(void):s(0),r(0){;}
  int operator<(patient otherp)
  {
    int s1 = s + r * current_time;
    int s2 = otherp.s + current_time * otherp.r;
    if( s1 < s2 )
      return 1;
    else if ( s1 == s2 && r < otherp.r )
      return 1;
    else
      return 0;
  }
  int operator>(patient otherp)
  {
    return (otherp<(*this));
  }
};

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
      int maxi = -1;
      int newpatients = 0;
      scanf("%d\n", &t);
      current_time = t;
      for(i = 0;i < nowpatents;++i)
        if( 0 == deleted[i] )
        {
          patients[newpatients] = patients[i];
          deleted[newpatients] = 0;
          if( (maxi < 0) || (patients[maxi] < patients[i]) )
            maxi = newpatients;
          newpatients++;
        }
      printf("%d %d\n", patients[maxi].s+(patients[maxi].r)*t, patients[maxi].r);
      deleted[maxi] = 1;
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
