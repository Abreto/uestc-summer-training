#include <cstdio>
#include <vector>

using namespace std;

int main(void)
{
    vector<int> x;
    for(int i = 1;i < 10;i++) x.push_back(i);
    auto it = x.begin()+1;
    x.erase(it);
    for(;it != x.end();it++)
        printf("%d\n", *it);
    for(it = x.begin();it != x.end();it++)
        printf("%d\n", *it);
    return 0;
}
