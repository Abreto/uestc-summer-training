/* UESTC 2017 Summer Training #8 Div.2. Problem C, by Abreto<m@abreto.net>. */
#include <stdio.h>

int min(int a, int b){return (a<b)?a:b;}
int max(int a, int b){return (a>b)?a:b;}

int main(void)
{
    int i = 0;
    int n = 0, k = 0;
    int maxsafe = 0, minbroken = 128;
    char res[8];

    scanf("%d%d", &n, &k);
    maxsafe = 1; minbroken = k;
    while(n--)
    {
        scanf("%d %s", &i, res);
        if('S' == res[0]) maxsafe = max(maxsafe,i);
        else if ('B' == res[0]) minbroken = min(minbroken,i);
    }

    printf("%d %d\n", maxsafe+1, minbroken-1);
    return 0;
}
