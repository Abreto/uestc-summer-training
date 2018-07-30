#include <cstdio>
#include <queue>

using namespace std;

#define MAXN    (2000000)
#define MAXQ    (1000000)

int cnt[(MAXN+2)<<2];
void inc(int p, int o = 1, int l = 1, int r = MAXN)
{
    if(p < l || r < p) return;
    if(p == l && r == p) {
        cnt[o] += 1;
    } else {
        int mid = (l+r)>>1;
        if(p <= mid) inc(p, o<<1, l, mid);
        else if(mid < p) inc(p, o<<1|1, mid+1, r);
        cnt[o] = cnt[o<<1] + cnt[o<<1|1];
    }
}
int qry(int L, int R, int o = 1, int l = 1, int r = MAXN)
{
    if(R < l || r < L) return 0;
    if(L <= l && r <= R) {
        return cnt[o];
    } else {
        int mid = (l+r)>>1;
        return qry(L, R, o<<1, l, mid) + qry(L, R, o<<1|1, mid+1, r);
    }
}

struct event
{
    int type;   /* 0 for left bound, 1 for right bound, 2 for point */
    int occur;
    int L, R;
    int *ans;
    int *rcd;
    event(int t, int o, int l, int r = 0, int *a = NULL, int *c = NULL)
    {
        type = t;
        occur = o;
        L = l;
        R = r;
        ans = a;
        rcd = c;
    }
    bool operator<(const event &e) const
    {
        if(occur != e.occur) return (occur > e.occur);
        else return (type < e.type);
    }
};

int R, Q;
priority_queue<event> q;
int record[MAXQ+10];
int ans[MAXQ+10];

int main(void)
{
    int i;
    int x, y, d;
    scanf("%d", &R);
    for(i = 0;i < R;i++)
    {
        scanf("%d%d", &x, &y);
        q.push(event(2, x-y, x+y));
    }
    scanf("%d", &Q);
    for(i = 0;i < Q;i++)
    {
        scanf("%d%d%d", &x, &y, &d);
        q.push(
            event(0,
            x-y-d-1, x+y-d, x+y+d,
            ans+i, record+i)
        );
        q.push(
            event(1,
            x-y+d, x+y-d, x+y+d,
            ans+i, record+i)
        );
    }
    while(!q.empty())
    {
        event e = q.top(); q.pop();
        if(2 == e.type)
        {
            inc(e.L);
        } else if(0 == e.type) {
            int before = qry(e.L, e.R);
            *(e.rcd) = before;
        } else {
            int now = qry(e.L, e.R);
            *(e.ans) = now - *(e.rcd);
        }
    }
    for(i = 0;i < Q;i++) printf("%d\n", ans[i]);
    return 0;
}
