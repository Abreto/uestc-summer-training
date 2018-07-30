#include <cstdio>

using namespace std;

int a[1024] = {0,1,1};

int main(void)
{
    int s = 2;
    for(int i = 3;i < 1024;i++)
    {
        a[i] = a[i-a[i-1]] + a[i-1-a[i-2]];
        s += a[i];
        printf("%d: %d,%d\n", i, a[i], s);
    }
    return 0;
}
