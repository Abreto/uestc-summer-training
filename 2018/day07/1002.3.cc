/* Multi-Univ #1. 1002 */
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <utility>
#include <set>

#define MAXN    100001

using namespace std;
typedef pair<int,int> pii;
#define mp make_pair
#define fi first
#define se second

pii dp[MAXN<<1][2], tmp[MAXN<<1][2];    /* 0 for max left(fi), 1 for max unclosed(se) */

int n;
pii ss[MAXN];

int concat(pii l, pii r, pii &ret)
{
    int ans = min(l.se, r.fi);
    ret.fi = l.fi + max(0, r.fi - l.se);
    ret.se = r.se + max(0, l.se - r.fi);
     printf("(%d,%d) %d gened by (%d,%d) (%d,%d)\n", ret.fi, ret.se, ans, l.fi,l.se,r.fi,r.se);
    return (ans<<1);
}

int ret;
set<int> calculated;
set<int> expanded;
void chmax(int ans, pii candidate)
{
    if(candidate.fi > dp[ans][0].fi) tmp[ans][0] = candidate;
    if(candidate.se > dp[ans][1].se) tmp[ans][1] = candidate;
    ret = max(ret, ans);
}
void expand(int base, pii src, pii tocat)
{
    pii dest;
    int delta = concat(src, tocat, dest);
    expanded.insert(base + delta);
    chmax(base+delta, dest);
    delta = concat(tocat, src, dest);
    expanded.insert(base + delta);
    chmax(base+delta, dest);
}
#define MAX_CONSIDERED 100
int do_dp(void)
{
    int i;
    ret = 0;
    for(i = 0;i < (n<<1);i++) dp[i][0] = dp[i][1] = mp(0,0);
    calculated.clear();
    calculated.insert(0);
    for(i = 0;i < n;i++)
    {
         printf("expand %d,%d\n", ss[i].fi, ss[i].se);
        expanded.clear();
        for(auto x : calculated)
        {
            expand(x, dp[x][0], ss[i]);
            expand(x, dp[x][1], ss[i]);
        }
        calculated = expanded;
        for(auto x : calculated)
        {
            dp[x][0] = tmp[x][0];
            dp[x][1] = tmp[x][1];
        }
    }
    return ret;
}

bool compar(const pii &x, const pii &y)
{
    return max(x.fi, x.se) < max(y.fi, y.se);
}

char line[100010];
void proc(void)
{
    int i, j;
    int ans = 0;
    scanf("%d", &n);
    for(j = 0;j < n;j++)
    {
        int l;
        scanf("%s", line); l = strlen(line);
        int left = 0, unclosed = 0;
        int balanced = 0;
        for(i = 0;i < l;i++)
        {
            assert(line[i] == '(' || line[i] == ')');
            if('(' == line[i]) unclosed++;
            else
            {
                if(unclosed > 0) { unclosed--; balanced++; }
                else left++;
            }
        }
        ans += (balanced<<1);
        ss[j] = mp(left, unclosed);
    }
    sort(ss, ss+n, compar);
    ans += do_dp();
    printf("%d\n", ans);
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while(T--) proc();
    return 0;
}
