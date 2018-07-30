/* Nowcoder#4 J. */
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;
typedef vector<int> vi;
#define pb push_back
typedef pair<int,int> pii;
#define mp make_pair
#define fi first
#define se second

#define MAXN    (200002)

int n, nins;
int a[MAXN];
vi g[MAXN]; /* i is idx in real array */
int in[MAXN];

/* restore the idx in real array */
queue<int> q;
/* (val,idx(in real array)) */
priority_queue< pii , vector<pii> , greater<pii> > pq;

int failed;
int asq[MAXN];
int nas;
int nout;

int md[MAXN<<2];
int lazy[MAXN<<2];
void build(int o = 1, int l = 1, int r = n)
{
    md[o] = 0;
    lazy[o] = 0;
    if(l < r)
    {
        int mid = (l+r)>>1;
        build(o<<1, l, mid);
        build(o<<1|1, mid+1, r);
    }
}
void markall(int v, int o)
{
    md[o] += v;
    lazy[o] += v;
}
void pushdown(int o)
{
    if(lazy[o])
    {
        markall(lazy[o], o<<1);
        markall(lazy[o], o<<1|1);
        lazy[o] = 0;
    }
}
void q0(int next = -1, int o = 1, int l = 1, int r = n)
{
    if(0 == md[o])
    {
        if(l == r)
        {
            if( -1 != a[l-1] )
            {
                if(-1 != next)
                {
                    g[l-1].pb(next);
                    in[next]++;
                }
                q.push(l-1);
            } else {
                if (-1 != next)
                    failed = 1;
            }
        } else {
            int mid = (l+r)>>1;
            pushdown(o);
            q0(next, o<<1, l, mid);
            q0(next, o<<1|1, mid+1, r);
        }
    }
}
void upd(int next, int L, int R, int v, int o = 1, int l = 1, int r = n)
{
    if(R < L) return;
    if(R < l || r < L) return;
    L = max(1, L);
    R = min(n, R);
    if(L <= l && r <= R)
    {
        markall(v, o);
        q0(next, o, l, r);
    } else {
        int mid = (l+r)>>1;
        pushdown(o);
        upd(next, L, R, v, o<<1, l, mid);
        upd(next, L, R, v, o<<1|1, mid+1, r);
        md[o] = min(md[o<<1], md[o<<1|1]);
    }
}


void myclear(void)
{
    failed = 0;
    nas = 0;
    nins = 0;
    nout = 0;
    while(!q.empty()) q.pop();
    while(!pq.empty()) pq.pop();
    build();
    for(int i = 0;i < n;i++)
    {
        in[i] = 0;
        g[i].clear();
    }
}

void proc(void)
{
    scanf("%d", &n);
    myclear();
    for(int i = 0;i < n;i++)
    {
        scanf("%d", a+i);
        if(a[i] != -1) nins++;
    }
    /**
     * real int: [0,n-1]
     * seg inte: [1,n]
     **/
    for(int i = 0;i < n;i++)
    {
        if(-1 != a[i])
        {
            int p = a[i] % n;
            if(p < i)
            {
                upd(-1, p+1, i, 1);
                /* increase [p,i-1] in real interval */;
            } else if(p > i) {
                upd(-1, p+1, n, 1);
                /* increase [p,n-1] in real interval */;
                upd(-1, 1, i, 1);
                /* increase [0,i-1] in real interval */;
            }
        }
    }
    q0();
    /* add (val, pos) which indegree[pos] == 0 to the priority queue */
    while(!q.empty())
    {
        int i = q.front(); q.pop();
        int v = a[i]; /* now indegree[i] has already be 0 */
        // printf("considering (%d,%d)\n", v, i);
        int p = v % n;
        nas++;
        if(p < i)
        {
            upd(i, p+1, i, -1);
            /* descrease [p,i-1] in real interval and add those (v,p) which in[p] = 0 to pq */;
        } else if (p > i) {
            upd(i, p+1, n, -1);
            /* descrease [p,n-1] in real interval and do as above */;
            upd(i, 1, i, -1);
            /* descrease [0,i-1] in real interval and do as above */;
        }
    }

    if(failed || (nas != nins))
    {
        puts("-1");
    } else {
        int before = 0;
        /* do the topsort and output answer */;
        for(int i = 0;i < n;i++)
            if(0 == in[i] && -1 != a[i])
                pq.push(mp(a[i], i));
        while(!pq.empty())
        {
            pii cur = pq.top(); pq.pop();
            int v = cur.fi, u = cur.se;
            asq[nout++] = v;
            for(auto x : g[u])
            {
                in[x]--;
                if(0 == in[x] && -1 != a[x])
                    pq.push(mp(a[x], x));
            }
        }
        if(nout != nins) puts("-1");
        else
        {
            for(int i = 0;i < nout;i++)
                printf("%s%d", i ? " ":"", asq[i]);
            puts("");
        }
    }
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while(T--) proc();
    return 0;
}
