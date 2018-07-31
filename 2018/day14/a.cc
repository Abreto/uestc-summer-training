#include <cassert>
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;
typedef long long int ll;



struct ac_machine
{
    static const int MAXN = 400040;
    static int n;
    static int t[MAXN], x[MAXN], y[MAXN];
    static inline bool in_circle(int tar, int shot)
    {
        ll dx = x[tar] - x[shot];
        ll dy = y[tar] - y[shot];
        ll r = y[tar];
        return (dx*dx + dy*dy) < (r*r);
    }
    struct pii
    {
        int q, id;
        pii(void){}
        pii(int qq, int ii):q(qq),id(ii){}
        bool operator<(const pii &o) const
        {
            /* if one is qry */
            if( (q) && (!o.q) && in_circle(o.id, id) ) return 1;
            if( (!q) && (o.q) && in_circle(id, o.id) ) return 0;
            return (y[id] == y[o.id]) ? (id < o.id) : (y[id] < y[o.id]);
        }
    };

    static int nxs, xs[MAXN];
    void discreate(void)
    {
        sort(xs, xs+nxs);
        nxs = unique(xs, xs+nxs) - xs;
    }
    int idx(int x)
    {
        return lower_bound(xs, xs+nxs, x) - xs + 1;    // to satisify segment tree idx
    }

    set<pii> seg[MAXN<<2];
    void build(int o = 1, int l = 1, int r = nxs)
    {
        seg[o].clear();
        if(l < r)
        {
            int mid = (l+r)>>1;
            build(o<<1, l, mid);
            build(o<<1|1, mid+1, r);
        }
    }
    void upd(int L, int R, int id, int t, int o = 1, int l = 1, int r = nxs)
    {
        if(R < L) return;
        if(R < l || r < L) return;
        if(L <= l && r <= R)
        {
            if(1 == t)
                seg[o].insert(pii(0,id));
            else
                seg[o].erase(pii(0,id));
        } else {
            int mid = (l+r)>>1;
            if(L <= mid) upd(L, R, id, t, o<<1, l, mid);
            if(R > mid) upd(L, R, id, t, o<<1|1, mid+1, r);
        }
    }
    int qry(int p, int id, int o = 1, int l = 1, int r = nxs)
    {
        if(p < l || r < p) return 0;
        auto it = seg[o].lower_bound(pii(1,id));
        if(it != seg[o].end())
        {
            if ( in_circle(it->id, id) ) return it->id;
        }
        if(l < r)
        {
            int mid = (l+r)>>1;
            if(p <= mid) return qry(p, id, o<<1, l, mid);
            return qry(p, id, o<<1|1, mid+1, r);
        }
        return 0;
    }

    void scan(void)
    {
        int i;
        scanf("%d", &n);
        for(i = 1;i <= n;i++)
        {
            scanf("%d%d%d", t+i, x+i, y+i);
            if(1 == t[i])
            {
                xs[nxs++] = x[i] - y[i];
                xs[nxs++] = x[i] + y[i];
            } else {
                assert(2 == t[i]);
                xs[nxs++] = x[i];
            }
        }
        discreate();
    }
    int ac(void)
    {
        build();
        for(int i = 1;i <= n;i++)
        {
            if(1 == t[i])
            {
                int L = idx(x[i]-y[i]);
                int R = idx(x[i]+y[i]);
                upd(L+1, R-1, i, 1);
            } else {
                int p = idx(x[i]);
                int tar = qry(p, i);
                if (0 == tar)
                {
                    puts("-1");
                } else {
                    printf("%d\n", tar);
                    int L = idx(x[tar]-y[tar]);
                    int R = idx(x[tar]+y[tar]);
                    upd(L+1, R-1, tar, -1);
                }
            }
        }
        return 0;
    }
};

int ac_machine::n = 0;
int ac_machine::t[MAXN] = {0}, ac_machine::x[MAXN] = {0}, ac_machine::y[MAXN] = {0};
int ac_machine::nxs = 0, ac_machine::xs[MAXN] = {0};

int main(void)
{
    ac_machine *app = new ac_machine();
    app->scan();
    return app->ac();
}
