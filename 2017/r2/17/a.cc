/* Osipovsky Cup 2014 (partially SYSU-Aug-2014 contest). Problem A, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

template <int STMAX = 1000000>
struct segment_tree
{
    struct node_t
    {
        static inline node_t merge(node_t n1, node_t n2)
        {
            node_t ans;
            ans.l = n1.l; ans.r = n2.r;
            ans.s = n1.s + n2.s;
            return ans;
        }

        /* Data field */
        int l,r;
        ll s;
    }nodes[(STMAX+1)<<2];

    struct lazy_t
    {
        int marked; /* Optional */
        ll delta;

        lazy_t(void){clear();}
        lazy_t(ll d):marked(1),delta(d){}
        void clear(void){marked=0;delta=0ll;}
    }marks[(STMAX+1)<<2];

    inline void maintain_leaf(int o, int idx)
    {
        nodes[o].l = nodes[o].r = idx;
        nodes[o].s = 0ll;
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
        ll len = nodes[o].r - nodes[o].l + 1;
        nodes[o].s += (act.delta * len);
        marks[o].delta += act.delta;
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

    /* Do act on all elements in [L,R] */
    void upd(int L, int R, lazy_t act, int o, int l, int r)
    {
        if( L <= l && r <= R )
        {
            mark(act, o);
        } else if (L <= R) {
            int mid = (l+r)>>1;
            pushdown(o);
            if( L <= mid ) upd(L, R, act, o<<1, l, mid);
            if( R > mid ) upd(L, R, act, o<<1|1, mid+1, r);
            maintain(o);
        }
    }

    node_t qry(int L, int R, int o, int l, int r)
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
    }

    int N;

    segment_tree(void):N(STMAX){}
    segment_tree(int n):N(n){}
    void build(int n){N = n; build(1,1,N);}
    void update(int L, int R, lazy_t act) {upd(L,R,act,1,1,N);}
    ll query(int L, int R) {return qry(L,R,1,1,N).s;}
};
#define MAXN    100010
typedef segment_tree<MAXN> segt;
typedef segt::lazy_t lat;

int N;
segt st;

int main(void)
{
    int i = 0;
    int M = 0, K = 0;
    int cnt = 0;
    scanf("%d", &N);
    st.build(N);
    scanf("%d", &M);
    while(M--)
    {
        int Li, Ri, Di;
        scanf("%d%d%d", &Li, &Ri, &Di);
        st.update(Li, Ri, lat(Di));
    }
    scanf("%d", &K);
    while(K--)
    {
        ll Hi; int Xi;
        scanf("%lld %d", &Hi, &Xi);
        ll attack = st.query(Xi, N);
        if(Hi > attack) ++cnt;
    }
    printf("%d\n", cnt);
    return 0;
}
