/* UESTC 2017 Summer Training #15 Div.2. Problem D, by Abreto<m@abreto.net>. */
#include <stdio.h>

typedef long long int ll;

ll f(int n)
{
    ll ln = n;
    ll aji = n;
    while(1 != ln)
    {
        if(ln&1) ln = ln*3ll+1ll;
        else ln = ln>>1;
        if(ln > aji) aji = ln;
    }
    return aji;
}

int main(void)
{
    int P = 0;
    int k = 0, n = 0;
    scanf("%d", &P);
    while(P--)
    {
        scanf("%d %d", &k, &n);
        printf("%d %lld\n", k, f(n));
    }
    return 0;
}
