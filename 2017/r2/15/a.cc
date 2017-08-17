/* UESTC 2017 Summer Training #32 Div.2. Problem A, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif
#define MAXN    10000
#define MAXM    10

int n, m;
ll A[MAXN+1];

template <int STMAX = 1000000>
struct segment_tree
{
    struct node_t
    {
        static inline node_t merge(node_t n1, node_t n2)
        {
            node_t ans;
            ans.l = n1.l; ans.r = n2.r;
            for(int i = 0;i < MAXM;++i)
                ans.s[i] = n1.s[i] + n2.s[i];
            return ans;
        }

        /* Data field */
        int l,r;
        ll s[MAXM];
    }nodes[(STMAX+1)<<2];

    inline void maintain_leaf(int o, int idx)
    {
        nodes[o].l = nodes[o].r = idx;
        for(int i = 0;i < MAXM;++i)
            nodes[o].s[i] = 0;
        nodes[o].s[A[idx]%m] = A[idx];
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
    void upd(int L, int R, ll dr, int o, int l, int r)
    {
        if( L <= l && r <= R )
        {
            if(A[l] + dr >= 0)
            {
                A[l] += dr;
                maintain_leaf(o, l);
            }
        } else if (L <= R) {
            int mid = (l+r)>>1;
            if( L <= mid ) upd(L, R, dr, o<<1, l, mid);
            if( R > mid ) upd(L, R, dr, o<<1|1, mid+1, r);
            maintain(o);
        }
    }

    ll qry(int L, int R, int mod, int o, int l, int r)
    {
        if(L <= l && r <= R)
            return nodes[o].s[mod];
        else if (L <= R)
        {
            int mid = (l+r)>>1;
            if(R <= mid) return qry(L,R,mod,o<<1,l,mid);
            if(L > mid) return qry(L,R,mod,o<<1|1,mid+1,r);
            return (qry(L,R,mod,o<<1,l,mid) + qry(L,R,mod,o<<1|1,mid+1,r));
        }
    }

    int N;

    segment_tree(void):N(STMAX){}
    segment_tree(int n):N(n){}
    void build(int n){N = n; build(1,1,N);}
    void update(int L, int R, ll dr) {upd(L,R,dr,1,1,N);}
    ll query(int L, int R, ll mod) {return qry(L,R,mod,1,1,N);}
};


segment_tree<MAXN> st;

int main(void)
{
    int q = 0;
    scanf("%d %d", &n, &m);
    for(int i = 1;i <= n;++i)
        scanf(INT64, A+i);
    st.build(n);
    scanf("%d", &q);
    while(q--)
    {
        char oper[4] = {0};
        scanf("%s", oper);
        if('s' == oper[0])
        {
            int l, r, mod;
            scanf("%d %d %d", &l, &r, &mod);
            printf(INT64 "\n", st.query(l,r,mod));
        } else {
            int p; ll r;
            scanf("%d " INT64, &p, &r);
            if('-' == oper[0]) r = -r;
            st.update(p,p,r);
            printf(INT64 "\n", A[p]);
        }
    }
    return 0;
}
