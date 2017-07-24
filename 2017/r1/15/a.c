/* UESTC 2017 Summer Training #15 Div.2. Problem A, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define MAXL    10000002

char D[MAXL];

int mo(int b)
{
    int ret = 0;
    char *p = D;
    while(*p)
    {
        ret = (ret*b) % (b-1);
        ret = (ret+*p-'0') % (b-1);
        p++;
    }
    return ret;
}

int main(void)
{
    int P = 0;
    int k = 0, B = 0;
    scanf("%d", &P);
    while(P--)
    {
        scanf("%d %d %s", &k, &B, D);
        printf("%d %d\n", k, mo(B));
    }
    return 0;
}
