/* MIPT-2016 Pre-Finals Workshop, Taiwan NTU Contest. Problem I, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
#define MAXD    20

ll dp_ie[MAXD][10], dp_de[MAXD][10];    /* [i][j] i-digits number starting with j */
ll dp_all[MAXD][10];
/* high <-- low */
ll dp[MAXD];

void myinit(void)
{
    int i = 0, j = 0, k = 0;
    for(i = 0;i < 10;++i)
        dp_ie[1][i] = dp_de[1][i] = dp_all[1][i] = 1;
    dp[1] = 9;
    for(i = 2;i < MAXD;++i)
    {
        for(j = 0;j < 10;++j)
        {
            for(k = 0;k <= j;++k)
                dp_ie[i][j] += dp_ie[i-1][k];
            for(k = j;k < 10;++k)
                dp_de[i][j] += dp_de[i-1][k];
            dp_all[i][j] = dp_ie[i][j] + dp_de[i][j] /* minus if all equal */ - 1;
            dp[i] += dp_all[i][j];
        }
        dp[i] -= dp_all[i][0];
    }
}

ll answer(ll x)
{
    int i = 0, j = 0;
    int ndx = 0;
    int digits[MAXD] = {0};
    ll ret = 0;
    if(0 == x) return 0;
    while(x)
    {
        digits[ndx] = x % 10;
        ndx++;
        x /= 10;
    }
    for(i = 1;i < ndx;++i)
        ret += dp[i];
    for(j = digits[ndx-1]-1;j > 0;j--)
        ret += dp_all[ndx][j];
    if(1 == ndx)
    {
        return ret+1;
    } else {
        int type = 0;
        for(i = ndx-2;i >= 0;--i)
        {
            if(type)    /* i/d determined */
            {
                if (type > 0) {
                    /* increasing or equaling from low to high */
                    if( digits[i+1] < digits[i] )
                    {
                        for(j = digits[i+1];j >= 0;--j)
                            ret += dp_ie[i+1][j];
                        break;
                    }
                    for(j = digits[i]-1;j >= 0;--j)
                        ret += dp_ie[i+1][j];
                } else {
                    /* decreasing or equaling from low to high */
                    if( digits[i+1] > digits[i] )
                    {
                        break;
                    }
                    for(j = digits[i]-1;j >= digits[i+1];--j)
                        ret += dp_de[i+1][j];
                }
            } else {
                if(digits[i] > digits[i+1])
                {
                    for(j = digits[i]-1;j > digits[i+1];--j)
                        ret += dp_de[i+1][j];
                    if(j == digits[i+1])
                        ret += dp_all[i+1][j];
                    for(j=digits[i+1]-1;j >= 0;--j)
                        ret += dp_ie[i+1][j];
                } else {
                    for(j = digits[i]-1;j >= 0;--j)
                        ret += dp_ie[i+1][j];
                }
            }
            if((0 == type) && digits[i] != digits[i+1])
                type = digits[i+1] - digits[i];
        }
        if(0 == type)   /* all equal */
        {
            ret++;  /* count itself. */
        } else if (i < 0) { /* itself is momo */
            ret++;
        }
    }
    return ret;
}

int main(void)
{
    int m = 0;
    myinit();
    scanf("%d", &m);
    while(m--)
    {
        ll li, ri;
        scanf("%lld %lld", &li, &ri);
        printf("%lld\n", answer(ri)-answer(li-1));
    }
    return 0;
}
