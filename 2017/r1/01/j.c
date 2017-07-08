/* UESTC 2017 Summer Training #1 Div.2. Problem J, by Abreto<m@abreto.net>. */
#include <stdio.h>

int main(void)
{
    int i = 0;
    int N = 0, K = 0;
    int nd = 0;
    int ld = 0, cd = 0;

    scanf("%d%d", &N, &K);
    scanf("%d", &ld);
    for(i = 1;i < N;++i)
    {
        scanf("%d", &cd);
        if(ld != cd) nd++;
        ld = cd;
    }
    printf("%.8lf\n", (double)(K-1)*(double)nd/(double)K);

    return 0;
}
