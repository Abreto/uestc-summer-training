/* UESTC 2017 Summer Training Round2 #03 Div.2. Problem J, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <algorithm>
#include <cassert>

using namespace std;

#define MAXN    100000
#define MAXM    2048

typedef long long int ll;

struct team
{
    ll t, n;
    team():t(0),n(0){}
    bool operator<(const team &o) const
    {
        return t<o.t;
    }
}t[MAXM];

ll N, M, K;
ll dp[MAXN+1];
ll last[MAXN+1];

int main(void)
{
    int i = 0, j = 0, Ai = 0;
    ll del = 0; ll ans = 10000000000ll;
    int ok = 0;
    scanf("%lld %lld %lld", &N, &M, &K);
    for(i = 1;i <= N;++i)
    {
        scanf("%d", &Ai);
        t[Ai].t = i;
        t[Ai].n++;
    }
    sort(t+1, t+M+1);
    for(i = 0;i < M;++i)
    {
        for(j = K;j >= t[i].n;--j)
        {
            ll newn = dp[j-t[i].n]+t[i].n;
            if(dp[j] < newn)
            {
                dp[j] = newn;
                last[j] = t[i].t;
            }
        }
        if(dp[K] >= 0 && dp[K] <= K && (N-dp[K] >= 0) && (N-dp[K] <= K))
        {
            ok = 1;
            ans = min(ans, dp[K]*last[K]+(N-dp[K])*N);
        }/*
        for(j = 1;j <= i;++j)
        {
            if(dp[i-j]+t[i].n <= K)
                dp[i] = max(dp[i], dp[i-j]+t[i].n);
        }
        if(dp[i] >= 0 && dp[i] <= K && (N-dp[i] >= 0) && (N-dp[i] <= K))
        {
            ok = 1;
            del = max(del, dp[i]*(N-t[i].t));
            ans = min(ans, dp[i]*t[i].t+(N-dp[i])*N);
        }*/
    }
    /*assert(N*N-del==ans);*/
    if(ok)
        printf("%lld\n", ans);
    else
        puts("-1");
    return 0;
}
