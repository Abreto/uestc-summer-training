/* UESTC 2017 Summer Training #32 Div.2. Problem F, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>
using namespace std;

#define MAXN    (301)
#define MAXD    (MAXN<<1)
#define MAXV    ((MAXN<<1)+MAXN*MAXN+2)
#define MAXE    (MAXV<<2)
struct edge
{
    static int N;
    int v, w;
    edge *n;
    edge(void):v(0),w(0),n(NULL){}
    edge(int vv, int ww, edge *nn):v(vv),w(ww),n(nn){}
};
int nE;
edge E[MAXE];
edge *front[MAXV];
void add_edge(int u, int v, int w)
{
    int ne = ++nE;
    E[ne] = edge(v, w, u[front]);
    u[front] = &(E[ne]);
}
edge *find_edge(int u, int v)
{
    for(edge *e = u[front];e != NULL;e = e->n)
        if(e->v == v)
            return e;
    return NULL;
}
void grant_e(int u, int v, int w)
{
    edge *e = find_edge(u, v);
    if(NULL == e) add_edge(u,v,w);
    else e->w += w;
}

int vis[MAXV];
int path[MAXV];
int dfs(int u, int t)
{
    vis[u] = 1;
    if(u == t) return 1;
    for(edge *e = u[front];e != NULL;e = e->n)
    {
        int v = e->v;
        if(!vis[v] && e->w && dfs(v,t))
        {
            path[u] = v;
            return 1;
        }
    }
    return 0;
}
int find_path(int s, int t)
{
    memset(vis, 0, sizeof(vis));
    return dfs(s,t);
}
int max_flow(int s, int t)
{
    int flow = 0;
    while(find_path(s,t))
    {
        int i = 0;
        int minf = find_edge(s,path[s])->w;
        for(i = path[s];i != t;i = path[i])
            minf = min(minf, find_edge(i,path[i])->w);
        for(i = s;i != t;i = path[i])
        {
            grant_e(i, path[i], -minf);
            grant_e(path[i], i, minf);
        }
        flow += minf;
    }
    return flow;
}

int n;

set<int> have[MAXD];
int napp;
unordered_map<int,int> a2id;
int id2a[MAXV];

#define S       (0)
#define T       (MAXV-1)
#define DIAG(i) (i)
#define NUM(a)  (2*n+(a))
#define V2N(v)  ((v)-2*n)

int main(void)
{
    int i = 0, j = 0;
    int ai = 0;
    scanf("%d", &n);
    for(i = 1;i <= n;++i)
        for(j = 1;j <= n;++j)
        {
            scanf("%d", &ai);
            if(!a2id.count(ai))
            {
                a2id[ai] = ++napp;
                id2a[napp] = ai;
            }
            have[n+j-i].insert(a2id[ai]);
        }
    for(i = 1;i <= 2*n-1;++i)
    {
        grant_e(S, DIAG(i), 1);
        for(auto id:have[i])
            grant_e(DIAG(i), NUM(id), 1);
    }
    for(auto aid:a2id)
        grant_e(NUM(aid.second), T, 1);
    int mf = max_flow(S,T);
    if(mf != 2*n - 1) puts("NO");
    else
    {
        printf("YES");
        for(i = 1;i <= 2*n-1;i++)
        {
            int u = DIAG(i);
            for(edge *e = u[front];e != NULL;e = e->n)
                if(0 == e->w)
                {
                    printf(" %d", id2a[V2N(e->v)]);
                    break;
                }
        }
        puts("");
    }
    return 0;
}
