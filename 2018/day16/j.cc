#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

ll n, p2, p3;
ll ans;

void upd(ll x, ll y)
{
    if(x < 0 || y < 0) return;
    if(2ll*x + 3l*y < n) return;
    ll cost = p2 * x + p3 * y;
    ans = min(ans, cost);
}

int main(void)
{
    scanf("%lld%lld%lld", &n, &p2, &p3);
    ll x = (n+1ll) / 2ll, y = (n+2ll)/3ll;
    ans = min(p2*x, p3*y);
    for(ll i = -10;i <= 10;i++)
        for(ll j = -10;j <= 10;j++)
        {
            upd(x+i,j);
            upd(i,y+j);
        }
    printf("%lld\n", ans);
    return 0;
}
