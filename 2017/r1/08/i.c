/* UESTC 2017 Summer Training #8 Div.2. Problem I, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <stdlib.h>

int compar(const void *a, const void *b)
{
    return ((*((int*)a))-(*((int*)b)));
}

void no(void){puts("NO");exit(EXIT_SUCCESS);}
void yes(void){puts("YES");exit(EXIT_SUCCESS);}

int main(void)
{
    int a[3] = {0}, b[3] = {0};
    scanf("%d%d%d", a, a+1, a+2);
    scanf("%d%d%d", b, b+1, b+2);
    qsort(a, 3, sizeof(int), compar);
    qsort(b, 3, sizeof(int), compar);
    if(a[0]!=b[0]||a[1]!=b[1]||a[2]!=b[2]) no();
    if(a[0]*a[0]+a[1]*a[1]!=a[2]*a[2]) no();
    yes();
    return 0;
}
