#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int maxn = 100;

int p[maxn];
vector< vector<int> > tab;

int main(void)
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) p[i] = i;
    int cnt = 1;
    do
    {
        int s = 0;
        for (int i = 1; i <= n; i++) s += abs(i - p[i]);
        printf("%s%d: ", (s < 10) ? "0":"", s);
        vector<int> v;
        for (int i = 1; i <= n; i++) printf("%d ", p[i]);
        puts("");
    }while(next_permutation(p + 1, p + n + 1));
    return 0;
}
