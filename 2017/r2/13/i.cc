/* UESTC 2017 Summer Training #30 Div.2. Problem I, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif
typedef long long int ll;

int n, k;
vector< pair<ll,ll> > houses[2];

ll deliver(int id)
{
    int i = 0, j = 0;
    int nh = houses[id].size();
    ll ret = 0;
    sort(houses[id].begin(), houses[id].end());
    for(i = nh-1;i >= 0;i--)
    {
        if(houses[id][i].second > 0)
        {
            ll xi = houses[id][i].first, mi = houses[id][i].second;
            ll definitely = mi / k;
            ll rem = mi % k;
            ret += definitely * 2ll * xi;
            if(rem)
            {
                int lasthouse = i;
                int rest = k - rem;
                ret += xi;
                for(j = i-1;rest > 0 && j >= 0;j--)
                {
                    if(rest > houses[id][j].second)
                    {
                        rest -= houses[id][j].second;
                        houses[id][j].second = 0;
                        ret += (houses[id][lasthouse].first - houses[id][j].first);
                        lasthouse = j;
                    } else {
                        houses[id][j].second -= rest;
                        rest = 0;
                        ret += (houses[id][lasthouse].first - houses[id][j].first);
                        lasthouse = j;
                    }
                }
                ret += houses[id][lasthouse].first;
            }
        }
    }
    return ret;
}

int main(void)
{
    int i = 0;
    ll ans = 0;
    ll xi = 0, mi = 0;
    scanf("%d %d", &n, &k);
    for(i = 0;i < n;i++)
    {
        scanf("%lld %lld", &xi, &mi);
        if(xi > 0)
        {
            houses[0].push_back(make_pair(xi,mi));
        } else if (xi < 0) {
            houses[1].push_back(make_pair(-xi,mi));
        }
    }
    ans = deliver(0) + deliver(1);
    printf("%lld\n", ans);
    return 0;
}
