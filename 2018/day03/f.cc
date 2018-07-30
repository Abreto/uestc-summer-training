#include <cstdio>

using namespace std;

#define MAXN    (2000000)
#define MAXQ    (1000000)

int cnt[(MAXN+2)<<2];
int lazy[(MAXN+2)<<2];
void pushdown(int o)
{
    if(lazy[o])
    {
        cnt[o<<1] += lazy[o];
        cnt[o<<1|1] += lazy[o];
        lazy[o<<1] += lazy[o];
        lazy[o<<1|1] += lazy[o];
        lazy[o] = 0;
    }
}
void upd(int L, int R, int v, int o = 1, int l = 1, int r = MAXN)
{
    if(L > R) return;
    if(R < l || r < L) return;
    if(L <= l && r <= R) {
        cnt[o] += v;
        lazy[o] += v;
    } else {
        int mid = l+r>>1;
        pushdown(o);
        if(L <= mid) upd(L, R, v, o<<1, l, mid);
        if(mid < R) upd(L, R, v, o<<1|1, mid+1, r);
    }
}
int qry(int p, int o = 1, int l = 1, int r = MAXN)
{
    if(p < l || p > r) return 0;
    if(p == l && r == p) {
        return cnt[o];
    } else {
        int mid = l+r>>1;
        pushdown(o);
        if(p <= mid) return qry(p, o<<1, l, mid);
        else return qry(p, o<<1|1, mid+1, r);
    }
}

struct event
{
    int type;
    int id;
};


int ans[MAXQ+10];

int main(void)
{
    return 0;
}
