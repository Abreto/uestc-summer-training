/* UESTC 2017 Summer Training #5 Div.2. Problem G, by Abreto<m@abreto.net>. */
#include <stdio.h>

int main(void)
{
    int x = 0, cnt = 0;
    scanf("%d", &x);
    while(x){cnt+=x&1;x>>=1;}
    printf("%d\n", cnt);
    return 0;
}
