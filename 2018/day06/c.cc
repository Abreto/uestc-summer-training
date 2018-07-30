#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> pip;
#define mp(l,a,b) make_pair(l, make_pair(a,b))

#define MAXN    (100010)
struct edge
{
    int v;
    edge *n;
    edge(void):v(0),n(NULL){}
    edge(int vv, edge *nn):v(vv),n(nn){}
}E[MAXN<<1];
int ne;
edge *front[MAXN];
void add_edge(int u, int v)
{
    E[ne] = edge(v, u[front]);
    u[front] = E+ne;
    ne++;
}

int n, m;
int d[MAXN];    /* depth, d[0] = 0, d[1] = 1; */
int f[MAXN][32];/* f[u][i]: (1<<i)-th father of u */
int son[MAXN], sz[MAXN];
int top[MAXN];
int id[MAXN]; int tot;

void get_sth(int u, int fa = 0)
{
    d[u] = d[fa]+1;
    f[u][0] = fa;
    for(int i = 0;f[f[u][i]][i];i++)
        f[u][i+1] = f[f[u][i]][i];
    sz[u] = 1;
    son[u] = -1;
    for(edge *e = front[u];e;e = e->n)
        if(e->v != fa)
        {
            get_sth(e->v, u);
            sz[u] += sz[e->v];
            if( -1 == son[u] || sz[son[u]] < sz[e->v] )
                son[u] = e->v;
        }
}
void link(int u, int fa)
{
    id[u] = (++tot);
    top[u] = fa;
    if(son[u] > 0)
    {
        link(son[u], fa);
    }
    for(edge *e = u[front];e;e = e->n)
        if(e->v != f[u][0] && e->v != son[u])
            link(e->v, e->v);
}

int sum[MAXN<<2];
void maintain(int o)
{
    sum[o] = sum[o<<1] + sum[o<<1|1];
}
void inc(int p, int o = 1, int l = 1, int r = n)
{
    if(p < l || r < p) return;
    if(p == l && r == p)
    {
        sum[o]++;
    } else {
        int mid = (l+r)>>1;
        inc(p, o<<1, l, mid);
        inc(p, o<<1|1, mid+1, r);
        maintain(o);
    }
}
int qry(int L, int R, int o = 1, int l = 1, int r = n)
{
    if(R < L) return 0;
    if(R < l || r < L) return 0;
    if(L <= l && r <= R) return sum[o];
    else
    {
        int mid = (l+r)>>1;
        return qry(L, R, o<<1, l, mid) + qry(L, R, o<<1|1, mid+1, r);
    }
}

void select(int u)
{
    inc(id[u], 1);
}
int is_coverd(int u, int v)
{
    int ret = 0;
    while(top[u] != top[v])
    {
        if( d[top[u]] > d[top[v]] )
        {
            ret += qry(id[top[u]], id[u]);
            u = f[top[u]][0];
        } else {
            ret += qry(id[top[v]], id[v]);
            v = f[top[v]][0];
        }
    }
    ret += qry(min(id[u], id[v]), max(id[u], id[v]));
    return ret;
}

void prehandle(void)
{
    get_sth(1);
    link(1, 1);
}

int lca(int u, int v)
{
    if(d[u] < d[v]) swap(u, v);
    /* make d[u] >= d[v] */
    for(int i = 20;i >= 0;i--)
        if(d[u] - (1<<i) >= d[v])
            u = f[u][i];
    /* up u */
    if (u == v) return u;
    /* now d[u] == d[v] */
    for(int i = 20;i >= 0;i--)
        if( d[u] - (1<<i) > 0 && f[u][i] != f[v][i] )
        {
            u = f[u][i];
            v = f[v][i];
        }
    assert(f[u][0] == f[v][0]);
    return f[u][0];
}

pip lcas[MAXN];
bool compar(const pip &x, const pip &y)
{
    return d[x.first] > d[y.first];
}


unsigned int ans;
int selected[MAXN];
int main(void)
{
    int i;
    scanf("%d", &n);
    for(i = 1;i < n;i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    prehandle();
    scanf("%d", &m);
    for(i = 0;i < m;i++)
    {
        int a, b, l;
        scanf("%d%d", &a, &b);
        l = lca(a, b);
        lcas[i] = mp(l, a, b);
    }
    sort(lcas, lcas+m, compar);
    for(i = 1;i < m;i++) assert(d[lcas[i].first] <= d[lcas[i-1].first]);
    for(i = 0;i < m;i++)
    {
        int l = lcas[i].first, a = lcas[i].second.first, b = lcas[i].second.second;
        if( !is_coverd(a, b) )
        {
            select(l);
            selected[ans++] = l;
        }
    }
    printf("%u\n", ans);
    for(i = 0;i < ans;i++) printf("%d ", selected[i]);
    puts("");
    return 0;
}
