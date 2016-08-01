/* UESTC 2016 Summer Training #10 Div.2. Problem B, by Abreto, 201607211541. */
#include <cstdio>
#include <cstring>
#include <map>
#include <string>

#define MAXINT  (1<<31-1)
#define REDUCTION_LIMITI  46340
#define MIN(a,b) (((a)<(b))?(a):(b))

using namespace std;

typedef struct _rationaln
{
  int up;
  int down;
}rationaln, *p_rationaln;

void do_reduction_force(p_rationaln n)
{
  int x = MIN(n->up, n->down);
  for(x ; x > 1 ; --x )
    if( (0 == (n->up)%x) && (0 == (n->down)%x) )
    {
      (n->up) /= x;
      (n->down) /= x;
      x = MIN(n->up, n->down) + 1;
    }
}

void do_reduction(p_rationaln n)
{
  if( n->up >= REDUCTION_LIMITI || n->down >= REDUCTION_LIMITI )
    do_reduction_force(n);
}

void print_n(rationaln n)
{
  int i = 0;
  int nsignd = 0;
  int afterdecmi = 0;
  char output[64] = "";
  int len = 0;
  do_reduction_force(&n);
  sprintf(output, "%.16lf", (double)(n.up) / (double)(n.down));
  len = strlen(output);
  while( output[i] < '1' || output[i] > '9' )
  {
    switch(output[i])
    {
    case '.':
      printf("0.");
      afterdecmi = 1;
      break;
    case '0':
      if( afterdecmi )
        printf("0");
      break;
    }
    ++i;
  }
  while(nsignd < 5)
  {
    if( i < len )
    {
      char ch = output[i];
      if( '0' <= ch && ch <= '9' )
        nsignd++;
      printf("%c", ch);
      ++i;
    }
    else
      printf("%d", (++nsignd)?0:0);
  }
}

int is_zero(rationaln n)
{
  return ( 0 == n.up || 0 == n.down );
}

/* return <0 if n1 < n2, 0 if n1==n2, >0 if n1 > n2. */
int cmp(rationaln n1, rationaln n2)
{
  long long int part1 = (long long int)(n1.up) * (long long int)(n2.down);
  long long int part2 = (long long int)(n1.down) * (long long int)(n2.up);
  long long int cond = part1 - part2;
  if( cond > 0 )
    return 1;
  else if( 0 == cond )
    return 0;
  else
    return -1;
}

rationaln multiply(rationaln a, rationaln b)
{
  rationaln ans = {0,0};
  ans.up = a.up * b.up;
  ans.down = a.down * b.down;
  do_reduction(&ans);
  return ans;
}

int m = 0;
/* generally, 2 for what Jack wants, 1 for what Jack is willing to trade. */
map<string, int> nametoid;
int ngoods;
rationaln ratios[128][128] = {{{0,0}}};
int npath[128][128] = {{0}};
rationaln minratio[128];
int nways = 0;

rationaln curratio;
char visited[128] = {0};

void dfs(int cur, rationaln tomul, int totalpath)
{
  rationaln cur_back = curratio;
  curratio = multiply(cur_back, tomul);
  int cond = cmp(minratio[cur], curratio);
  visited[cur] = 1;

  if( cond < 0 )
  {
    visited[cur] = 0;
    curratio = cur_back;
    return;
  }

  if( 2 == cur )
  {
    if( cond > 0 )
    {
      minratio[2] = curratio;
      nways = totalpath;
    }
    else if( 0 == cond )
      nways += totalpath;
  }
  else
  {
    int next = 0;

    minratio[cur] = curratio;
    for(next = 2;next <= ngoods;next++)
      if( 0 == visited[next] && (npath[cur][next] > 0) ) // !is_zero(ratios[cur][next]) )
        dfs(next, ratios[cur][next], totalpath * npath[cur][next]);
  }

  visited[cur] = 0;
  curratio = cur_back;
}

void dfs_entry(void)
{
  int i = 0;
  visited[1] = 1;
  for(i = 2;i <= ngoods;++i)
    if( npath[1][i] > 0 ) //if( !is_zero(ratios[1][i]) )
    {
      curratio.up = curratio.down = 1;
      dfs(i, ratios[1][i], npath[1][i]);
    }
  visited[1] = 0;
}



int main(void)
{
  int T = 0, n = 0;

  scanf("%d", &n);
  for(T = 0;T < n;++T)
  {
    int i = 0, j = 0;
    char source[128] = "", dist[128] = "";
    string sour, dis;

    scanf("%s %s %d", dist, source, &m);

    /* clear. */
    nametoid.clear();
    for(i = 1;i <= m*2;++i)
    {
      for(j = 1;j <= m*2;++j)
        npath[i][j] = 0;
      minratio[i].up = MAXINT; minratio[i].down = 1;
    }

    nametoid[string(source)] = 1;
    nametoid[string(dist)] = 2;
    ngoods = 2;
    for(i = 0;i < m;++i)
    {
      rationaln ratio;
      p_rationaln tostore;
      int s = 0, t = 0;
      scanf("%d %s %d %s",&(ratio.down),dist,&(ratio.up),source);
      sour = source;dis = dist;
      if( 0 == nametoid[sour] )
        nametoid[sour] = ++ngoods;
      if( 0 == nametoid[dis] )
        nametoid[dis] = ++ngoods;
      do_reduction_force(&ratio);
      s = nametoid[sour]; t = nametoid[dis];
      tostore = &(ratios[s][t]);
      if( npath[s][t] > 0 )
      {
        int cond = cmp(*tostore, ratio);
        if( 0 == cond )
          npath[s][t]++;
        else if( cond > 0 )
        {
          npath[s][t] = 1;
          *tostore = ratio;
        }
      }
      else
      {
        *tostore = ratio;
        npath[s][t] = 1;
      }
    }

    dfs_entry();

    printf("Case %d: ", T+1);
    print_n(minratio[2]);
    printf(" %d\n", nways);
  }

  return 0;
}
