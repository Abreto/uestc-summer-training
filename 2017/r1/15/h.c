/* UESTC 2017 Summer Training #15 Div.2. Problem H, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define MAXN    128
#define MOD 1000000007
typedef long long int ll;

ll A[MAXN][MAXN];
ll C[MAXN][MAXN];
ll factorial[MAXN];

void init(void)
{
    ll i = 0, j = 0;
    C[0][0] = C[1][0] = C[1][1] = 1;
    for(i = 2;i < MAXN;++i)
    {
        C[i][0] = C[i][i] = 1;
        for(j = 1;j < i;++j)
            C[i][j] = (C[i-1][j-1] + C[i-1][j])%MOD;
    }
    A[0][0] = A[1][0] = A[1][1] = 1;
    for(i = 2;i < MAXN;++i)
    {
        A[i][0] = 1;
        for(j = 1;j <= i;++j)
            A[i][j] = (A[i][j-1]*(i-j+1ll))%MOD;
    }
    factorial[0] = 1;
    for(i = 1;i < MAXN;++i)
    {
        factorial[i] = (factorial[i-1]*i) % MOD;
    }
}

ll ans(int n, int m)
{
    ll i = 0;
    ll ret = factorial[n+m];
    for(i = 1;i <= m;++i)
    {
        ll flag = (i&1) ? -1ll : 1ll;
        ll delta = (C[m][i]*factorial[n+m-i])%MOD;
        ret = (ret + flag*delta + MOD) % MOD;
    }
    return ret;
}

int main(void)
{
    int n = 0, m = 0;
    init();
    scanf("%d %d", &n, &m);
    printf("%lld\n", ans(n,m));
    return 0;
}
