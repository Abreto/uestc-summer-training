/* Petrozavodsk Summer Training Camp 2016. Problem J, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long int ll;

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#define MAXN    500000

int n, m;
ll a[MAXN+1];
ll sum[MAXN+1];

template <int STMAX = 1000000>
struct segment_tree
{
    struct node_t
    {
        static inline node_t merge(node_t &n1, node_t &n2)
        {
            node_t ans;
            ans.l = n1.l; ans.r = n2.r;
            ans.rem = n1.rem + n2.rem;
            if(n1.minh < n2.minh)
            {
                ans.minh = n1.minh;
                ans.minhd = n1.minhd;
            } else {
                ans.minh = n2.minh;
                ans.minhd = n2.minhd;
            }
            n1.rem = n2.rem = 0;
            return ans;
        }

        /* Data field */
        int l,r;
        ll rem;
        ll minh, minhd;
    }nodes[(STMAX+1)<<2];

    struct lazy_t
    {
        int marked; /* Optional */
        ll di, bi;

        lazy_t(void){clear();}
        lazy_t(ll d, ll b):marked(1),di(d),bi(b){}
        void clear(void){marked=0;di=0;bi=0;}
    }marks[(STMAX+1)<<2];

    inline void maintain_leaf(int o, int idx)
    {
        nodes[o].l = nodes[o].r = idx;
        nodes[o].rem = 0;
        nodes[o].minh = 0;
    }
    inline void maintain(int o)
    {
        nodes[o] = node_t::merge(nodes[o<<1], nodes[o<<1|1]);
    }

    /* Usage: build(1,1,n); */
    void build(int o, int l, int r) /* [l,r] */
    {
        if( r <= l )
        {
            maintain_leaf(o, l);
        } else {
            int mid = l+r>>1;
            build(o<<1, l, mid);
            build(o<<1|1, mid+1, r);
            maintain(o);
        }
    }

    /* Modify all elements in [l,r] */
    void mark(lazy_t act, int o)
    {
        /* do something .. */
        marks[o].marked = 1;
    }

    /* Pass cached updates. */
    void pushdown(int o)
    {
        if( marks[o].marked )
        {
            mark(marks[o], o<<1);
            mark(marks[o], o<<1|1);
            marks[o].clear();
        }
    }

    /* if all child are flat. */
    void pushup(int o)
    {
        int lc = o<<1, rc = o<<1|1;
        if( marks[lc].marked && marks[rc].marked )
            if( marks[lc].di == marks[rc].di && marks[lc].bi == marks[rc].bi )
            {
                marks[o].di = marks[lc].di;
                marks[o].bi = marks[lc].bi;
                marks[o].marked = 1;
            }
    }

    /* Do act on all elements in [L,R] */
    void upd(lazy_t act, int o, int l, int r)
    {
        if( marks[o].marked || l == r )
        {
            ll growth = act.di - marks[o].di;
            if( marks[o].bi + growth * a[l] >= act.bi )
            {
                ll t1 = marks[o].bi * (r - l + 1);
                ll t2 = growth * (sum[r] - sum[l-1]);
                nodes[o].rem = t1 + t2 - act.bi * (r - l + 1);
                nodes[o].minh = act.bi;
                nodes[o].minhd = act.di;
                marks[o].di = act.di;
                marks[o].bi = act.bi;
                return;
            }
        }
        ll growth = act.di - nodes[o].minhd;
        if( nodes[o].minh + growth * a[l] >= act.bi )
        {
            ll t1 = nodes[o].rem;
            ll t2 = growth * (sum[r] - sum[l-1]);
            nodes[o].rem = t1 + t2 - act.bi * (r - l + 1);
            nodes[o].minh = act.bi;
            nodes[o].minhd = act.di;
            marks[o].di = act.di;
            marks[o].bi = act.bi;
            return;
        }
        if (l < r) {
            int mid = (l+r)>>1;
            upd(act, o<<1, l, mid);
            upd(act, o<<1|1, mid+1, r);
            pushup(o);
            maintain(o);
        }
    }

    /*node_t qry(int o, int l, int r)
    {
        if(L <= l && r <= R)
            return nodes[o];
        else if (L <= R)
        {
            int mid = (l+r)>>1;
            pushdown(o);
            if(R <= mid) return qry(L,R,o<<1,l,mid);
            if(L > mid) return qry(L,R,o<<1|1,mid+1,r);
            return node_t::merge(qry(L,R,o<<1,l,mid),qry(L,R,o<<1|1,mid+1,r));
        }
    }*/

    int N;

    segment_tree(void):N(STMAX){}
    segment_tree(int n):N(n){}
    void build(int n){N = n; build(1,1,N);}
    /*void update(lazy_t act) {upd(act,1,1,N);}*/
    /*node_t query(void) {return qry(1,1,N);}*/
    ll q(ll d, ll b)
    {
        upd(lazy_t(d,b), 1, 1, N);
        return nodes[1].rem;
    }
};

typedef segment_tree<MAXN> st;
st H;

int main(void)
{
    int i = 0;
    scanf("%d %d", &n, &m);
    for(i = 1;i <= n;++i)
        scanf(INT64, a+i);
    sort(a+1, a+n+1);
    for(i = 1;i <= n;++i)
        sum[i] = sum[i-1] + a[i];
    H.build(n);
    while(m--)
    {
        ll di = 0, bi = 0;
        scanf(INT64 INT64, &di, &bi);
        printf(INT64 "\n", H.q(di, bi));
    }
    return 0;
}
