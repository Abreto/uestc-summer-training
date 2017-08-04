/* UESTC 2017 Summer Training Round2 #03 Div.2. Problem B, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

#define MAXN    100000
#define MAXSQ   317
#define MAXQ    1000000

#define BLOCKID(pos)    ( ((pos)-1)/blocklen )
#define BLOCKL(id)      ( (id)*blocklen+1 )
#define BLOCKR(id)      ( ((id)+1)*blocklen )

int blocklen;
int nblocks;

struct query_t
{
    int l, r, a, b;
    int *ans;
    query_t(){}
    query_t(int ll, int rr, int aa, int bb, int *an):l(ll),r(rr),a(aa),b(bb),ans(an){}
    bool operator<(const query_t &o) const
    {
        return (BLOCKID(l)==BLOCKID(o.l))?((BLOCKID(l)&1)?(r<o.r):(r>o.r)):(BLOCKID(l)<BLOCKID(o.l));
    }
}Q[MAXQ];

int n, m;
int s[MAXN+1];
int ans[MAXQ];

namespace ds
{
    int app[MAXN+1];
    int totapp[MAXSQ];
    void upd(int pos, int delta)
    {
        int bid = BLOCKID(pos);
        totapp[bid] += delta;
        app[pos] += delta;
    }
    int qry(int pos)
    {
        int i = 0;
        int bid = BLOCKID(pos), ret = 0;
        if(0 == pos) return 0;
        for(i = 0;i < bid;++i) ret += totapp[i];
        for(i = BLOCKL(bid);i <= pos;++i) ret += app[i];
        return ret;
    }
    int query(int l, int r)
    {
        return qry(r)-qry(l-1);
    }
}

void init(void)
{
    blocklen = ceil(sqrt(n));
    nblocks = (n-1)/blocklen+1;
    /*memset(ds::app, 0, sizeof(ds::app));
    memset(ds::totapp, 0, sizeof(ds::totapp));*/
}

int app[MAXN+1];
void extend(int pos, int d)
{
    int x = s[pos];
    if(1 == d) {
        if(1 == ++app[x]) ds::upd(x,d);
    } else {
        if(0 == --app[x]) ds::upd(x,d);
    }
}

void mosover(void)
{
    int i = 0;
    int l = 1, r = 0;
    sort(Q, Q+m);
    for(i = 0;i < m;++i)
    {
        query_t &q = Q[i];
        while(r < q.r) extend(++r, +1);
        while(r > q.r) extend(r--, -1);
        while(l > q.l) extend(--l, +1);
        while(l < q.l) extend(l++, -1);
        *(q.ans) = ds::query(q.a, q.b);
    }
}

int main(void)
{
    int i;
    scanf("%d %d", &n, &m);
    for(i = 1;i <= n;++i)
        scanf("%d", s+i);
    for(i = 0;i < m;++i)
    {
        int L, R, a, b;
        scanf("%d%d%d%d", &L, &R, &a, &b);
        Q[i] = query_t(L,R,a,b,ans+i);
    }
    init();
    mosover();
    for(i = 0;i < m;++i) printf("%d\n", ans[i]);
    return 0;
}
