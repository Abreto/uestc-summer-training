/* UESTC 2017 Summer Training #6 Div.2. Problem E, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define REP(x) for(x=0;x<10;++x)

int f[10][10];

int xo(int a, int b)
{
    return f[a][b];
}

int calc(int a, int b, int c, int d)
{
    return f[f[f[f[0][a]][b]][c]][d];
}
int check(int a, int b, int c, int d, int e)
{
    return f[calc(a,b,c,d)][e];
}
int judge(int a, int b, int c, int d, int e)
{
    int i = 0;
    REP(i){if(i!=a)if(!check(i,b,c,d,e))return 0;}
    REP(i){if(i!=b)if(!check(a,i,c,d,e))return 0;}
    REP(i){if(i!=c)if(!check(a,b,i,d,e))return 0;}
    REP(i){if(i!=d)if(!check(a,b,c,i,e))return 0;}
    REP(i){if(i!=e)if(!check(a,b,c,d,i))return 0;}
    if(a!=b&&!check(b,a,c,d,e))return 0;
    if(b!=c&&!check(a,c,b,d,e))return 0;
    if(d!=c&&!check(a,b,d,c,e))return 0;
    if(e!=d&&!check(a,b,c,e,d))return 0;
    return 1;
}

int main(void)
{
    int i = 0, j = 0, k = 0, l = 0;
    int cnt = 0;
    for(i = 0;i < 10;++i)
        for(j = 0;j < 10;++j)
            scanf("%d", &(f[i][j]));
    REP(i)REP(j)REP(k)REP(l)
    {
        int e = calc(i,j,k,l);
        if(!judge(i,j,k,l,e)) cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}
