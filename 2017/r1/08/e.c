/* UESTC 2017 Summer Training #8 Div.2. Problem E, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compar(const void *a, const void *b)
{
    return ((*((int*)b)) - (*((int*)a)));
}

int main(void)
{
    int i = 0;
    int n = 0;
    int cnt[64] = {0};
    char str[128] = {0};

    scanf("%s", str);
    n = strlen(str);
    for(i = 0;i < n;++i)
        cnt[str[i]-'a']++;
    qsort(cnt, 64, sizeof(int), compar);
    n -= cnt[0]; n -= cnt[1];

    printf("%d\n", n);
    return 0;
}
