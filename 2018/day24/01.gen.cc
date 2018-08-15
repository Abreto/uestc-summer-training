#include <cstdio>
#include <cstdlib>

using namespace std;

int main(void)
{
    puts("400");
    for (int i = 0;i < 400;i++)
        printf("100000 100000 %ld\n", random() % (100001));
    return 0;
}
