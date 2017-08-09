/* UESTC 2017 Summer Training #23 Div.2. Problem B, by Abreto<m@abreto.net> */
#include <stdio.h>

#define INPUTFILE   "B.in"

/* 1299709 */
#define MAXN    1300000

int N;
char notprime[MAXN];
int primes[MAXN];

void init(void)
{
    int i = 0, j = 0;
    N = 0;
    notprime[0] = notprime[1] = 1;
    for(i = 2;i < MAXN;++i)
    {
        if(0 == notprime[i])
            primes[N++] = i;
        for(j = 0;j < N && primes[j]*i < MAXN;++j)
        {
            notprime[i*primes[j]] = 1;
            if(0 == i % primes[j]) break;
        }
    }
}
int bisearch(int x)
{
    int l = 0, r = N-1; /* [l,r] */
    while(l < r)
    {
        int mid = (l+r)>>1;
        if(primes[mid+1] <= x)
            l = mid+1;
        else r = mid;
    }
    return l;
}

int answer(int x)
{
    if(0 == notprime[x]) return 0;
    else
    {
        int l = bisearch(x);
        return primes[l+1]-primes[l];
    }
}

int main(void)
{
    int i = 0;
#ifndef ABDEBUG
    freopen(INPUTFILE, "r", stdin);
#endif
    init();
    while(EOF != scanf("%d", &i) && i)
        printf("%d\n", answer(i));
    return 0;
}
