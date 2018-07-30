#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int range(int l, int r)
{
    int w = r - l + 1;
    return l + (rand() % w);
}

int main(void)
{
    int T = 10;
    srand(time(NULL));
    printf("%d\n", T);
    while(T--)
    {
        int n = 50, m = 10000;
        puts("50 10000");
        while(m--)
        {
            int ui = range(1,n);
            int vi = range(1,n);
            while(ui==vi) vi = range(1,n);
            printf("%d %d %d\n", ui, vi, range(1,10000));
        }
        int q = 100000;
        puts("100000");
        while(q--)
        {
            printf("%d %d %d\n", range(1,n), range(1,n), range(1,10000));
        }
    }
    return 0;
}
