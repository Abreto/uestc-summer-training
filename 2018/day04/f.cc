#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long int ll;

#define mod (1000000007)
#define MAXN    (1<<10)

int n, nu;
ll a[MAXN];
ll u[MAXN];
ll m[MAXN];
ll prod[MAXN];
ll C[MAXN][MAXN];

void myinit(void)
{
    int i, j;
    C[0][0] = 1;
    for(i = 1;i < MAXN;i++)
    {
        C[i][0] = C[i][i] = 1;
        for(j = 1;j < i;j++)
        {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
        }
    }
}

ll qow(ll a, ll p)
{
    ll ret = 1;
    while(p)
    {
        if(1 & p) ret = (ret * a) % mod;
        a = (a * a) % mod;
        p >>= 1;
    }
    return ret;
}

ll nmax[MAXN];
ll additional(ll top)
{
    int i, j;
    ll sigma = ((top + 1) * top / 2ll) % mod;
    ll ret = 0;
    for(i = n;i > 0;i--)
    {
        nmax[i] = (qow(top, n-i) * sigma) % mod;
        for(j = i+1;j <= n;j++)
            nmax[i] = (nmax[i] - nmax[j] + mod) % mod;
        nmax[i] = (nmax[i] * C[n][i]) % mod;
        ret = (ret + nmax[i]) % mod;
    }
    return ret;
}

ll calc(void)
{
    int i, s = 0;
    ll ret = 0;
    prod[0] = 1;
    for(i = 1;i < nu;i++)
    {
        ll cnt = qow(u[i-1], m[i-1]);
        prod[i] = (prod[i-1] * cnt) % mod;
    }
    for(i = nu-1;i >= 0;i--)
    {
        ll part1 = prod[i];
        s += m[i];
        ll tominus = qow(u[i], s);
        ll minus = qow(u[i]-1, s);
        ll part2 = (tominus - minus + mod) % mod;
        ll d = (part1 * part2) % mod;
        d = (d * u[i]) % mod;
        ret = (ret + d) % mod;
    }
    if(u[0] > 1)
    {
        ret = (ret + additional(u[0] - 1)) % mod;
    }
    return ret;
}

int main(void)
{
    int i, j;
    myinit();
    while(EOF != scanf("%d", &n))
    {
        for(i = 0;i < n;i++)
            scanf("%lld", a+i);
        sort(a, a+n);
        j = 0;
        for(i = 0;i < n;i++)
        {
            if(0 == j || a[i] != u[j-1])
            {
                u[j] = a[i];
                m[j++] = 1;
            } else {
                m[j-1]++;
            }
        }
        nu = j;
        printf("%lld\n", calc());
    }
    return 0;
}
