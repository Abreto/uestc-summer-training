#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    srandom(time(NULL));
    int n = (random() % 18) + 1;
    printf("%d\n", n);
    for(int i = 0;i < (1<<n);i++)
        putchar('0' + (random() & 1));
    puts("");
    return 0;
}
