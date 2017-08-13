/* UESTC 2017 Summer Training #28 Div.2. Problem J, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

#define MAXN    20000
#define MAXM    100000
#define MAXLGN  16
#define INF     100000
int N, M, S;

struct edge
{
    int v, w, n;
};
int nE;
edge E[(MAXM<<1)+1];
int front[MAXN+1];
void add_edge(int u, int v, int w)
{
    int ne = ++nE;
    E[ne].v = v; E[ne].w = w; E[ne].n = u[front];
    u[front] = ne;
}

namespace disjoint
{
    int par[MAXN+1];
    void init(void)
    {
        int i = 0;
        for(i = 0;i <= MAXN;++i)
            par[i] = i;
    }
    int fdr(int i)
    {
        return (i == par[i]) ? i : (par[i] = fdr(par[i]));
    }
    void uni(int i, int j)
    {
        par[fdr(i)] = fdr(j);
    }
}

priority_queue< pair<int, pair<int,int> > > q;

void make_tree(void)
{
    int nedge = 0;
    disjoint::init();
    while(nedge < N-1 && !q.empty())
    {
        auto cur = q.top(); q.pop();
        int w = cur.first;
        int a = cur.second.first, b = cur.second.second;
        int fa = disjoint::fdr(a), fb = disjoint::fdr(b);
        if(fa != fb)
        {
            add_edge(a, b, w);
            add_edge(b, a, w);
            disjoint::uni(a,b);
            nedge++;
        }
    }
}

int dep[MAXN+1];
int ancestor[MAXN+1][MAXLGN];
int minw[MAXN+1][MAXLGN];

void dfs(int u, int fa)
{
    ancestor[u][0] = fa; dep[u] = dep[fa] + 1;
    for(int e = u[front];e;e = E[e].n)
    {
        int v = E[e].v, w = E[e].w;
        if(v != fa)
        {
            minw[v][0] = w;
            dfs(v, u);
        }
    }
}

void init_system(void)
{
    int i = 0, w = 0;
    int t = 0;
    dep[0] = -1;
    dfs(1,0);
    for(w = 1;(t=(1<<w)) < N;++w)
        for(i = 1;i <= N;++i) if( dep[i] >= t )
        {
            ancestor[i][w] = ancestor[ancestor[i][w-1]][w-1];
            minw[i][w] = min(minw[i][w-1], minw[ancestor[i][w-1]][w-1]);
        }
}

int query(int a, int b)
{
    if(dep[a] < dep[b]) return query(b,a);
    else    /* now dep[s] > dep[t] */
    {
        int i = 0;
        int maxbit = MAXLGN-1;
        int ret = INF;
        //while((1<<maxbit) <= dep[a]) maxbit++;
        /* first up a to same dep with b. */
        for(i = maxbit;i >= 0;i--)
            if(dep[a] - (1<<i) >= dep[b])
            {
                ret = min(ret, minw[a][i]);
                a = ancestor[a][i];
            }
        if(a == b) return ret;
        for(i = maxbit;i >= 0;i--)
            if(dep[a] - (1<<i) >= 0 && ancestor[a][i] != ancestor[b][i])
            {
                ret = min(ret, min(minw[a][i], minw[b][i]));
                a = ancestor[a][i];
                b = ancestor[b][i];
            }
        ret = min(ret, min(minw[a][0], minw[b][0]));
        return ret;
    }
}

int main(void)
{
    int i = 0;
    scanf("%d %d %d", &N, &M, &S);
    for(i = 0;i < M;++i)
    {
        int A, B, W;
        scanf("%d %d %d", &A, &B, &W);
        q.push(make_pair(W,make_pair(A,B)));
    }
    make_tree();
    init_system();
    while(S--)
    {
        int L, H;
        scanf("%d %d", &L, &H);
        printf("%d\n", query(L,H));
    }
    return 0;
}
