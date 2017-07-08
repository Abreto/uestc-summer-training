/* UESTC 2017 Summer Training #1 Div.2. Problem F, by Abreto<m@abreto.net>. */
#include <stdio.h>

int main(void)
{
    int N = 0, K = 0;
    scanf("%d%d", &N, &K);
    printf("%s\n", (0==((N+1)%K))?"yes":"no");
    return 0;
}
