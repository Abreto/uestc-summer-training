/* UESTC 2017 Summer Training #11 Div.2. Problem H, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define INPUT   "hotel.in"
#define OUTPUT  "hotel.out"

typedef long long int ll;

ll dp[20][10];
ll tot1[20];    /* include leading zero. */
ll tot2[20];    /* exclude leading zero. */
ll sum[20];

void init(void)
{
    int i = 0, j = 0;
    for(j = 0;j < 10;++j)
        dp[1][j] = 1;
    tot1[1] = 10;
    tot2[1] = 9;
    sum[1] = 9;
    for(i = 2;i < 20;++i)
    {
        for(j = 0;j < 10;++j)
            if(1 != j)
                dp[i][j] = tot1[i-1];
            else
                dp[i][j] = tot1[i-1]-dp[i-1][3];
        for(j = 0;j < 10;++j)
            tot1[i] += dp[i][j];
        tot2[i] = tot1[i] - dp[i][0];
        sum[i]  = sum[i-1] + tot2[i];
    }
}

ll ans(ll N)
{
    int i = 0, d = 0;
    ll ret = 0, cur = 0;
    for(i = 1;i < 20;++i)
        if(sum[i] >= N)
            break;
    /* i digits, sure; */
    cur = sum[i-1];
    for(d = 1;d < 10;++d)
    {
        if(cur+dp[i][d] >= N)
        {
            ret = d;
            //N -= cur;
            i--;
            break;
        }
        cur += dp[i][d];
    }
    while(i)
    {
        int lastd = ret % 10;
        /*cur = sum[i-1];*/
        for(d = 0;d < 10;++d)
            if(!(1==lastd&&3==d))
            {
                if(cur+dp[i][d] >= N)
                {
                    ret *= 10;
                    ret += d;
                    //N -= cur;
                    i--;
                    break;
                }
                cur += dp[i][d];
            }
    }
    return ret;
}

int main(void)
{
    int T = 0;
    ll N = 0;
    init();
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w+", stdout);
    for(T = 1;T < 20;++T)
        printf("%d:%lld\n", T, sum[T]);
    for(T = 1;T < 20;++T)
    {
        printf("%d:", T);
        for(N = 0;N < 10;++N)
            printf(" %lld", dp[T][N]);
        puts("");
    }
    scanf("%d", &T);
    while(T--)
    {
        scanf("%lld", &N);
        printf("%lld\n", ans(N));
    }
    return 0;
}
