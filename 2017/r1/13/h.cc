/* UESTC 2017 Summer Training #13 Div.2. Problem H, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cstring>
#include <string>
#include <map>

using namespace std;

map<string,int> day;

char pure[5][4][64];

char table[5][4][8][16];
int nrow[5];

void init(void)
{
    day["Tuesday"] = 1;
    day["Thursday"] = 2;
    day["Saturday"] = 3;
}

void read(void)
{
    int n = 0;
    char name[64] = {0};
    char dayofweek[16] = {0}; int ith = 0;
    scanf("%d", &n); getchar();
    while(n--)
    {
        fgets(name, 64, stdin); name[strlen(name)-1] = 0;
        scanf("%s %d", dayofweek, &ith); getchar();
        strcpy(pure[ith][day[dayofweek]], name);
    }
}

void handle(void)
{
    int i = 0, j = 0;
    for(i = 1;i < 5;++i)
        for(j = 1;j < 4;++j)
        {
            int k = 0, l = 0;
            int len = strlen(pure[i][j]);
            int curow = 0, rem = 10;
            for(k = 0;k < len;curow++)
            {
                int max2print = 0;
                for(l = 0;l <= 10 && (k+l)<=len;++l)
                    if (' ' == pure[i][j][k+l] || 0 == pure[i][j][k+l])
                        max2print = l;
                pure[i][j][k+max2print] = 0;
                strcpy(table[i][j][curow], pure[i][j]+k);
                for(l=max2print;l < 10;++l)
                    table[i][j][curow][l] = ' ';
                table[i][j][curow][10] = 0;
                k = k+max2print+1;
            }
            if(curow > nrow[i]) nrow[i] = curow;
            /*while(k < len)
            {
                if(curow+1>nrow[i]) nrow[i]=curow+1;
                if(len-k<=rem)
                {
                    strcpy(table[i][j][curow]+10-rem, pure[i][j]+k);
                    k = len;
                } else {
                    int l = k;
                    for(l=k;pure[i][j][l]!=' ';l++);
                }
            }*/
        }
}

void putchrs(int ch, int n)
{
    while(n--) putchar(ch);
}

void print(void)
{
    int i = 0, j = 0, k = 0;
    putchar('+');
    for(i = 0;i < 3;++i)
    {
        putchrs('-',10);putchar('+');
    } puts("");
    for(i = 1;i < 5;++i)
    {
        for(k = 0;k < nrow[i];++k)
        {
            putchar('|');
            for(j = 1;j < 4;++j)
            {
                printf("%s|", (0==table[i][j][k][0])?"          ":table[i][j][k]);
            }
            puts("");
        }
        if(0 == nrow[i])
        {
            putchar('|');
            for(k = 0;k < 3;++k)
            {
                putchrs(' ', 10);putchar('|');
            }
            puts("");
        }
        putchar('+');for(k = 0;k < 3;++k){putchrs('-',10);putchar('+');}puts("");
    }
}

int main(void)
{
    init();
    read();
    handle();
    print();
    return 0;
}
