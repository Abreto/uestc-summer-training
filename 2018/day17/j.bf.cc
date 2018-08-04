#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

typedef unsigned uint;
typedef unsigned long long ull;

uint x, y, z;
uint tang()
{
    uint t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;
    return z;
}

ull gcd(ull m, ull n)
{
    return (0 == n) ? m : gcd(n, m%n);
}

uint a[10000000];

int main(void)
{
    int n;
    scanf("%d%u%u%u", &n, &x, &y, &z);
    for(int i = 1;i <= n;i++)
    {
        a[i] = tang();
    }
    sort(a+1, a+n+1);
    /*for(int i = 1;i <= n;i++)
    {
        printf("%u: ", a[i]);
        for(int j = 1;j < i;j++)
            printf("%llu ", gcd(a[i], a[j]));
        puts("");
    }*/
    ull ans = 0;
    int ansi, ansj;
    for(int i = 1;i <= n;i++)
    {
        for(int j = 1;j <= n;j++)
        {
            if(i == j) continue;
            ull candidate = 1ull * a[i] / gcd(a[i], a[j]) * a[j];
            if(candidate > ans)
            {
                ans = candidate;
                ansi = i;
                ansj = j;
            }
        }
    }
    printf("%llu: [%d](%u)x[%d](%u)\n", ans, n-ansi, a[ansi], n-ansj, a[ansj]);
    return 0;
}
