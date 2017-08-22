/* UESTC 2017 Summer Training #33 Div.2. Problem B, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

int n;
int a[16];

void transform_to_next(void)
{
    int i = 0;
    int b[16];
    for(i = 0;i < n;++i)
        b[i] = abs(a[i]-a[(i+1)%n]);
    for(i = 0;i < n;++i)
        a[i] = b[i];
}

int check(void)
{
    for(int i = 0;i < n;++i)
        if(a[i])
            return 0;
    return 1;
}

void proc(void)
{
    int i = 0;
    scanf("%d", &n);
    for(i = 0;i < n;++i)
        scanf("%d", a+i);
    for(i = 0;i < 1024;++i)
    {
        if(check())
        {
            puts("ZERO");
            return;
        }
        transform_to_next();
    }
    puts("LOOP");
}

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--)  proc();
    return 0;
}
