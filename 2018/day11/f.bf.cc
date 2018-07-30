#include <cstdio>
#include <cstdlib>
#include <set>

using namespace std;

#define MAXN    256

int mat[MAXN][MAXN];

int n;

int sum[MAXN];
int check()
{
    int i = 0, j = 0;
    for(i = 0;i < (n<<1);i++)
    {
        sum[i] = 0;
    }
    for(i = 0;i < n;i++)
        for(j = 0;j < n;j++)
        {
            sum[i] += mat[i][j];
            sum[j+n] += mat[i][j];
        }
    sort(sum, sum+(n<<1));
    int *sumr = unique(sum, sum+(n<<1));
    return (sumr == sum+(n<<1));
}

void dfs(int pos)
{
    if(n*n == pos)
    {
        if(check())
        {
            puts("possible");
            for(int i = 0;i < n;i++)
            {
                for(int j = 0;j < n;j++)
                    printf("%d ", mat[i][j]);
                puts("");
            }
            exit(0);
        }
    } else {
        for(int i = -1;i < 2;i++)
        {
            mat[pos / n][pos % n] = i;
            dfs(pos+1);
        }
    }
}

int main(void)
{
    scanf("%d", &n);
    dfs(0);
    puts("impossible");
    return 0;
}
