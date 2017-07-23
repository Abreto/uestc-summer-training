/* UESTC 2017 Summer Training #14 Div.2. Problem A, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define MAXN    100001
#define MOD 1000000007

typedef long long int ll;

int n;
ll a[MAXN], b[MAXN];
ll sa[MAXN], sb[MAXN];
ll ans;
ll dp[MAXN];

int main(void)
{
    int i = 0, j = 0;
    scanf("%d", &n);
    for(i = 1;i <= n;++i)
        scanf("%lld", a+i);
    for(i = 1;i <= n;++i)
        scanf("%lld", b+i);
    for(i = 1;i <= n;++i)
        for(j = i;j <= n;j+=i)
            sa[i] = (sa[i]+a[j])%MOD;
    for(i = 1;i <= n;++i)
        for(j = i;j <= n;j+=i)
            sb[i] = (sb[i]+b[j])%MOD;
    for(i = n;i > 0;--i)
    {
        ll t = 0;
        dp[i] = (sa[i]*sb[i])%MOD;
        for(j = (i<<1);j <= n;j+=i)
            dp[i] = (dp[i]-dp[j]+MOD)%MOD;
        t = (i*dp[i])%MOD;
        ans = (ans+t)%MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
