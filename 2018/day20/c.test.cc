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
    ll maxunit = 0;
    for(int i = 0;i <= 18;i++)
    {
        ll delta = 0;
        ll three = qow(3, 18-i);
        if( greated )
        {
            delta = three;
        } else {
            ll two = qow(2, 1ll<<i);
            if(two > three)
            {
                delta = three;
                greated = 1;
                printf("greated at %d\n", i);
            } else {
                delta = two;
            }
        }
        sum += delta;
        length += delta * (1ll<<i);
        maxsize = max(maxsize, delta * (1ll<<i));
        maxunit = max(maxunit, delta);
    }
    printf("%lld\n", sum);
    printf("%lld\n", length);
    printf("%lld\n", maxsize);
    printf("%lld\n", maxunit);
    return 0;
}
