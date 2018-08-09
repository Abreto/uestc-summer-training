#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
ll qow(ll a, ll p)
{
    ll ret = 1;
    while(p)
    {
        if (1 & p) ret *= a;
        a *= a;
        p >>= 1;
    }
    return ret;
}

int main(void)
{
    int greated = 0;
    ll sum = 0;
    ll length = 0;
    ll maxsize = 0;
    ll iter = 0;
    for(int i = 0;i <= 18;i++)
    {
        ll delta = 0;
        ll left = qow(3, 18-i);
        ll right = qow(3, i);
        delta = min(left, right);
        sum += delta;
        length += delta * (1ll<<i);
        maxsize = max(maxsize, delta * (1ll<<i));
    }
    printf("%lld\n", sum);
    printf("%lld\n", length);
    printf("%lld\n", maxsize);
    printf("%lld\n", iter);
    return 0;
}
