/* UESTC 2017 Summer Training #14 Div.2. Problem F, by Abreto<m@abreto.net>. */
#include <stdio.h>

int main(void)
{
    char dst[4] = "PER";
    char ori[512];
    char *p = NULL;
    int cnt = 0;
    scanf("%s", ori);
    for(p=ori;*p;p++)
        if(*p != dst[(p-ori)%3])
            cnt++;
    printf("%d\n", cnt);
    return 0;
}
