/* UESTC 2017 Summer Training #4 Div.2. Problem G, by Abreto<m@abreto.net>. */
#include <stdio.h>

typedef long long int ll;

ll max(ll a, ll b)
{
    return (a>b)?a:b;
}

ll ans(ll N)
{
    ll odd = (N+1)/2, even = N/2;
    ll c1 = odd*(odd-1)/2 * even;
    ll c2 = max(0, even*(even-1)*(even-2)/6);
    return c1+c2;
}

int main(void)
{
    ll N = 0;

    scanf("%lld", &N);
    printf("%lld\n", ans(N));

    return 0;
}