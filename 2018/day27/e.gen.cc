#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

int range(int L, int R)
{
    int w = R - L + 1;
    return L + (random() % w);
}

void onecase(void)
{
    int n = 10000;
    puts("10000 10000");
    while (n--)
        printf("%d ", range(1, 100000));
    puts("");
}

int main(void)
{
    int t = 3;
    srandom(time(NULL));
    puts("3");
    while (t--) onecase();
    return 0;
}
