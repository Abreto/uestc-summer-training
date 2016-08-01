/* UESTC 2016 Summer Training #5 Div.2. Problem E, by Abreto, 201607151434. */
#include <cstdio>
#include <map>

#define MAXN  16

using namespace std;

int n = 0, m = 0;
int total_min[MAXN], total_max[MAXN];
int mini[MAXN], maxi[MAXN];
map<int,int>  calced[MAXN][MAXN];
map<int,int>  count_m[MAXN][MAXN];

int count(int f, int t, int bones)
{
  if( (calced[f][t])[bones] )
    return (count_m[f][t])[bones];
  if( f == t )
  {
    if( mini[f] <= bones && bones <= maxi[f] )
      return 1;
    else
      return 0;
  }
  else if (f < t)
  {
    int lbones = 0;
    int mid = (f+t)/2;
    int l_low_bones = total_min[mid] - total_min[f-1];  /* l: f to mid */
    int l_upp_bones = total_max[mid] - total_max[f-1];  /* r: mid+1 to t */
    int r_low_bones = total_min[t] - total_min[mid];
    int r_upp_bones = total_max[t] - total_max[mid];
    int nsolutions = 0;
    for(lbones = l_low_bones;lbones <= l_upp_bones;++lbones)
    {
      int rbones = bones - lbones;
      int ls = 0, rs = 0;
      if( rbones < r_low_bones )
        break;
      ls = count(f, mid, lbones);
      rs = count(mid+1, t, rbones);
      nsolutions += (ls * rs);
    }
    (calced[f][t])[bones] = 1;
    (count_m[f][t])[bones] = nsolutions;
    return nsolutions;
  }
}

int main(void)
{
  int N = 0;

  scanf("%d", &N);
  while(N--)
  {
    int i = 0;
    int min_i = 0, max_i = 0;

    total_min[0]  = 0;
    total_max[0] = 0;
    mini[0] = 0;
    maxi[0] = 0;
    scanf("%d %d", &n, &m);
    for(i = 1;i <= n;++i)
    {
      scanf("%d %d", &min_i, &max_i);
      total_min[i] = total_min[i-1] + min_i;
      total_max[i] = total_max[i-1] + max_i;
      mini[i] = min_i;
      maxi[i] = max_i;
    }

    if( m < total_min[n] || m > total_max[n] )
      printf("0\n");
    else if( m == total_min[n] || m == total_max[n] )
      printf("1\n");
    else
      printf("%d\n", count(1, n, m));
  }

  return 0;
}
