/* UESTC 2017 Summer Training #34 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

#define MAXN    100001

int n;
int a[MAXN<<2];

template <int STMAX = 1000000>
struct segment_tree
{
    struct node_t
    {
        static inline node_t merge(node_t n1, node_t n2)
        {
            node_t ans;
            ans.l = n1.l; ans.r = n2.r;
            ans.m = min(n1.m, n2.m);
            return ans;
        }

        /* Data field */
        int l,r;
        int m;
    }nodes[(STMAX+1)<<2];

    inline void maintain_leaf(int o, int idx)
    {
        nodes[o].l = nodes[o].r = idx;
        nodes[o].m = a[idx];
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

    /* dir: 0 means to right, 1 means to left. */
    int qry(int L, int R, int ub, int dir, int o, int l, int r)
    {
        if(L <= l && r <= R)
        {
            if(l == r)
            {
                if(nodes[o].m < ub) return l;
                else return -1;
            } else {
                int mid = (l+r)>>1;
                int closer = (o<<1|1)^dir, farther = (o<<1)^dir;
                int cl, cr, fl, fr;
                if(0 == dir)
                {
                    cl = mid+1; cr = r;
                    fl = l; fr = mid;
                } else {
                    cl = l; cr = mid;
                    fl = mid+1; fr = r;
                }
                if(nodes[closer].m >= ub) return qry(L,R,ub,dir,farther,fl,fr);
                else return qry(L,R,ub,dir,closer,cl,cr);
            }
        }
        else if (L <= R)
        {
            int mid = (l+r)>>1;
            int closer = (o<<1|1)^dir, farther = (o<<1)^dir;
            int cl, cr, fl, fr;
            if(0 == dir)
            {
                cl = mid+1; cr = r;
                fl = l; fr = mid;
            } else {
                cl = l; cr = mid;
                fl = mid+1; fr = r;
            }
            if(R <= mid) return qry(L,R,ub,dir,o<<1,l,mid);
            if(L > mid) return qry(L,R,ub,dir,o<<1|1,mid+1,r);
            int cq = qry(L,R,ub,dir,closer,cl,cr);
            if(cq > 0)  return cq;
            else return qry(L,R,ub,dir,farther,fl,fr);
        }
    }

    int N;

    segment_tree(void):N(STMAX){}
    segment_tree(int n):N(n){}
    void build(int n){N = n; build(1,1,N);}
    int query(int L, int R, int ub, int dir) {return qry(L,R,ub,dir,1,1,N);}
};

segment_tree<MAXN*3> st;

int main(void)
{
    int i = 0, j = 0;
    int min_length = 0x7fffffff;
    int ansi, ansj, ansk;
    scanf("%d", &n);
    for(i = 1;i <= n;++i)
        scanf("%d", a+i);
    for(j = 1;j < 3;++j)
        for(i = 1;i <= n;++i)
            a[j*n+i] = a[i];
    st.build(3*n);
    for(i = n+1;i <= 2*n;++i)
    {
        int lq = st.query(i-n+1, i-1, a[i], 0);
        int rq = st.query(i+1, i+n-1, a[i], 1);
        if(lq > 0 && rq > 0)
        {
            int new_length = rq - lq;
            if(new_length < min_length)
            {
                ansj = (i-1)%n+1;
                ansi = (lq-1)%n+1;
                ansk = (rq-1)%n+1;
                min_length = new_length;
            }
        }
    }
    printf("%d %d %d\n", ansi, ansj, ansk);
    return 0;
}
