#include <cassert>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

typedef struct ac_machine
{
    typedef long long int ll;
    static const int MAXN = 100010;
    static const int MOD = 1000000007;
    ll fact[MAXN], fiv[MAXN], inv[MAXN];
    inline void pre(void)
    {
        ll i;
        fact[0] = fact[1] = 1;
        fiv[0] = fiv[1] = 1;
        inv[1] = 1;
        for(i = 2ll;i < MAXN;i++)
        {
            fact[i] = (i * fact[i-1]) % MOD;
            inv[i] = (MOD - MOD/i) * inv[MOD%i] % MOD;
            fiv[i] = (inv[i] * fiv[i-1]) % MOD;
            assert(1 == (inv[i] * i % MOD));
            assert(1 == (fiv[i] * fact[i] % MOD));
        }
    }
    inline ll C(int n, int k)
    {
        ll ret = fact[n];
        ret = (ret * fiv[n-k]) % MOD;
        return (ret * fiv[k]) % MOD;
    }

    struct Q
    {
        static size_t block;
        int id;
        int n, m;
        bool operator<(const Q &o) const
        {
            int nb = m / block, no = o.m / block;
            if(nb == no) return (n < o.n);
            else return nb < no;
        }
    }q[MAXN];
    int T;
    int ans[MAXN];
    ll n, m, current_ans;
    void bruteforce(void)
    {
        int i;
        n = q[0].n; m = -1ll;
        current_ans = 0ll;
        for(i = 0;i < T;i++)
        {
            const Q &qi = q[i];
            /* 先扩大区间，再减小区间 */
            while(n < qi.n)
            {
                current_ans = (2ll * current_ans) % MOD;
                current_ans = (current_ans - C(n,m) + MOD) % MOD;
                n++;
            }
            while(m > qi.m)
            {
                current_ans = (current_ans - C(n,m) + MOD) % MOD;
                m--;
            }
            while(n > qi.n)
            {
                n--;
                current_ans = (current_ans + C(n,m)) % MOD;
                current_ans = (current_ans * inv[2]) % MOD;
            }
            while(m < qi.m)
            {
                m++;
                current_ans = (current_ans + C(n,m)) % MOD;
            }
            ans[qi.id] = current_ans;
        }
    }
    int wa(void)
    {
        int i;
        int n, m;
        pre();
        scanf("%d", &T);
        Q::block = (int)sqrt(T);
        for(i = 0;i < T;i++)
        {
            q[i].id = i;
            scanf("%d%d", &q[i].n, &q[i].m);
        }
        sort(q, q+T);
        bruteforce();
        for(i = 0;i < T;i++)
            printf("%d\n", ans[i]);
        return 0;
    }
}am;

size_t am::Q::block;

int main(void)
{
    return (new am())->wa();
}
