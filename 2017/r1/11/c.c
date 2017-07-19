/* UESTC 2017 Summer Training #11 Div.2. Problem C, by Abreto<m@abreto.net>. */
#include <stdio.h>

int min(int a, int b){return (a<b)?a:b;}
int max(int a, int b){return (a>b)?a:b;}

#define MAXN    1000001

#define INPUTFILE   "dales.in"
#define OUTPUTFILE  "dales.out"

int N;
int a[MAXN];
int li[MAXN], ri[MAXN];
int ld[MAXN], rd[MAXN];

void proccess(void)
{
    int i = 0;
    int h = 0, d = 0;
    scanf("%d", &N);
    for(i = 0;i < N;++i)
        scanf("%d", a+i);
    li[0] = ld[0] = 0;
    for(i = 1;i < N;++i)
        if(a[i] > a[i-1])
        {
            li[i] = li[i-1]+1;
            ld[i] = 0;
        }
        else if(a[i] < a[i-1])
        {
            li[i] = 0;
            ld[i] = ld[i-1]+1;
        }
        else li[i]=ld[i]=0;
    ri[N-1] = rd[N-1] = 0;
    for(i = N-2;i >= 0;i--)
        if(a[i] < a[i+1])
        {
            ri[i] = 0;
            rd[i] = rd[i+1]+1;
        }
        else if(a[i] > a[i+1])
        {
            ri[i] = ri[i+1]+1;
            rd[i] = 0;
        }
        else ri[i]=rd[i]=0;
    for(i = 0;i < N;++i)
    {
        h = max(h, min(li[i],ri[i]));
        d = max(d, min(ld[i],rd[i]));
    }
    printf("%d %d\n", h, d);
}

int main(void)
{
    int T = 0;
    freopen(INPUTFILE, "r", stdin);
    freopen(OUTPUTFILE, "w+", stdout);
    scanf("%d", &T);
    while(T--) proccess();
    return 0;
}
