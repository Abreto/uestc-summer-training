/* UESTC 2017 Summer Training #5 Div.2. Problem F, by Abreto<m@abreto.net>. */
#include <stdio.h>

typedef long long int ll;

int sg(int s, int k)
{
    if(k&1) return (s&1);
    else
    {
        int r = s%(k+1);
        return (r==k)?2:(r&1);
    }
}

int ans(int s, int k)
{
    ll i = 0;
    for(i = 1;i <= s;i *= k)
        if(0 == sg(s-i,k))
            return i;
    return 0;
}

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--)
    {
        int S = 0, K = 0;
        scanf("%d%d", &S, &K);
        printf("%d\n", ans(S,K));
    }
    return 0;
}
