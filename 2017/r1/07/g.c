/* UESTC 2017 Summer Training #7 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <stdio.h>

void proccess(void)
{
    int i = 0;
    int a[32] = {0};
    for(i = 0;i < 20;++i)
        scanf("%d", a+i);
    for(i = 19;i > 0;--i)
    {
        a[i-1] += a[i]/2;
        a[i] &= 1;
    }
    printf("%d", a[0]);
    for(i = 1;i < 20;++i)
        printf(" %d", a[i]);
    puts("");
}

int main(void)
{
    int N = 0;
    scanf("%d", &N);
    while(N--) proccess();
    return 0;
}
