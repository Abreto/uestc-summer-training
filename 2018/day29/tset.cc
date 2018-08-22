#include <cstdio>

using namespace std;

int f[16][16][16*16];

int main(void)
{
    int n;
    scanf("%d", &n);
    f[1][0][0] = f[1][1][0] = 1;
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
            for (int k = 0; k <= i * i; k++)
            {
                int x = f[i-1][j][k];
                if (0 == x) continue;
                f[i][j][k+j] += (2*j+1) * x;
                if (j) f[i][j-1][k+j] += j*j * x;
                f[i][j+1][k+j] += f[i-1][j][k];
            }
        printf("%d:\n", i);
        for (int j = 0; j <= i; j++)
        {
            for (int k = 0; k <= i * i; k++)
                printf("%d ", f[i][j][k]);
            puts("");
        }
    }
    return 0;
}
