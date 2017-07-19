/* UESTC 2017 Summer Training #10 Div.2. Problem C, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <set>
#include <utility>

using namespace std;
typedef set< pair<int,int> > spii;

#define MAXV    10001
#define MAXE    200001

struct egde_t
{
    int id;
    int w;
    int nxt;
};
int front[MAXV];
egde_t edg[MAXE];
int nedges;
void add_edge(int u, int v, int w)
{
    int newedge = ++nedges;
    edg[newedge].id = v;
    edg[newedge].w = w;
    edg[newedge].nxt = u[front];
    u[front] = newedge;
}

int d[MAXV];
int solid[MAXV];
int dp[MAXV];
set<int> par[MAXV];

int dijstra(int s, int t)
{
    int v = s[front];
    spii q;
    dp[s] = 1;
    q.insert(make_pair(0, s));
    while(!q.empty())
    {
        auto it = q.begin();
        int u = it->second;
        int v = u[front];
        q.erase(it);
        solid[u] = 1;
        if(u == t) break;
        while(v)
        {
            int w = edg[v].id;
            if(!solid[w])
            {
                int newd = d[u]+edg[v].w;
                if( (0==d[w]) || (newd < d[w]) )
                {
                    q.erase(make_pair(d[w],w));
                    d[w] = d[u] + edg[v].w;
                    dp[w] = dp[u];
                    q.insert(make_pair(d[w],w));
                } else if (newd == d[w]) {
                    dp[w] += dp[u];
                    q.insert(make_pair(d[w],w));
                }
            }
            v = edg[v].nxt;
        }
    }
    return dp[t];
}

int main(void)
{
    int V = 0, E = 0;
    int u = 0, v = 0, w = 0;
    int s = 0, t = 0;
    scanf("%d%d", &V, &E);
    while(E--)
    {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u,v,w);
    }
    scanf("%d%d", &s, &t);
    printf("%d\n", dijstra(s,t));
    return 0;
}
