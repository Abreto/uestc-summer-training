/* UESTC 2017 Summer Training Round2 #03 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <cstdio>
#include <set>

using namespace std;

typedef long long int ll;

int np = 6;
int p[7] = {2,3,5,7,11,13};
int maxe[7] = {30,12,5,3,1,1};
ll ii[17] = {0,0,4,27,0,3125,0,823543,0,0,0,285311670611,0,302875106592253,0,0,0};
set<ll> ans;
int k = 0;
ll r = 0;

int min(int a, int b){return (a<b)?a:b;}
ll mypow(ll a, ll b)
{
    ll ret = 1, base = a;
    while(b)
    {
        if(b&1) ret *= base;
        base *= base;
        b >>= 1;
    }
    return ret;
}

void dfs(int pos, int rem, ll val)
{
    if(0 == rem)
    {
        ans.insert(val);
    } else if (pos < np) {
        int i = 0;
        for(i = 0;i <= min(rem,maxe[pos]);++i)
        {
            ll delta = mypow(ii[p[pos]],i);
            ll nval = val * delta;
            if(nval/val != delta || nval > r)
                return;
            dfs(pos+1, rem-i, nval);
        }
    }
}

int main(void)
{
    scanf("%d %lld", &k, &r);
    dfs(0, k, 1);
    printf("%lu%s", ans.size(), ans.size()?"\n":"");
    for(auto n:ans)
        printf("%lld ", n);
    puts("");
    return 0;
}
