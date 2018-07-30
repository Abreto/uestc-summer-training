#include <cstdio>

using namespace std;

#define MAXN    256

int n;
int mat[MAXN][MAXN];

void proc(void)
{
    scanf("%d", &n);
    if(1 & n) puts("impossible");
    else
    {
        puts("possible");
        for(int i = 0;i < n;i++)
        {
            for(int j = 0;j < n;j++)
            {
                if(j) putchar(' ');
                if(i+j < n-1) printf("1");
                else if (i + j > n-1) printf("-1");
                else printf("%d", i < j);
            }
            puts("");
        }
    }
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while(T--) proc();
    return 0;
}
