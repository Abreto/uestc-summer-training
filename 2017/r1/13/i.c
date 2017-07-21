/* UESTC 2017 Summer Training #13 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <stdio.h>

#define MAXN 100001
#define S 1568617

int d[MAXN];
int nfac[S+1];

int main(void)
{
    int i = 0, j = 0;
    int n = 0, s = 0;
    for(i = 1;i <= S;++i)
        for(j = i;j <= S;j+=i)
            nfac[j]++;
    scanf("%d", &n);
    s = S;
    for(i = 99999;i > 0;i--)
    {
        int t = nfac[s];
        d[i] = t;
        s -= t;
    }
    d[0] = s;
    for(i = 0;i < n;++i)
        printf("%d ", d[i]);
    puts("");
    return 0;
}
