/* Osipovsky Cup 2014 (partially SYSU-Aug-2014 contest). Problem A, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXN    5120

int N;
ll V[MAXN];
int P[MAXN];
int minp[MAXN];
int dp[MAXN][MAXN]; /* [start][length] */

void myinit(void)
{
    int i = 0, j = 0;
    for(i = 0;i <= N;++i)
        minp[i] = P[i];
    memset(dp, -1, sizeof(dp));
}

int do_dp(int i, int w)
{
    int *ans = &(dp[i][w]);
    if(*ans > -1) return (*ans);
    if(w <= 1) return (*ans = 0);
    ll lsum = 0, rsum = 0;
    ll j = i, k = i+w-1;
    lsum = V[j]; rsum = V[k];
    dp[i][w] = minp[w];
    while(j < k)
    {
        if(lsum == rsum)
        {
            dp[i][w] = min(dp[i][w], minp[j-i+1]+minp[i+w-k]+do_dp(j+1,k-j-1));
            lsum += V[++j];
        } else if (lsum < rsum) {
            lsum += V[++j];
        } else {
            rsum += V[--k];
        }
    }
    return dp[i][w];
}

int main(void)
{
    int i = 0;
    scanf("%d", &N);
    for(i = 0;i < N;++i)
        scanf("%lld", V+i);
    for(i = 1;i <= N;++i)
        scanf("%d", P+i);
    myinit();
    printf("%d\n", do_dp(0,N));
    return 0;
}
