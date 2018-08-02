#include <cstdio>

using namespace std;

typedef long long int ll;

int check(int n)
{
    ll n2 = 1ll*n*n;
    ll l = 1ll*n*n+1, r = 1ll*n*n+2ll*n;
    ll diviee = 1ll*n*n*n*n;
    int ok = 0;
    for(ll x = l;x <= r;x++)
        if(0 == diviee % x)
        {
            ok = 1;
            ll L = x - n2;
            printf("n=%d: %lld=%lld+%lld in [%lld,%lld] | %lld(%lld)\n", n, x, 1ll*n*n, x-1ll*n*n, l, r, diviee, diviee%x);
            printf("%lld/%lld=%lld+%lld\n", n2*L, n2+L, (n2*L)/(n2+L), (n2*L)%(n2+L));
            printf("2n-l=%lld\n", 2ll*n-(x-n2));
            printf("k=%lld\n", n2*n2/x);
            printf("n^2-k=%lld\n", n2-n2*n2/x);
            puts("----");
            //return 1;
        }
    if(ok) puts("#####");
    return 0;
}

int main(void)
{
    int n = 0;
    int maxn = 0;
    scanf("%d", &maxn);
    for(n = 1;n <= maxn;n++)
        if(check(n));
            // printf("%d\n", n);
    return 0;
}
