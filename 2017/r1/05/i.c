/* UESTC 2017 Summer Training #5 Div.2. Problem I, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define MAXN    2001
#define MOD (1000000007)

typedef long long int ll;

ll dp[MAXN][26][4];
ll ans[MAXN];

void dodp(void)
{
    int i = 0, j = 0, k = 0, l = 0;
    for(i = 2;i < MAXN;++i)
    {
        for(j = 0;j < 26;++j)
        {
            /* 1 == k */
            for(k = 0;k < 26;++k)
                if(j != k)
                {
                    for(l = 1;l < 4;++l)
                        dp[i][j][1] = (dp[i][j][1]+dp[i-1][k][l])%MOD;
                }
            for(k = 2;k < 4;++k)
                dp[i][j][k] = (dp[i][j][k]+dp[i-1][j][k-1])%MOD;
        }
    }
}

void init(void)
{
    int i = 0, j = 0, k = 0;
    for(i = 0;i < 26;++i)
        dp[1][i][1] = 1;
    dodp();
    for(i = 0;i < MAXN;++i)
        for(j = 0;j < 26;++j)
            for(k = 1;k < 4;++k)
                ans[i] = (ans[i]+dp[i][j][k])%MOD;
}

int main(void)
{
    int T = 0, n = 0;
    scanf("%d", &T);
    init();
    while(T--)
    {
        scanf("%d", &n);
        printf("%lld\n", ans[n]);
    }
    return 0;
}
