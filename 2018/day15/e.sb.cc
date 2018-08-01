#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long int ll;

int L;
ll A[16];
ll sum[16], isum[16], dsum[16];

void pre(void)
{
    ll i = 0;
    sum[0] = 0;
    for(i = 0;i < L;i++)
        sum[i+1] = sum[i] + A[i];
    isum[0] = 0;
    for(i = 0;i < L;i++)
        isum[i+1] = isum[i] + (i+1) * A[i];
    isum[0] = (L)*A[0];
    for(i = 0;i < L;i++)
        dsum[i+1] = dsum[i] + (L-i) * A[i];
}

ll sumofinc(ll begin, ll length)
{
    ll first_length = min(L - begin, length - begin + 1);
    ll first_sum = (isum[L] - isum[begin]) - (begin-1ll)*(sum[L]-sum[begin]);
    ll middle_sum = 0;
    ll middle_block = (length - first_length) / L;
}

ll sumofeq(ll begin, ll length, ll weight)
{
    ;
}

ll sumofdrop(ll end, ll length)
{
    ;
}

ll calc(ll x0, ll y0, ll x1, ll y1)
{
    ll h = x1 - x0 + 1, w = y1 - y0 + 1;
    ll slope = min(h, w) - 1;
    ll eq = abs(h-w) + 1;
    return sumofinc((x0+y0)%L, slope) + sumofeq((x1+y0)%L, eq, slope+1) + sumofdrop((x1+y1)%L, slope);
}

void proc(void)
{
    int i;
    scanf("%d", &L);
    for(i = 0;i < L;i++)
        scanf("%lld", A+i);
    pre();
    scanf("%d", &i);
    while(i--)
    {
        ll x0, y0, x1, y1;
        scanf("%lld%lld%lld%lld", &x0, &y0, &x1, &y1);
        printf("%lld\n", calc(x0,y0,x1,y1));
    }
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while(T--) proc();
    return 0;
}
