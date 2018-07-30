#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

#define MAXN    24
typedef int ll;
typedef pair<ll,ll> pll;
#define mp make_pair
#define inf 0x7fffffff

int n, S;
pll f[1<<MAXN]; /* (min number, min used) */
ll w[MAXN];

int main(void)
{
    int i, j;
    scanf("%d%d", &n, &S);
    for(i = 0;i < n;i++) scanf("%d", w+i);
    for(i = 0;i < (1<<n);i++)
        f[i] = mp(inf, 0);
    f[0] = mp(1,0);
    for(i = 0;i < (1<<n);i++)
    {
        for(j = 0;j < n;j++)
        {
            if(0 == ((i >> j) & 1))
            {
                ll need = f[i].second + w[j];
                pll candidate;
                if(need > S)
                {
                    candidate = mp(f[i].first+1, w[j]);
                } else {
                    candidate = mp(f[i].first, need);
                }
                f[i | (1<<j)] = min(f[i | (1<<j)], candidate);
            }
        }
    }
    printf("%d\n", f[(1<<n)-1].first);
    return 0;
}
