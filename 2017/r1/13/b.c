/* UESTC 2017 Summer Training #13 Div.2. Problem B, by Abreto<m@abreto.net>. */
#include <stdio.h>

void putmin(int n, int s)
{
    if(1 == n) putchar(s+'0');
    else
    {
        int i = 0;
        for(i = 0;i < 10;++i)
            if( s-i >= 0 && s-i <= 9*(n-1) )
            {
                putchar(i+'0');
                putmin(n-1, s-i);
                break;
            }
    }
}

void putmax(int n, int s)
{
    if(1 == n) putchar(s+'0');
    else
    {
        int i = 0;
        for(i = 9;i >= 0;--i)
            if(s-i >= 0 && s-i <= 9*(n-1))
            {
                putchar(i+'0');
                putmax(n-1, s-i);
                break;
            }
    }
}

void proccess(int n, int s)
{
    if(0 == s)
    {
        if(1 == n)
            puts("0 0");
        else
            puts("-1 -1");
    } else {
        if(s > 9*n) puts("-1 -1");
        else
        {
            int i = 0;
            for(i = 1;i < 10;++i)
                if(s-i >= 0 && s-i <= 9*(n-1) )
                {
                    putchar(i+'0');
                    putmin(n-1,s-i);
                    break;
                }
            putchar(' ');
            for(i = 9;i > 0;--i)
                if(s-i >= 0 && s-i <= 9*(n-1))
                {
                    putchar(i+'0');
                    putmax(n-1,s-i);
                    break;
                }
            puts("");
        }
    }
}

int main(void)
{
    int T = 0, n = 0, s = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d %d", &n, &s);
        proccess(n, s);
    }
    return 0;
}
