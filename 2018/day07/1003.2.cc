#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int,int> pii;
#define mp make_pair
#define se second

int n;
pii pnts[3003];

int main(void)
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i = 0;i < n*3;i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            pnts[i] = mp(x, i+1);
        }
        sort(pnts, pnts+n*3);
        for(int i = 0;i < n*3;i+=3)
        {
            printf("%d %d %d\n", pnts[i].se, pnts[i+1].se, pnts[i+2].se);
        }
    }
    return 0;
}
