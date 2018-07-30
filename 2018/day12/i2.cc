#include <cassert>
#include <cstdio>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;
#define pb push_back
typedef pair<int,int> pii;
#define mp make_pair
#define fi first
#define se second

#define MAXN    (10010)

void ask(int n)
{
    printf("%d\n", n);
    fflush(stdout);
}

int w[16];
void myinit(void)
{
    for(int i = 0;i < 11;i++)
        w[i] = (1<<(2*i));
}

int n, k;
int sz[MAXN];
int peak[MAXN];

int get_median(void)
{
    long long int tot = 0;
    long long int passed = 0;
    vector<pii> vp;
    for(int i = 0;i < n;i++)
        if(sz[i])
        {
            tot += w[sz[i]];
            vp.pb(mp(peak[i], w[sz[i]]));
        }
    sort(vp.begin(), vp.end());
    tot >>= 1;
    for(auto m : vp)
    {
        long long int np = passed + m.se;
        if(passed <= tot && tot <= np)
            return m.fi;
        passed = np;
    }
    return -1;
}

int main(void)
{
    int i;
    myinit();
    scanf("%d%d", &n, &k);
    for(i = 0;i < n;i++)
    {
        scanf("%d", peak+i);
        sz[i] = k;
    }
    while(1)
    {
        char res[8];
        int x = get_median();
        ask(x);
        assert(x >= 0);
        scanf("%s", res);
        if('E' == res[0]) break;
        else
        {
            for(i = 0;i < n;i++)
            {
                if(sz[i])
                {
                    if('<' == res[0]) sz[i] -= (peak[i] <= x);
                    else sz[i] -= (peak[i] >= x);
                }
                scanf("%d", peak+i);
            }
        }
    }
    return 0;
}
