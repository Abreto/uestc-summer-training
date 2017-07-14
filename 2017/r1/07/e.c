/* UESTC 2017 Summer Training #7 Div.2. Problem E, by Abreto<m@abreto.net>. */
#include <stdio.h>

int g[16];
int cnt[10];

int nolessthan(int x)
{
    int i = 0;
    if(0 == x) return 1;
    for(i = 1;i < 10;++i)
    {
        if(cnt[i] >= 3)
        {
            cnt[i] -= 3;
            if(nolessthan(x-1)) return 1;
            cnt[i] += 3;
        }
    }
    for(i = 1;i < 8;++i)
        if(cnt[i] && cnt[i+1] && cnt[i+2])
        {
            cnt[i]--; cnt[i+1]--; cnt[i+2]--;
            if(nolessthan(x-1)) return 1;
            cnt[i]++; cnt[i+1]++; cnt[i+2]++;
        }
    return 0;
}

int query(void)
{
    int i = 0, j = 0;
    for(i = 1;i < 10;++i)
    {
        if(cnt[i] > 1) /* 1 pair */
        {
            cnt[i] -= 2;
            if(nolessthan(4)) return 1;
            cnt[i] += 2;
        }
    }
    return 0;
}

int main(void)
{
    int N = 0;
    scanf("%d", &N);
    while(N--)
    {
        int i = 0;
        for(i = 0;i < 10;++i) cnt[i] = 0;
        for(i = 0;i < 14;++i)
        {
            scanf("%d", g+i);
            cnt[g[i]]++;
        }
        printf("%s\n", query()?"Vulnerable":"Immune");
    }
    return 0;
}
