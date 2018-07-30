#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long int ll;
typedef pair<ll,ll> pll;    /* (wi, -vi) */
#define mp make_pair

#define MAXN    (1<<9)
#define MAXM    (30000000)
#define NSTATE  (5000000)

ll n;
ll W;
ll ans;
pll goods[MAXN];
// 67108864, 33554432
ll f[MAXM+1];
// 37108864, 15000000
int nprev;
pll prevs[NSTATE], extend[NSTATE], tmp[NSTATE];

void updans(ll candidate)
{
    ans = max(ans, candidate);
}

void naive_solver(void)
{
    int i, j;
    for(i = 0;i < n;i++)
    {
        ll wi = goods[i].first, vi = -goods[i].second;
        for(j = W;j >= wi;j--)
        {
            f[j] = max(f[j], f[j-wi]+vi);
        }
    }
    for(i = 0;i <= W;i++) updans(f[i]);
}

void rough_solve(void)
{
    ll r = ((double)W) * ((double)n) / 2e8;
    r = max(r, W / MAXM);
    r = max(r, 1ll);
    ll mw = W / r;
    int i, j;
    for(i = 0;i < n;i++)
    {
        ll wi = goods[i].first / r, vi = -goods[i].second;
        for(j = mw;j >= wi;j--)
        {
            f[j] = max(f[j], f[j-wi]+vi);
        }
    }
    for(i = 0;i <= mw;i++) updans(f[i]);
}

int cnt;
void expand(int id)
{
    if(cnt++ > 3e8) return;
    int i, j;
    ll wi = goods[id].first, vi = -goods[id].second;
    int next = 0, ntmp = 0;

    for(i = 0;i < nprev;i++)
    {
        if( prevs[i].first + wi < W )
        {
            extend[next++] = mp(prevs[i].first+wi, prevs[i].second-vi);
        }
    }
    
    i = 0, j = 0;
    while(i < nprev || j < next)
    {
        if(i < nprev && j < next)
        {
            if( prevs[i] < extend[j] )
            {
                tmp[ntmp++] = prevs[i++];
            } else {
                tmp[ntmp++] = extend[j++];
            }
        }
        if(i < nprev)
        {
            tmp[ntmp++] = prevs[i++];
        }
        if(j < next)
        {
            tmp[ntmp++] = extend[j++];
        }
    }
    
    nprev = 0;
    for(i = 0;i < ntmp && nprev < NSTATE;i++)
    {
        if(0 == nprev || tmp[i].second < prevs[nprev-1].second )
        {
            prevs[nprev++] = tmp[i];
        }
    }

    updans(-prevs[nprev-1].second);
}

void modify(void)
{
    prevs[0] = mp(0,0);
    nprev = 1;
    random_shuffle(goods, goods+n);
    for(int i = 0;i < n;i++) expand(i);
}

int main(void)
{
    int i; ll wi, vi;
    scanf("%lld%lld", &n, &W);
    if(0 == n) return 0 * puts("0");
    for(i = 0;i < n;i++)
    {
        scanf("%lld%lld", &wi, &vi);
        goods[i] = mp(wi, -vi);
    }
    if(W <= MAXM && n*W <= 3.5e8) naive_solver();
    else
    {
        rough_solve();
        modify();
    }
    printf("%lld\n", ans);
    return 0;
}
