/* UESTC 2017 Summer Training #15 Div.2. Problem G, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <string.h>

int len;
char alphabat[128];

int main(void)
{
    int P = 0;
    int K = 0, N = 0;
    int pos = 0, offset = 0;
    scanf("%d", &P);
    while(P--)
    {
        scanf("%d", &K); getchar();
        fgets(alphabat, 128, stdin);
        len = strlen(alphabat)-1;
        printf("%d ", K);
        scanf("%d", &N);
        pos = 0;
        while(N--)
        {
            scanf("%d", &offset);
            pos = (pos+offset+len) % len;
            putchar(alphabat[pos]);
        }
        puts("");
    }
    return 0;
}
