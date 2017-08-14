/* Petrozavodsk Summer-2015. Xudyh Contest. Problem A, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MOD 1000000007
#define MAXN    128

ll factorial[MAXN];
ll C[MAXN][MAXN];
void init(void)
{
    int i = 0, j = 0;
    factorial[0] = 1;
    for(i = 1;i < MAXN;++i)
        factorial[i] = (factorial[i-1] * i) % MOD;
    for(i = 1;i < MAXN;++i)
    {
        C[i][0] = 1;
        for(j = 1;j <= i;++j)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
    }
}

int n;
ll a[MAXN];
char op[MAXN];
ll dp[MAXN][MAXN];  /* dp[i][len] */

void clear(void)
{
    memset(dp, 0, sizeof(dp));
}

void do_dp(void)
{
    int i = 0, j = 0;
    int w = 0;
    for(i = 0;i < n;++i)
        dp[i][1] = a[i] % MOD;
    for(w = 2;w <= n;++w)   /* length */
    {
        for(i = 0;i <= n-w;++i) /* start pos */
        {
            dp[i][w] = 0;
            for(j = 0;j < w;++j)    /* op offset to i */
            {
                char oper = op[i+j];
                ll llen = (ll)(j+1), rlen = (ll)(w-j-1ll);
                ll le = dp[i][llen], ri = dp[i+j+1][rlen];
                ll lp = factorial[llen-1], rp = factorial[rlen-1];
                ll tmp = 0;
                if('*' == oper)
                {
                    tmp = (le * ri) % MOD;
                } else if ('+' == oper) {
                    ll tmp1 = (le * rp) % MOD, tmp2 = (ri * lp) % MOD;
                    tmp = (tmp1 + tmp2) % MOD;
                } else if ('-' == oper) {
                    ll tmp1 = (le * rp) % MOD, tmp2 = (ri * lp) % MOD;
                    tmp = (tmp1 - tmp2 + MOD) % MOD;
                }
                ll tmp3 = (tmp * C[w-1][j]) % MOD;
                dp[i][w] = (dp[i][w] + tmp3)  % MOD;
            }
        }
    }
}

void proc(void)
{
    int i = 0;
    for(i = 0;i < n;++i)
        scanf("%lld", a+i);
    scanf("%s", op);
    do_dp();
    printf("%lld\n", dp[0][n]);
}

int main(void)
{
    int T = 0;
    init();
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        clear();
        proc();
    }
    return 0;
}
