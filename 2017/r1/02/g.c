/* UESTC 2017 Summer Training #2 Div.2. Problem D, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define ISDIGIT(x) ((x>='0')&&(x<='9'))
void readn(int *n)
{
    int c=0;*n=0;
    for(;!ISDIGIT(c);c=getchar());
    for(;ISDIGIT(c);c=getchar())*n=(*n)*10+c-'0';
}
void putn(int n)
{
    int ns[16]={0,n%10},nd=1;
    while(n/=10)ns[++nd]=n%10;
    while(nd)putchar(ns[nd--]+'0');
}

int min(int a, int b) {return (a<b)?a:b;}
int max(int a, int b) {return (a>b)?a:b;}

#define MAXN    10001

int n;
int child[MAXN][2];
int nchild[MAXN];

int dp(int mc)
{
    if(0 == nchild[mc])
        return 1;
    else if(1 == nchild[mc])
        return dp(child[mc][0]);
    else
    {
        int a = dp(child[mc][0]), b = dp(child[mc][1]);
        return max(min(a,b)+1, max(a,b));
    }
}

int main(void)
{
    int i = 0;
    int ai = 0;
    while(EOF != scanf("%d", &n) && n)
    {
        for(i = 1;i <= n;++i)
        {
            nchild[i] = 0;
        }
        for(i = 1;i < n;++i)
        {
            readn(&ai);
            child[ai][nchild[ai]++] = i+1;
        }
        printf("%d\n", dp(1));
    }
    return 0;
}
