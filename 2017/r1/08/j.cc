/* UESTC 2017 Summer Training #8 Div.2. Problem J, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <set>

using namespace std;

#define MAXL 128

typedef long long int ll;

int w, h;
ll gird[MAXL][MAXL];
ll tmp[MAXL][MAXL];
int d[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

void blur(void)
{
    int i = 0, j = 0, k = 0;
    for(i = 0;i < h;++i)
        for(j = 0;j < w;++j)
        {
            tmp[i][j] = gird[i][j];
            for(k = 0;k < 8;++k)
                tmp[i][j] += gird[(h+i+d[k][0])%h][(w+j+d[k][1])%w];
        }
    for(i = 0;i < h;++i)
        for(j = 0;j < w;++j)
            gird[i][j] = tmp[i][j];
}

int main(void)
{
    int i = 0, j = 0;
    int b = 0;
    set<ll> gray;
    scanf("%d%d%d", &w, &h, &b);
    for(i = 0;i < h;++i)
        for(j = 0;j < w;++j)
            scanf("%lld", &(gird[i][j]));
    while(b--) blur();
    for(i = 0;i < h;++i)
        for(j = 0;j < w;++j)
            gray.insert(gird[i][j]);
    printf("%lu\n", gray.size());
    return 0;
}
