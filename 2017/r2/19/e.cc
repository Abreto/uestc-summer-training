/* UESTC 2017 Summer Training #33 Div.2. Problem E, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

int n, w;
ll u[128];
ll sumu[128];
ll dp[128][128];    /* dp[i][j]: j paging zones in first i cells */

void proc(void)
{
    int i = 0, j = 0, k = 0;
    scanf("%d%d", &n, &w);
    for(i = 1;i <= n;++i)
        scanf("%lld", u+i);
    sort(u+1, u+n+1, greater<int>());
    for(i = 1;i <= n;++i)
        sumu[i] = u[i] + sumu[i-1];
    for(i = 1;i <= n;++i)
    {
        dp[i][1] = i * sumu[i];
        for(j = 2;j <= i;++j)
        {
            dp[i][j] = 0x7fffffffffffffff;
            for(k = 1;k <= i-j+1;++k)
                dp[i][j] = min(dp[i][j], dp[i-k][j-1] + i*(sumu[i]-sumu[i-k]));
        }
    }
    double du = dp[n][w];
    double db = sumu[n];
    printf("%.4lf\n", du/db);
}

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--) proc();
    return 0;
}
