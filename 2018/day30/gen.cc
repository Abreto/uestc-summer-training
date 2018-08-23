#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int range(int L, int R)
{
    int w = R - L + 1;
    return L + (random() % w);
}

int main(void)
{
    srandom(time(NULL));
    int N = 100, K = 10;
    int T = range(1, K);
    printf("100 10 %d\n", T);
    for (int i = 1; i <= N; i++)
    {
        int zero = range(1, K+1);
        for (int j = 1; j <= K + 1; j++)
        {
            if (j == zero) printf("0 ");
            else printf("%d ", range(1, 1e9));
        }
        puts("");
    }
    return 0;
}
