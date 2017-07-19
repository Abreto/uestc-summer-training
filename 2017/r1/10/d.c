/* UESTC 2017 Summer Training #10 Div.2. Problem D, by Abreto<m@abreto.net>. */
#include <stdio.h>

int main(void)
{
    int i = 0, j = 0, n = 0;
    scanf("%d", &n);
    for(i = 1;i < n;i*=2)
        j++;
    printf("%d\n",j+1);
    return 0;
}
