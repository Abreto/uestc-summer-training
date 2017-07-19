/* UESTC 2017 Summer Training #10 Div.2. Problem B, by Abreto<m@abreto.net>. */
#include <stdio.h>

int gird[4][4];

void handle(int t)
{
    int i = 0, j = 0, k = 0;
    int l = 0;
    if(0 == t)
    {
        for(i = 0;i < 4;++i)
        {
            k = 0;
            for(j = 0;j < 4;++j)
                if(gird[i][j])
                {
                    for(l = j+1;0==gird[i][l] && l < 4;++l);
                    if(l < 4 && gird[i][j]==gird[i][l])
                    {
                        gird[i][k] = gird[i][j]*2;
                        j = l;
                    } else {
                        gird[i][k] = gird[i][j];
                        j = l-1;
                    }
                    k++;
                }
            for(k;k<4;++k)
                gird[i][k] = 0;
        }
    } else if (2 == t) {
        for(i = 0;i < 4;++i)
        {
            k = 3;
            for(j = 3;j >= 0;--j)
                if(gird[i][j])
                {
                    for(l = j-1;0==gird[i][l] && l>=0;--l);
                    if(l>=0 && gird[i][j]==gird[i][l])
                    {
                        gird[i][k] = gird[i][j]*2;
                        j = l;
                    } else {
                        gird[i][k] = gird[i][j];
                        j = l+1;
                    }
                    k--;
                }
            for(k;k>=0;--k)
                gird[i][k] = 0;
        }
    } else if (1 == t) {
        for(j = 0;j < 4;++j)
        {
            k = 0;
            for(i = 0;i < 4;++i)
                if(gird[i][j])
                {
                    for(l = i+1;0==gird[l][j] && l < 4;++l);
                    if(l < 4 && gird[i][j]==gird[l][j])
                    {
                        gird[k][j] = gird[i][j]*2;
                        i = l;
                    } else {
                        gird[k][j] = gird[i][j];
                        i = l-1;
                    }
                    k++;
                }
            for(k;k<4;++k)
                gird[k][j] = 0;
        }
    } else {
        for(j = 0;j < 4;++j)
        {
            k = 3;
            for(i = 3;i >= 0;--i)
                if(gird[i][j])
                {
                    for(l = i-1;0==gird[l][j] && l >= 0;--l);
                    if(l >= 0 && gird[i][j]==gird[l][j])
                    {
                        gird[k][j] = gird[i][j]*2;
                        i = l;
                    } else {
                        gird[k][j] = gird[i][j];
                        i = l+1;
                    }
                    k--;
                }
            for(k;k>=0;--k)
                gird[k][j] = 0;
        }
    }
}

int main(void)
{
    int i = 0, j = 0;
    int d = 0;
    for(i = 0;i < 4;++i)
        for(j = 0;j < 4;++j)
            scanf("%d", &(gird[i][j]));
    scanf("%d", &d);
    handle(d);
    for(i = 0;i < 4;++i)
    {
        printf("%d", gird[i][0]);
        for(j = 1;j < 4;++j) printf(" %d", gird[i][j]);
        puts("");
    }
    return 0;
}
