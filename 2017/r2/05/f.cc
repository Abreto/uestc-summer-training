/* /* UESTC 2017 Summer Training #21. Problem F, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN    64
#define MAXV    (MAXN*MAXN)
#define MAXE    (MAXV*MAXV)
struct edge_t
{
    int v, n, w;
    edge_t(){}
    edge_t(int vv, int nn, int ww):v(vv),n(nn),w(ww){}
}E[MAXE];
int nE;
int front[MAXV];
int find_edge(int u, int v)
{
    for(int e = u[front];e;e = E[e].n)
        if(E[e].v == v)
            return e;
    return 0;
}
void add_edge(int u, int v, int w)
{
    int ne = ++nE;
    E[ne] = edge_t(v, u[front], w);
    u[front] = ne;
}
void grant_e(int u, int v, int w)
{
    int e = find_edge(u,v);
    if(e) E[e].w += w;
    else add_edge(u,v,w);
}
void print_graph(void)
{
    int i = 0;
    for(i = 0;i < MAXV;++i)
        if(i[front])
        {
            printf("%d:", i);
            for(int e = i[front];e;e=E[e].n)
                printf(" %d(%d)", E[e].v, E[e].w);
            puts("");
        }
    puts("------------------");
}
int vis[MAXV];
int path[MAXV];
int dfs(int u, int t)
{
    vis[u] = 1;
    if(u == t) return 1;
    for(int e=u[front];e;e=E[e].n)
    {
        int v = E[e].v;
        if(!vis[v] && E[e].w && dfs(v,t))
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
        int minf = E[find_edge(s,path[s])].w;
        for(i = path[s];i != t;i = path[i])
            minf = min(minf, E[find_edge(i,path[i])].w);
        for(i = s;i != t;i = path[i])
        {
            grant_e(i, path[i], -minf);
            grant_e(path[i], i, minf);
        }
        flow += minf;
    }
    return flow;
}

int N, M, A, B;
char gird[MAXN][MAXN];

#define HASH(x,y)   ((x)*M+(y)+1)
#define S           HASH(0,-1)
#define T           HASH(N,0)

int main(void)
{
    int i = 0, j = 0;
    scanf("%d %d %d %d", &N, &M, &A, &B);
    for(i = 0;i < N;++i)
        scanf("%s", gird[i]);
    for(i = 0;i < N;++i)
        for(j = 0;j < M;++j)
        {
            if('.' == gird[i][j]) grant_e(S, HASH(i,j), B);
            else if ('#' == gird[i][j]) grant_e(HASH(i,j), T, B);
            if(j)
            {
                grant_e(HASH(i,j-1), HASH(i,j), A);
                grant_e(HASH(i,j), HASH(i,j-1), A);
            }
            if(i)
            {
                grant_e(HASH(i-1,j), HASH(i,j), A);
                grant_e(HASH(i,j), HASH(i-1,j), A);
            }
        }
    printf("%d\n", max_flow(S,T));
    return 0;
}
