/* UESTC 2017 Summer Training #9 Div.2. Problem B, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define INPUTFILE   "input.txt"
#define OUTPUTFILE  "output.txt"

int n, m;
char gird[128][128];
int ans;

void calc(void)
{
    int i = 0, j = 0, k = 0;
    int d[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};
    for(i = 1;i <= n;++i)
        for(j = 1;j <= m;++j)
            if('0' != gird[i][j])
            {
                ans += 2;
                for(k = 0;k < 4;++k)
                {
                    int ni = i+d[k][0], nj = j+d[k][1];
                    if(ni < 1 || ni > n || nj < 1 || nj > m)
                        ans += (gird[i][j]-'0');
                    else if (gird[ni][nj] < gird[i][j])
                        ans += (gird[i][j]-gird[ni][nj]);
                }
            }
}

void proccess(void)
{
    int i = 0, j = 0;
    scanf("%d%d", &n, &m);
    for(i = 1;i <= n;++i)
        scanf("%s", gird[i]+1);
    calc();
    printf("%d\n", ans);
}

int main(void)
{
    //freopen(INPUTFILE, "r", stdin);
    //freopen(OUTPUTFILE, "w+", stdout);
    proccess();
    return 0;
}
