#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long int ll;

#define mod (1000000007)
#define MAXN    (1<<10)

int n, nu;
ll a[MAXN];
ll prod[MAXN];

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

ll f[MAXN];
ll calc(void)
{
    int i, j;
    ll ret = 0;
    prod[0] = 1;
    for(i = 1;i < n;i++)
    {
        prod[i] = (prod[i-1] * a[i-1]) % mod;
    }
    for(i = 0;i < n;i++)
    {
        ll sig = (a[i] * (a[i]+1) / 2ll) % mod;
        f[i] = (prod[i] * sig) % mod;
        f[i] = (f[i] * qow(a[i]-1, n-i-1)) % mod;
        for(j = 0;j < i;j++)
            f[i] = (f[i] - f[j] + mod) % mod;
        ret = (ret + f[i]) % mod;
    }
    return ret;
}

int main(void)
{
    int i, j;
    while(EOF != scanf("%d", &n))
    {
        for(i = 0;i < n;i++)
            scanf("%lld", a+i);
        sort(a, a+n);
        printf("%lld\n", calc());
    }
    return 0;
}
