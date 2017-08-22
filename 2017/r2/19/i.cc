/* UESTC 2017 Summer Training #33 Div.2. Problem I, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

template <int STMAX = 1000000>
struct segment_tree
{
    struct node_t
    {
        static inline node_t merge(node_t n1, node_t n2)
        {
            node_t ans;
            ans.l = n1.l; ans.r = n2.r;
            /* merge n1 and n2 to ans. */
            return ans;
        }

        /* Data field */
        int l,r;
    }nodes[(STMAX+1)<<2];

    struct lazy_t
    {
        int marked; /* Optional */
        int states;
        int cities;

        lazy_t(void){clear();}
        lazy_t(int s, int c):marked(1),states(s),cities(c){}
        void clear(void){marked=states=cities=0;}
    }marks[(STMAX+1)<<2];

    inline void maintain_leaf(int o, int idx)
    {
        nodes[o].l = nodes[o].r = idx;
        marks[o] = lazy_t(0,0);
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
            marks[o].clear();
        }
    }

    /* Modify all elements in [l,r] */
    void mark(lazy_t act, int o)
    {
        marks[o].states += act.states;
        marks[o].cities += act.cities;
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
        }
    }

    lazy_t qry(int L, int R, int o, int l, int r)
    {
        if(L <= l && r <= R)
            return marks[o];
        else if (L <= R)
        {
            int mid = (l+r)>>1;
            pushdown(o);
            if(R <= mid) return qry(L,R,o<<1,l,mid);
            if(L > mid) return qry(L,R,o<<1|1,mid+1,r);
        }
    }

    int N;

    segment_tree(void):N(STMAX){}
    segment_tree(int n):N(n){}
    void build(int n){N = n+1; build(1,1,N);}
    void update(int L, int R, lazy_t act) {upd(L+1,R+1,act,1,1,N);}
    lazy_t query(int pos) {return qry(pos+1,pos+1,1,1,N);}
    void print(void)
    {
        for(int i = 1;i <= N*4;++i)
            printf("(%d,%d):%d,%d\n", nodes[i].l, nodes[i].r, marks[i].states, marks[i].cities);
    }
};

#define MAXN    (100000)
#define MAXY    (1000000)
#define MAXSEGNOT   (MAXY+1)

typedef segment_tree<MAXSEGNOT> segt;
typedef segt::lazy_t lzy_t;

int n;
segt st;
int ys[MAXN];
int miny[MAXN], maxy[MAXN];
int tot_maxy;
namespace disjoint
{
    int size[MAXN];
    int par[MAXN];
    void init(void)
    {
        for(int i = 0;i < n;++i)
        {
            par[i] = i;
            size[i] = 1;
        }
    }
    int fdr(int i)
    {
        return (par[i] == i) ? i : (par[i] = fdr(par[i]));
    }
    int uni(int i, int j)
    {
        int fi = fdr(i), fj = fdr(j);
        if(fi == fj) return fj;
        par[fi] = fj;
        size[fj] += size[fi];
        return fj;
    }
}

void clear(void)
{
    tot_maxy = 0;
    disjoint::init();
}

void proc(void)
{
    int i = 0;
    int m = 0;
    for(i = 0;i < n;++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        ys[i] = miny[i] = maxy[i] = y;
        if(y > tot_maxy) tot_maxy = y;
    }
    st.build(tot_maxy);
    scanf("%d", &m);
    while(m--)
    {
        char com[8];
        scanf("%s", com);
        if('r' == com[0])
        {
            int A, B;
            scanf("%d%d", &A, &B);
            int fA = disjoint::fdr(A), fB = disjoint::fdr(B);
            if(fA != fB)
            {
                st.update(miny[fA], maxy[fA]-1, lzy_t(-1,-disjoint::size[fA]));
                st.update(miny[fB], maxy[fB]-1, lzy_t(-1,-disjoint::size[fB]));
                int nf = disjoint::uni(fA, fB);
                maxy[nf] = max(maxy[nf], max(maxy[fA],maxy[fB]));
                miny[nf] = min(miny[nf], min(miny[fB],miny[fA]));
                st.update(miny[nf], maxy[nf]-1, lzy_t(1, disjoint::size[nf]));
            }
        } else if ('l' == com[0]) {
            double dC;
            scanf("%lf", &dC);
            int C = (int)(dC);
            lzy_t q = st.query(C);
            printf("%d %d\n", q.states, q.cities);
        } else *((int*)NULL)=0;
        /*st.print();*/
    }
}

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        clear();
        proc();
    }
    return 0;
}
