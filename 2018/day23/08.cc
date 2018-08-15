#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long int ll;

const int maxn = 128128;

struct persistent
{
    static const int maxnodes = (maxn * 64);
    int n;
    ll raw[maxn];
    struct node_t
    {
        node_t *l, *r;
        int cnt;
        ll sum;
        node_t(void) : l(NULL), r(NULL), cnt(0), sum(0ll) { }
        void maintain(void)
        {
            assert(l && r);
            cnt = l->cnt + r->cnt;
            sum = l->sum + r->sum;
        }
    }nodes[maxnodes];
    int tot;
    node_t *newnode(void) { return (nodes + (tot++)); }
    persistent(void) : tot(0) { }
    node_t *roots[maxn];
    node_t *build(int l, int r)
    {
        node_t *ret = newnode();
        if (l < r)
        {
            int mid = (l + r) >> 1;
            ret->l = build(l, mid);
            ret->r = build(mid+1, r);
        }
        return ret;
    }
    node_t *insert(const node_t *prev, int pos, int l, int r)
    {
        node_t *ret = newnode();
        (*ret) = (*prev);
        if (l == pos && pos == r)
        {
            ret->cnt++;
            ret->sum += raw[pos];
        } else {
            int mid = (l + r) >> 1;
            if (pos <= mid) ret->l = insert(prev->l, pos, l, mid);
            else ret->r = insert(prev->r, pos, mid+1, r);
            ret->maintain();
        }
        return ret;
    }
    ll ksum(const node_t *head, const node_t *tail, int k, int l, int r)
    {
        if (l == r) return raw[l] * k;
        ll s = (tail->sum) - (head->sum);
        int total = (tail->cnt) - (head->cnt);
        if (k == total) return s;
        int mid = (l + r) >> 1;
        int rank = (tail->l->cnt) - (head->l->cnt);
        ll ls = ksum(head->l, tail->l, min(k, rank), l, mid);
        if (k <= rank) return ls;
        return ls + ksum(head->r, tail->r, k - rank, mid+1, r);
    }
}segtree;

class ac_machine
{
    int N;
    int a[maxn], d[maxn];
    ll asum[maxn];
    int id(int x)
    {
        return lower_bound(segtree.raw + 1, segtree.raw + segtree.n + 1, x) - segtree.raw;
    }
public:
    int wa(void)
    {
        int i;
        scanf("%d", &N);
        for (i = 1;i <= N;i++) { scanf("%d", a+i); asum[i] = asum[i-1] + a[i]; }
        for (i = 1;i <= N;i++) scanf("%d", d+i);
        for (i = 1;i <= N;i++) segtree.raw[i] = d[i] - a[i];
        sort(segtree.raw + 1, segtree.raw + N + 1);
        segtree.n = unique(segtree.raw + 1, segtree.raw + N + 1) - segtree.raw - 1;
        segtree.roots[0] = segtree.build(1, segtree.n);
        for (i = 1;i <= N;i++) segtree.roots[i] = segtree.insert(segtree.roots[i-1], id(d[i]-a[i]), 1, segtree.n);
        scanf("%d", &i);
        while (i--)
        {
            int lj, rj;
            scanf("%d%d", &lj, &rj);
            int len = rj - lj + 1;
            int k = len / 3;
            ll dbscore = 2ll * (asum[rj] - asum[lj-1]);
            ll tots = segtree.ksum(segtree.roots[lj-1], segtree.roots[rj], len, 1, segtree.n);
            ll ks = segtree.ksum(segtree.roots[lj-1], segtree.roots[rj], k, 1, segtree.n);
            ll k2s = segtree.ksum(segtree.roots[lj-1], segtree.roots[rj], k<<1, 1, segtree.n);
            // printf("%d,%d,%d: %lld,%lld,%lld\n", lj, rj, k, tots, ks, k2s);
            ll ans = dbscore + 2ll * (tots - k2s) + (k2s - ks);
            // long double da = ans;
            printf("%lld.%lld\n", ans / 2, (ans & 1) * 5);
        }
        return 0;
    }
};

int main(void)
{
    return (new ac_machine())->wa();
}
