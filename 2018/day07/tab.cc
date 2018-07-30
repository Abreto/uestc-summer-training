#include <cstdio>

using namespace std;
typedef long long int ll;

int main(void)
{
    ll maxn = 100;
    for(ll n = 1;n <= maxn;n++)
    {
        ll ans = 0;
        ll ax, ay, az;
        for(ll i = 1;i <= n;i++)
        for(ll j = 1;j <= n;j++)
        {
            ll k = n - i - j;
            if(0 == k) continue;
            if(n % i || n % j || n % k) continue;
            ll prod = i * j * k;
            if(prod > ans)
            {
                ans = prod;
                ax = i; ay = j; az = k;
            }
        }
        printf("%lld, %lld: %lld, %lld, %lld\n", n, ans, ax, ay, az);
    }
    return 0;
}
