#include <stdio.h>

#define MAXN    100001
#define MAXS    1600000

int ndiv_m[MAXS];
int ndiv(int x)
{
    int i = 0, cnt = 0;
    for(i = 1;i*i < x;++i)
        if(x == x/i*i)
            cnt += 2;
    if(i*i == x) cnt++;
    return cnt;
}

int dp[MAXS];
int mins[MAXN];

int main(void)
{
    int n = 0, m = 0;
    int i = 0;
    scanf("%d %d", &n, &m);
    dp[1] = dp[2] = 1;
    for(i = 3;i < n;++i)
    {
        dp[i] = dp[i-ndiv(i)]+1;
        if(dp[i] > 100000)
            break;
    }
    for(i = 1;i < n;++i)
        if(0 == mins[dp[i]])
            mins[dp[i]] = i;
    printf("int dp[%d]={0", m);
    for(i = 1;i < m;++i)
        printf(",%d", mins[i]);
    puts("};");
    return 0;
}
