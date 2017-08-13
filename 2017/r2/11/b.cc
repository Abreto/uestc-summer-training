/* UESTC 2017 Summer Training #28 Div.2. Problem B, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
#define MAXN    100000
#define MAXX    1000000
#define INF 1048576

int N, C;

template <int STMAX = 1000000>
struct segment_tree
{
    struct lazy_t
    {
        int marked; /* Optional */
        int x,y;

        lazy_t(void){clear();}
        lazy_t(int nx, int ny):marked(1),x(nx),y(ny){}
        void clear(void){marked=0;x=-1;y=INF;}
    }marks[(STMAX+1)<<2];

    inline void maintain_leaf(int o, int idx)
    {
        marks[o] = lazy_t(-1,INF);
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
            pushup(o);
        }
    }

    /* Modify all elements in [l,r] */
    void mark(lazy_t act, int o)
    {
        marks[o].x = act.x;
        marks[o].y = act.y;
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

    void pushup(int o)
    {
        if(1 == marks[o<<1].marked && 1 == marks[o<<1|1].marked)
            if((marks[o<<1].x == marks[o<<1|1].x)&&(marks[o<<1].y == marks[o<<1|1].y))
            {
                marks[o].x = marks[o<<1].x;
                marks[o].y = marks[o<<1].y;
                marks[o].marked = 1;
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
            pushup(o);
        }
    }

    lazy_t qry(int pos, int o, int l, int r)
    {
        if(l <= pos && pos <= r && 1 == marks[o].marked)
            return marks[o];
        else
        {
            int mid = (l+r)>>1;
            pushdown(o);
            if(pos <= mid) return qry(pos,o<<1,l,mid);
            if(pos > mid) return qry(pos,o<<1|1,mid+1,r);
        }
    }

    int N;

    segment_tree(void):N(STMAX){}
    segment_tree(int n):N(n){}
    void build(int n){N = n+1; build(1,1,N);}
    void update(int L, int R, lazy_t act) {upd(L+1,R+1,act,1,1,N);}
    lazy_t query(int pos) {return qry(pos+1,1,1,N);}
};
typedef segment_tree<MAXX> segtree;

template <typename T>
struct point
{
    T x,y;
    point(void):x(T()),y(T()){}
    point(T xx, T yy):x(xx),y(yy){}
    inline point operator-(const point& b) const {return point(x-b.x,y-b.y);}
    inline T operator^(const point& b) const {return ((x)*(b.y))-((b.x)*(y));} /* outter product */
};
typedef long long int ll;
typedef point<ll> Point;

struct seg
{
    Point p1, p2;
    seg(void){}
    seg(Point P1, Point P2)
    {
        if(P1.x < P2.x)
        {
            p1 = P1;
            p2 = P2;
        } else {
            p1 = P2;
            p2 = P1;
        }
    }
    inline bool operator<(const seg& b) const
    {
        if(p2.x <= b.p1.x) return min(p1.y,p2.y)<min(b.p1.y,b.p2.y);
        else if (p1.x >= b.p2.x) return min(p1.y,p2.y)<min(b.p1.y,b.p2.y);
        else
        {
            if(p1.x < b.p1.x && b.p1.x < p2.x)
            {
                ll t = (p1-b.p1)^(p2-b.p1);
                return (t > 0);
            } else if (p1.x < b.p2.x && b.p2.x < p2.x) {
                ll t = (p1-b.p2)^(p2-b.p2);
                return (t > 0);
            } else {
                ll t = (b.p1-p1)^(b.p2-p1);
                return (t < 0);
            }
        }
    }
};

segtree st;
seg segs[MAXN];

int main(void)
{
    int i = 0;
    scanf("%d %d", &N, &C);
    for(i = 0;i < N;++i)
    {
        int X1, Y1, X2, Y2;
        scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
        segs[i] = seg(Point(X1,Y1),Point(X2,Y2));
    }
    sort(segs, segs+N);
    st.build(MAXX);
    for(i = N;i > 0;--i)
    {
        auto cur = segs[i-1];
        Point le = cur.p1, ri = cur.p2;
        segtree::lazy_t todup;
        if(le.y == ri.y)
        {
            todup = segtree::lazy_t(-1,le.y);
        } else if (le.y > ri.y) {
            todup = st.query(le.x);
            if(-1 == todup.x) todup.x = le.x;
        } else {
            todup = st.query(ri.x);
            if(-1 == todup.x) todup.x = ri.x;
        }
        st.update(le.x, ri.x, todup);
    }
    while(C--)
    {
        int X;
        scanf("%d", &X);
        segtree::lazy_t ans = st.query(X);
        int sx = 0;
        if(-1 == ans.x) sx = X;
        else sx = ans.x;
        printf("%d", sx);
        if(ans.y <= MAXX)
            printf(" %d", ans.y);
        puts("");
    }
    return 0;
}
