/* UESTC 2017 Summer Training Round2 #03 Div.2. Problem , by . */
#include <stdio.h>
#include <string.h>

typedef unsigned long long int ull;
#define inf (-1ll)

ull n; ull nlen;
char k[64]; ull klen;
ull beforedp[64];
ull dp[64];

#define NUMIZE(c)   ((c)-'0')

ull sec(int i, int j)
{
    ull ret = NUMIZE(k[i]);
    while((++i) <= j)
    {
        ret *= 10;
        ret += NUMIZE(k[i]);
    }
    return ret;
}

ull lg(ull n)
{
    ull ret = 0;
    while(n)
    {
        ret++;
        n /= 10;
    }
    return ret;
}
ull min(ull a, ull b)
{
    return (a<b)?a:b;
}

int main(void)
{
    int i = 0, j = 0;
    scanf("%llu", &n); nlen = lg(n);
    scanf("%s", k); klen = strlen(k);
    for(i = 0;i < klen;++i)
    {
        dp[i] = dp[i-1]*n + sec(i,i);
        for(j = 2;j <= nlen;++j)
        {
            ull di = sec(i-j+1,i);
            if(di < n && NUMIZE(k[i-j+1])!=0)
                dp[i] = min(dp[i], dp[i-j]*n + di);
        }
    }
    printf("%llu\n", dp[klen-1]);
    return 0;
}
