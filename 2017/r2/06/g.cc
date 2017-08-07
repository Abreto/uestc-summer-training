/* UESTC 2017 Summer Training #22. Problem G, by Abreto<m@abreto.net> */
#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>
#include <utility>

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pli;
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif
#define mp(a,b) make_pair(a,b)

#define MAXN    200000
int N, K;
ll p[MAXN];

ll ans(void)
{
    priority_queue< pli, vector<pli>, greater<pli> > pq;
    sort(p, p+N);
    pq.push(mp(p[0],0));
    while(--K)
    {
        pli cur = pq.top(); pq.pop();
        if(N-1 == cur.second) continue;
        pq.push(mp(cur.first+p[cur.second+1], cur.second+1));
        pq.push(mp(cur.first+p[cur.second+1]-p[cur.second], cur.second+1));
    }
    return pq.top().first;
}

int main(void)
{
    int i = 0;
    scanf("%d %d", &N, &K);
    for(i = 0;i < N;++i)
        scanf(INT64, p+i);
    printf(INT64 "\n", ans());
    return 0;
}
