/* UESTC 2017 Summer Training #4 Div.2. Problem E, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN    100010

int K;
char boards[MAXN];
int nboards;
int redidx[MAXN];
int nreds;

int bfind(int x)
{
    int l = 0, r = nreds-1;
    while(l < r)
    {
        int mid = (l+r)>>1;
        if( redidx[mid] > x )
            r = mid - 1;
        else if (redidx[mid] < x)
            l = mid + 1;
        else
            return mid;
    }
    return l;
}

int main(void)
{
    int i = 0, j = 0;

    scanf("%d", &K);
    scanf("%s", boards);
    nboards = strlen(boards); nreds = 0;
    for(i = 0;i < nboards;++i)
        if('1' == boards[i])
            redidx[nreds++] = i+1;
    for(j = 0;j < nboards;j += K)
        for(i = 0;i < nreds;++i)
        {
            int wanted = redidx[i] + j + 1;
            int w = bfind(wanted);
            if(wanted > nboards) break;
            if(w >= 0 && w < nreds && w != i && redidx[w] == wanted)
            {
                printf("%d %d\n", redidx[i], wanted);
                exit(EXIT_SUCCESS);
            }
        }
    printf("0 0\n");
    return 0;
}
