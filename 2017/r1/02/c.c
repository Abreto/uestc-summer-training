/* UESTC 2017 Summer Training #2 Div.2. Problem C, by Abreto<m@abreto.net>. */
#include <stdio.h>

int n;
char gird[128][128];

void proccess(void)
{
    int i = 0, j = 0, k = 0;
    int cnt = 0;
    scanf("%d", &n);
    for(i = 0;i < n;++i)
        scanf("%s", gird[i]);
    
    for(i = 0;i < n/2;++i)
    {
        int ip = n-1-i;
        j = i;
        {
            int jp = n-1-j;
            int appear[256] = {0};
            int maxappear = 0;
            int cords[4][2] = {{i,j}, {ip,j}, {i,jp}, {ip,jp}};
            for(k = 0;k < 4;++k)
            {
                appear[gird[cords[k][0]][cords[k][1]]]++;
                if(appear[gird[cords[k][0]][cords[k][1]]] > maxappear)
                    maxappear = appear[gird[cords[k][0]][cords[k][1]]];
            }
            cnt += (4-maxappear);
        }
        for(j = i+1;j < n/2;++j)
        {
            int jp = n-1-j;
            int appear[256] = {0};
            int maxappear = 0;
            int cords[4][2] = {{i,j}, {ip,j}, {i,jp}, {ip,jp}};
            for(k = 0;k < 4;++k)
            {
                appear[gird[cords[k][0]][cords[k][1]]]++;
                if(appear[gird[cords[k][0]][cords[k][1]]] > maxappear)
                    maxappear = appear[gird[cords[k][0]][cords[k][1]]];
                appear[gird[cords[k][1]][cords[k][0]]]++;
                if(appear[gird[cords[k][1]][cords[k][0]]] > maxappear)
                    maxappear = appear[gird[cords[k][1]][cords[k][0]]];
            }
            cnt += (8-maxappear);
        }

        {
            int appear[256] = {0};
            int maxappear = 0;
            int cords[4][2] = {{i,n/2}, {ip,n/2}, {n/2, i}, {n/2, ip}};
            for(k = 0;k < 4;++k)
            {
                appear[gird[cords[k][0]][cords[k][1]]]++;
                if(appear[gird[cords[k][0]][cords[k][1]]] > maxappear)
                    maxappear = appear[gird[cords[k][0]][cords[k][1]]];
            }
            cnt += (4-maxappear);
        }
    }
    printf("%d\n", cnt);
}

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--) proccess();
    return 0;
}
