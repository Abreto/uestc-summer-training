/* UESTC 2017 Summer Training #30 Div.2. Problem J, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif
typedef long long int ll;
#define MAXN    200000
#define MAXLGN  32

int n, q;
ll ai[MAXN+1];
ll minv[MAXN+1][MAXLGN];

void init(void)
{
    int i = 0, w = 0, t = 0, l = 0;
    for(i = 1;i <= n;++i)
        minv[i][0] = ai[i];
    for(w = 1;(t = (1<<w)) <= n;++w)
    {
        l = t;
        t >>= 1;
        for(i = 1;i+l-1<=n;++i)
            minv[i][w] = min(minv[i][w-1], minv[i+t][w-1]);
    }
}

int main(void)
{
    int i = 0, j = 0;
    scanf("%d %d", &n, &q);
    for(i = 1;i <= n;++i)
        scanf(INT64, ai+i);
    init();
    while(q--)
    {
        ll vi;
        int li, ri;
        scanf(INT64 " %d %d", &vi, &li, &ri);
        i = li;
        while(i <= ri)
        {
            int ni = i;
            vi %= ai[i];
            for(j = MAXLGN;j >= 0;--j)
                if( (ni+(1<<j)) <= ri+1 && minv[ni][j] > vi )
                {
                    ni += (1<<j);
                }
            i = ni;
        }
        printf(INT64 "\n", vi);
    }

    return 0;
}

