/* UESTC 2017 Summer Training #8 Div.2. Problem H, by Abreto<m@abreto.net>. */
#include <stdio.h>

int max(int a,int b){return (a>b)?a:b;}

#define MAXT    2000001

int dp[MAXT];
int fun[MAXT];
int wt[MAXT];

int main(void)
{
    int i = 0, n = 0;
    int mi = 0;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%d", &mi);
        scanf("%d%d", fun+mi, wt+mi);
    }
    for(i = 1000000;i > 0;i--)
    {
        dp[i] = max(dp[i+1], fun[i]+dp[i+wt[i]]);
    }
    printf("%d\n", dp[1]);
    return 0;
}
