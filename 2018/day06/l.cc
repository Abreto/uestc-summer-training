#include <cstdio>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;
typedef vector<int> VI;
typedef long long int ll;
typedef pair<ll,int> pli;
#define pb  push_back
#define mp  make_pair
#define fi  first
#define se  second

#define MAXN    (200002)
#define MAXM    (200002)
typedef struct edge
{
    int v;
    ll c;
    int id;
    ll give;
    edge *n;
    edge(void):v(0),c(0ll),id(0),n(NULL){give = -1;}
    edge(int vv, ll cc, int ii, edge *nn):v(vv),c(cc),id(ii),n(nn){give = -1;}
}*ep;
int ne;
edge E[MAXM<<1];
ep front[MAXN];
void add_edge(int u, int v, ll c, int id)
{
    E[ne] = edge(v, c, id, u[front]);
    u[front] = E+ne;
    ne++;
}

int n, m;

ll d[MAXN];
char solid[MAXN];
priority_queue< pli , vector<pli>, greater<pli> > q;
void dijstra(int s)
{
    q.push(mp(0ll, s));
    while(!q.empty())
    {
        auto it = q.top(); q.pop();
        int u = it.se;
        if(solid[u]) continue;
        solid[u] = 1;
        for(ep e = u[front];e;e = e->n)
        {
            int v = e->v;
            if(!solid[v])
            {
                ll newdis = d[u] + e->c;
                e->give = newdis;
                if( 0 == d[v] || (newdis < d[v]) )
                {
                    d[v] = newdis;
                    q.push(mp(d[v], v));
                }
            }
        }
    }
}

#define N   (MAXN<<1)
int tot;
VI g[N],tree[N],rg[N],bucket[N];
int sdom[N],par[N],dom[N],dsu[N],label[N];
int arr[N],rev[N],T;
int idmap[MAXM];
void dfs_adedge(int u, int f = 0)
{
    for(ep e = u[front];e;e = e->n)
        if(e->v != f)
        {
            if(e->give == d[e->v])  /* we need this edge */
            {
                ++tot;
                g[u].pb(tot);
                g[tot].pb(e->v);
                idmap[tot] = e->id;
                dfs_adedge(e->v, u);   /* TO CHECK */
            }
        }
}
void dfs0(int u)
{
    T++;arr[u]=T;rev[T]=u;
    label[T]=T;sdom[T]=T;dsu[T]=T;
    int sz = g[u].size();
    for(int i=0;i<sz;i++)
    {
        int w = g[u][i];
        if(!arr[w])
        {
            dfs0(w);
            par[arr[w]]=arr[u];
        }
        rg[arr[w]].pb(arr[u]);
    }
}
int Find(int u,int x=0)
{
    if(u==dsu[u])return x?-1:u;
    int v = Find(dsu[u],x+1);
    if(v<0)return u;
    if(sdom[label[dsu[u]]]<sdom[label[u]])
        label[u] = label[dsu[u]];
    dsu[u] = v;
    return x?v:label[u];
}
void Union(int u,int v)
{
    dsu[v] = u;
}
void construct(void)
{
    tot = n;
    dfs_adedge(1);
    assert(g[13][0] == 6);
    dfs0(1);
    for(int i=T;i>=1;i--)
    {
        int sz1 = rg[i].size(), sz2 = bucket[i].size();
        for(int j=0;j<sz1;j++)
            sdom[i] = min(sdom[i],sdom[Find(rg[i][j])]);
        if(i>1)bucket[sdom[i]].pb(i);
        for(int j=0;j<sz2;j++)
        {
            int w = bucket[i][j],v = Find(w);
            if(sdom[v]==sdom[w]) dom[w]=sdom[w];
            else dom[w] = v;
        }
        if(i>1)Union(par[i],i);
    }
    for(int i=2;i<=T;i++)
    {
        if(dom[i]!=sdom[i])dom[i]=dom[dom[i]];
        tree[rev[i]].pb(rev[dom[i]]);
        tree[rev[dom[i]]].pb(rev[i]);
    }
}

int ans[MAXM];
int sz[N];
void get_ans(int u, int p = 0)
{
    printf("%d goes to %d\n", p, u);
    for(auto v : tree[u])
    {
        if(v == p) continue;
        get_ans(v, u);
        sz[u] += sz[v];
    }
    sz[u] += (u <= n);
    printf("sz[%d] = %d\n", u, sz[u]);
    if(u > n) ans[idmap[u]] = sz[u];
}

int main(void)
{
    int i;
    scanf("%d%d", &n, &m);
    for(i = 0;i < m;i++)
    {
        int u, v; ll c;
        scanf("%d%d%lld", &u, &v, &c);
        add_edge(u, v, c, i);
        add_edge(v, u, c, i);
    }
    dijstra(1);
    construct();
    for(i = n+1;i <= tot;i++) printf("%d -> %d\n", i, idmap[i]);
    get_ans(1);
    for(i = 0;i < m;i++)
        printf("%d\n", ans[i]);
    return 0;
}
