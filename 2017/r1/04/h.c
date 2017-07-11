/* UESTC 2017 Summer Training #4 Div.2. Problem H, by Abreto<m@abreto.net>. */
#include <stdio.h>

int poss(int w, int h)
{
    if(w < 10 && h < 10 && w*h < 6) return 0;
    if(w % 6)
    {
        if(0 == w%2)
        {
            return (0 == h%3);
        } else if (0 == w%3) {
            return (0 == h%2);
        } else return (w>6)?(poss(w%6,h)||poss(h,w%6)):0;
    } else {
        return (h>1);
    }
}

int main(void)
{
    int K = 0;
    int N = 0, M = 0;
    scanf("%d", &K);
    while(K--)
    {
        scanf("%d%d", &N, &M);
        printf("%s\n", (poss(N,M)||poss(M,N))?"Yes":"No");
    }
    return 0;
}
