/* UESTC 2017 Summer Training #2 Div.2. Problem D, by Abreto<m@abreto.net>. */
#include <stdio.h>

int gird[1024][1024];

int ox, oy;
int curx, cury;
int dire;

void oxoy(int oox, int ooy)
{
    curx = ox = oox;
    cury = oy = ooy;
}
void nextline(void)
{
    cury += dire;
    curx = ox;
}
void putone(int c)
{
    gird[curx][cury] = c;
    curx += dire;
}
void putsth(int c, int n)
{
    while(n--) putone(c);
}

#define putstar(n)  (putsth('*',(n)))
#define putspace(n) (putsth(' ',(n)))

int lg(int x)
{
    int ret = 0;
    while(x)
    {
        x >>= 1;
        ret++;
    }
    return (ret-1);
}

void draw(int N,int lux, int luy, int pd)
{
    int i = 0;
    int lgN = lg(N), N4p1 = N/4+1, N8m1 = N/8-1;

    oxoy(lux, luy); dire = pd;
    putstar(N); nextline();
    
    for(i = 0;i < N8m1;++i)
    {
        putstar(1);putspace(N-2);putstar(1);nextline();
    }
    putstar(1);putspace(N8m1);putstar(N/4);putspace(N/4);putstar(N/4);putspace(N8m1);putstar(1);nextline();
    for(i = 0;i < N4p1-2;++i)
    {
        putstar(1);putspace(N8m1);
        putstar(1);putspace(N/4-2);putstar(1);
        putspace(N/4);
        putstar(1);putspace(N/4-2);putstar(1);
        putspace(N8m1);putstar(1);
        nextline();
    }
    putstar(1);putspace(N8m1);putstar(N/4);putspace(N/4);putstar(N/4);putspace(N8m1);putstar(1);nextline();
    for(i = 0;i < N8m1;++i)
    {
        putstar(1);putspace(N-2);putstar(1);nextline();
    }

    if(N > 8)
    {
        for(i = 1;i < N/2;++i)
        {
            putstar(1);putspace(N-2);putstar(1); nextline();
        }
        putstar(N);
        draw(N/2, lux+pd*(N/4*3-1), luy+pd*(N-1), -pd);
    } else {
        putstar(1);putspace(1);putstar(4);putspace(1);putstar(1);nextline();
        for(i = 0;i < 2;++i)
        {
            putstar(1);putspace(1);putstar(1);putspace(2);putstar(1);putspace(1);putstar(1);nextline();
        }
        putstar(8); nextline();
    }
}

int main(void)
{
    int i = 0, j = 0;
    int N = 0;
    while(1)
    {
        scanf("%d", &N);
        if(N < 8) break;
        draw(N, 0, 0, 1);
        for(i = 0;i < N;++i)
        {
            for(j = 0;j < N;++j)
                printf("%c", gird[j][i]?gird[j][i]:' ');
            puts("");
        }
        puts("");
    }
    return 0;
}
