/* UESTC 2017 Summer Training #1 Div.2. Problem C, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define SET(x, i)   (x=((x)|(1<<(i))))
#define GET(x, i)   (((x)>>(i))&1)
#define EPS (1e-8)

int N, M;
double K;
int f[2048];

int count(int bits)
{
    int cnt = 0;
    while(bits)
    {
        cnt += (bits & 1);
        bits >>= 1;
    }
    return cnt;
}

int main(void)
{
    int i = 0, j = 0;
    int Q = 0, q = 0;
    int state = 0;
    long long int ans = 0;
    scanf("%d%d", &N, &M);
    while(N--)
    {
        state = 0;
        scanf("%d", &Q);
        while(Q--)
        {
            scanf("%d", &q);
            SET(state, q);
        }
        f[state]++;
    }
    scanf("%lf", &K);
    Q = (2<<M);
    for(i = 0;i < Q;++i)
        for(j = i;j < Q;++j)
        {
            double and = (double)count(i & j), or = (double)count(i | j);
            if( and/or - K >= -EPS )
            {
                if(i == j)
                    ans += (long long int)f[i] * (long long int)(f[i]-1) / 2;
                else
                    ans += (long long int)f[i] * (long long int)f[j];
            }
        }

    printf("%lld\n", ans);
    return 0;
}
