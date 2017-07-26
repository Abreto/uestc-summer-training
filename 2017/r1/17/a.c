/* UESTC 2017 Summer Training #17 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <stdio.h>

#define MAXN    80001
char a[MAXN], b[MAXN];

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--)
    {
        int i = 0;
        int N = 0, X = 0, Y = 0;
        int neq = 0, ndiff = 0, d = 0;
        scanf("%d%d%d", &N, &X, &Y);
        d = (X>Y)?(X-Y):(Y-X);
        scanf("%s\n", a);
        scanf("%s\n", b);
        for(i = 0;i < N;++i)
        {
            neq += (a[i] == b[i]);
            ndiff += (a[i] != b[i]);
        }
        if(d > ndiff) puts("Lying");
        else if ((X+Y)>(2*neq+ndiff)) puts("Lying");
        else puts("Not lying");
    }
    return 0;
}
