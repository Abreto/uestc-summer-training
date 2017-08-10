/* UESTC 2017 Summer Training #26 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <cstdio>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

#define PROB    "cylinders"

void init(void)
{
#ifndef ABDEBUG
    freopen(PROB ".in", "r", stdin);
    freopen(PROB ".out", "w+", stdout);
#endif
}
#define mp make_pair
typedef long long int ll;
typedef pair<int,int> tc;
typedef pair< tc , int > state;
#define MAXXN   100001ll

#define MAXN    32
int n;
int x[MAXN];
int have[MAXXN];
int l;
char app[MAXN][MAXXN];

int bfs(void)
{
    int ret = 0;
    int i = 0, j = 0;
    int nwhile = 0;
    queue< state > q;
    if(0 == l) return 0;
    for(i = 0;i < n;++i) if(x[i] == l) return 1;
    for(i = 0;i < n;++i)
    {
        q.push(mp(mp(i,0),1)); app[i][0] = 1;
        q.push(mp(mp(0,x[i]),1)); app[0][x[i]] = 1;
    }
    while((!q.empty()))// && (nwhile++<772002))
    {
        vector<state> toadd;
        state cur = q.front(); q.pop();
        //printf("%d,%d,%d\n", cur.first.first, cur.first.second, cur.second);
        int newo = cur.second+1;
        tc nt = cur.first;
        if(l == cur.first.second) return cur.second;
        for(i = 0;i < n;++i) /* tap or sink */
        {
            nt.first = i;
            if(app[nt.first][nt.second]) continue;
            toadd.push_back(mp(nt,newo)); app[nt.first][nt.second]=1;
        }
        for(i = 0;i < n;++i) /* scale to a */
        {
            int delta = x[cur.first.first] - x[i];
            if(0 == delta) continue;
            nt.first = i;
            nt.second = cur.first.second + delta;
            if(nt.second < 0) break;
            if(nt.second == l) return newo;
            if(nt.second > x[n-1] || have[nt.second] || app[nt.first][nt.second]) continue;
            toadd.push_back(mp(nt,newo)); app[nt.first][nt.second]=1;
        }
        for(i = 0;i < n;++i) /* scale to b */
        {
            int delta = cur.first.second - x[i];
            if(0 == delta) continue;
            nt.first = i;
            nt.second = x[cur.first.first] + delta;
            if(nt.second < 0) break;
            if(nt.second == l) return newo;
            if(nt.second > x[n-1] || have[nt.second]) continue;
            if(app[nt.first][nt.second]) continue;
            toadd.push_back(mp(nt,newo)); app[nt.first][nt.second]=1;
        }/**/
        random_shuffle(toadd.begin(), toadd.end());
        for(auto s:toadd)
            q.push(s);
    }
    return -1;
}

int gcd(int a, int b) {return (0 == b)?a:gcd(b,a%b);}

void proc(void)
{
    int i = 0;
    scanf("%d", &n);
    for(i = 0;i < n;++i)
    {
        scanf("%d", x+i);
        have[x[i]] = 1;
    }
    scanf("%d", &l);
    int allgcd = x[1];
    for(i = 2;i < n;++i)
        allgcd = gcd(allgcd, x[i]);
    if(l % allgcd) puts("IMPOSSIBLE");
    else
    {
        int ans = bfs();
        if(-1 == ans) puts("IMPOSSIBLE");
        else printf("%d\n", ans);
    }
}

int main(void)
{
    init();
    proc();
    return 0;
}
