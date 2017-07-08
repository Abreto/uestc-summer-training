/* UESTC 2017 Summer Training #1 Div.2. Problem H, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define MAXN    500001

int min(int a, int b)
{
    return (a<b)?a:b;
}

int N, k;
/* 0 for negative, 1 for positive */
int cnt[MAXN][2];
int dp[MAXN][2];

int main(void)
{
    int i = 0;
    int ai = 0;

    scanf("%d%d\n", &N, &k);
    for(i = 0;i < N;++i)
    {
        scanf("%d", &ai);
        cnt[i%k][ai>0]++;
    }
    dp[0][0] = cnt[0][1];
    dp[0][1] = cnt[0][0];
    for(i = 1;i < k;++i)
    {
        dp[i][0] = min(dp[i-1][0]+cnt[i][0], dp[i-1][1]+cnt[i][1]);
        dp[i][1] = min(dp[i-1][0]+cnt[i][1], dp[i-1][1]+cnt[i][0]);
    }

    printf("%d\n", dp[k-1][1]);
    return 0;
}
