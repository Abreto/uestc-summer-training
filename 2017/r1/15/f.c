/* UESTC 2017 Summer Training #15 Div.2. Problem F, by Abreto<m@abreto.net>. */
#include <stdio.h>

typedef long long int ll;

/* A001250 */
ll dp[32] = {1, 1, 2, 4, 10, 32, 122, 544, 2770, 15872, 101042, 707584, 5405530, 44736512, 398721962, 3807514624, 38783024290, 419730685952, 4809759350882, 58177770225664, 740742376475050};

int main(void)
{
    int P = 0;
    int D = 0, n = 0;
    scanf("%d", &P);
    while(P--)
    {
        scanf("%d %d", &D, &n);
        printf("%d %lld\n", D, dp[n]);
    }
    return 0;
}
