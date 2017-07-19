/* UESTC 2017 Summer Training #11 Div.2. Problem E, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define INPUTFILE   "figure.in"
#define OUTPUTFILE  "figure.out"
#define MAXL    32

int H, W, N;
int gird[MAXL][MAXL];

#define CHECK   if(nspots>=N) goto output

void proccess(int caseid)
{
    int i = 0, j = 0;
    int nspots = 0;
    scanf("%d%d%d", &H, &W, &N);
    for(i = 0;i < H;++i)
        for(j = 0;j < W;++j)
            gird[i][j] = '.';
    for(i = 1;i < H-1;++i)
        for(j = 2-(i&1);j < W-1;j += 2)
        {
            gird[i][j] = '#';
            nspots++;
            CHECK;
        }
output:
    if(caseid) puts("");
    if(nspots<N) {puts("Impossible");return;}
    for(i = 0;i < H;++i)
    {
        for(j = 0;j < W;++j)
            putchar(gird[i][j]);
        puts("");
    }
}

int main(void)
{
    int T = 0, ncase = 0;
    //freopen(INPUTFILE, "r", stdin);
    //freopen(OUTPUTFILE, "w+", stdout);
    scanf("%d", &T);
    while(T--) proccess(ncase++);
    return 0;
}
