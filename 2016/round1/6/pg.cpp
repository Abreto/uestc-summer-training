/* UESTC 2016 Summer Training #6 Div.2. Problem G, by Abreto, 201607161403. */
#include <cstdio>
#include <queue>

using namespace std;

class patient
{
public:
  int t;
  int s;
  int r;
  patient(void):t(0),s(0),r(0){;}
  void updateto(int ttime)
  {
    s += r * (ttime-t);
    t = ttime;
  }
  int operator<(patient otherp)
  {
    if( s < otherp.s )
      return 1;
    else if ( s == otherp.s && r < otherp.r )
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
  printf("Case#%d:\n", casei);

  scanf("%d\n", &N);
  while(N--)
  {
    scanf("%c ", &eventtype);
    if( 'P' == eventtype )
    {
      int t0 = 0, s0 = 0, r = 0;
      patient newp;
      scanf("%d %d %d\n", &t0, &s0, &r);
      newp.t = t0;newp.s = s0;newp.r = r;
      patients[nowpatents++] = newp;
    }
    else if( 'A' == eventtype )
    {
      int i = 0;
      int t = 0;
      int maxi = 0;
      scanf("%d\n", &t);
      for(i = 0;i < nowpatents;++i)
        if( 0 == deleted[i] )
        {
          patients[i].updateto(t);
          if( patients[maxi] < patients[i] )
            maxi = i;
        }
      printf("%d %d\n", patients[maxi].s, patients[maxi].r);
      deleted[maxi] = 1;
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
