/* UESTC 2017 Summer Training #34 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

#define MAXN    128

int n;

void mymove(int a, int b, int c)
{
    printf("%d %d %d\n", a, b, c);
}

int main(void)
{
    int i = 0, j = 0;
    scanf("%d", &n);
    mymove(1,1,0);
    for(i = 1;i < n;++i)
    {
        for(j = i+2;j <= n;++j)
        {
            mymove(j,j,i);
            mymove(i,i,j);
        }
        mymove(i+1,i+1,i);
    }
    for(i = n;i > 2;--i)
        mymove(i-1, i-1, i);
    mymove(0,1,2);
    return 0;
}
