/*  */
#include <cstdio>

using namespace std;

#define MAXN    (100001)

int n, m;
int brokenx[MAXN], brokeny[MAXN];
int calculated[MAXN];

int main(void)
{
    int i, j, x, y;
    int ans = 0;
    scanf("%d%d", &n, &m);
    while(m--)
    {
        scanf("%d%d", &x, &y);
        brokenx[x] = 1;
        brokeny[y] = 1;
    }
    for(i = 1;i <= n;i++)
        if(0 == calculated[i])
        {
            j = n - i + 1;
            calculated[i] = calculated[j] = 1;
            if(i == j)
            {
                if(brokenx[i] && brokeny[i])
                {
                    ans += 0;
                } else {
                    ans += 1;
                }
            } else {
                ans += 4;
                ans -= brokenx[i];
                ans -= brokenx[j];
                ans -= brokeny[i];
                ans -= brokeny[j];
            }
        }
    printf("%d\n", ans);
    return 0;
}
