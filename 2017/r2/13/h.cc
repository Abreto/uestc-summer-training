/* UESTC 2017 Summer Training #30 Div.2. Problem H, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif
typedef long long int ll;

#define MAXK    200010

ll n;
int k;
int nrs;
ll rs[MAXK];
unordered_map<ll,int> r2id; /* 0-based */
pair<ll,ll> artists[MAXK];  /* (bi,ai) */

void descrete_r(void)
{
    sort(rs, rs+k);
    nrs = unique(rs, rs+k)-rs;
    for(int i = 0;i < nrs;i++)
        r2id[rs[i]] = i;
}

template <int STMAX = 200010>
struct segment_tree
{
    struct node_t
    {
        static inline node_t merge(node_t n1, node_t n2)
        {
            node_t ans;
            ans.l = n1.l; ans.r = n2.r;
            ans.mv = max(n1.mv, n2.mv);
            return ans;
        }

        /* Data field */
        int l,r;
        ll mv;
    }nodes[(STMAX+1)<<2];

    inline void maintain_leaf(int o, int idx)
    {
        nodes[o].l = nodes[o].r = idx;
        nodes[o].mv = 0ll;
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

    /* Do act on all elements in [L,R] */
    void upd(int pos, ll nv, int o, int l, int r)
    {
        if( pos <= l && r <= pos )
        {
            nodes[o].mv = max(nodes[o].mv, nv);
        } else {
            int mid = (l+r)>>1;
            if( pos <= mid ) upd(pos, nv, o<<1, l, mid);
            if( pos > mid ) upd(pos, nv, o<<1|1, mid+1, r);
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
            if(R <= mid) return qry(L,R,o<<1,l,mid);
            if(L > mid) return qry(L,R,o<<1|1,mid+1,r);
            return node_t::merge(qry(L,R,o<<1,l,mid),qry(L,R,o<<1|1,mid+1,r));
        }
    }

    int N;

    segment_tree(void):N(STMAX){}
    segment_tree(int n):N(n){}
    void build(int n){N = n; build(1,1,N);}
    void update(int pos, ll nv) {upd(pos+1, nv, 1,1,N);}    /* pos and L/R is 0-base */
    node_t query(int L, int R) {return qry(L+1,R+1, 1,1,N);}
};

typedef segment_tree<MAXK+1> segtree;
segtree st;

int main(void)
{
    int i = 0;
    scanf(INT64 "%d", &n, &k);
    for(i = 0;i < k;++i)
    {
        scanf(INT64 INT64, &(artists[i].second), &(artists[i].first));
        rs[i] = artists[i].first;
    }
    descrete_r();
    st.build(nrs);
    sort(artists, artists+k);
    for(i = 0;i < k;++i)
    {
        ll ai = artists[i].second, bi = artists[i].first;
        ll *prm = lower_bound(rs, rs+nrs, ai);
        ll mv = 0;
        if(prm == rs)
        {
            mv = 0;
        } else {
            prm--;
            mv = st.query(0, prm-rs).mv;
        }
        st.update(r2id[bi], mv+bi-ai+1);
    }
    printf("%lld\n", n - st.query(0,nrs-1).mv);
    return 0;
}
