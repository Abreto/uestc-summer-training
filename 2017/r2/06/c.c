/* UESTC 2017 Summer Training #22. Problem C, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <math.h>

#define MAXC    2000

int cnt[MAXC][MAXC];

int main(void)
{
    int i = 0, j = 0;
    int N = 0;
    int ans = 0;
    scanf("%d", &N);
    while(N--)
    {
        int xi1 = 0, yi1 = 0, xi2 = 0, yi2 = 0;
        double dxi1 = 0.0, dyi1 = 0.0, dxi2 = 0.0, dyi2 = 0.0;
        double k = 0.0;
        int dy = 0, dx = 0;
        int w = 0;
        scanf("%d %d %d %d", &xi1, &yi1, &xi2, &yi2);
        if(xi1 == xi2 || yi1 == yi2) continue;
        if(xi1 > xi2)
        {
            xi1 ^= xi2; xi2 ^= xi1; xi1 ^= xi2;
            yi1 ^= yi2; yi2 ^= yi1; yi1 ^= yi2;
        }
        dy = yi2 - yi1; dx = xi2 - xi1;
        w = xi2 - xi1;
        if(yi2 > yi1)
            for(i = 0;i < w;++i)
            {
                int bot = i*dy / dx;
                int top = ((i+1)*dy+dx-1)/dx;
                for(j = bot;j < top;++j)
                    cnt[i+xi1][yi1+j] = 1;
            }
        else
            for(i = 0;i < w;++i)
            {
                int top = i * dy / dx;
                int bot = ((i+1)*dy+1)/dx - 1;
                for(j = bot;j < top;++j)
                    cnt[i+xi1][yi1+j] = 1;
            }
    }
    for(i = 0;i < 2000;++i)
        for(j = 0;j < 2000;++j)
            if(1 == cnt[i][j])
                ans++;
    printf("%d\n", ans);
    return 0;
}
