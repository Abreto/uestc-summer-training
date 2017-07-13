/* UESTC 2017 Summer Training #6 Div.2. Problem A, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <string.h>

char a[100001];

int main(void)
{
    int n0 = 0, n1 = 0;
    char *p = a;
    scanf("%s", a);
    while(*p)
    {
        if('0'==*p)n0++;
        else if('1'==*p)n1++;
        ++p;
    }
    printf("%d\n", (n0<n1)?n0:n1);
    return 0;
}
