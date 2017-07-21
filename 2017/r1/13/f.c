/* UESTC 2017 Summer Training #13 Div.2. Problem F, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <string.h>

/*
1..N
c..V
f[j]=max{f[j],f[j-c[i]]+w[i]}
*/

int max(int a, int b) {return (a>b)?a:b;}

#define MAXD    16
int d;
int purec[MAXD], w[MAXD];
int c[MAXD];
int f[1000000];

int dp(int V)
{
    int i = 0, j = 0;
    V /= 1000;
    memset(f, 0, (V+1)*sizeof(int));
    for(i = 0;i < d;++i)
        for(j = c[i];j <= V;++j)
            f[j] = max(f[j], f[j-c[i]]+w[i]);
    return f[V];
}

void proccess(void)
{
    int i = 0;
    int amount = 0, years = 0;
    scanf("%d %d", &amount, &years);
    scanf("%d", &d);
    for(i = 0;i < d;++i)
    {
        scanf("%d %d", purec+i, w+i);
        c[i] = purec[i]/1000;
    }
    while(years--)
        amount += dp(amount);
    printf("%d\n", amount);
}

int main(void)
{
    int N = 0;
    scanf("%d", &N);
    while(N--) proccess();
    return 0;
}
