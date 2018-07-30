#include <cassert>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define pb  push_back
#define MAX3N   3003

struct pnt
{
    int x, y;
    int id;
}P[MAX3N];

vector<int> vertical[MAX3N];
int n;
int xs[MAX3N];
int nx;

int getid(int x)
{
    return lower_bound(xs, xs+nx, x) - xs;
}

void myclear(void)
{
    for(int i = 0;i < MAX3N;i++)
    {
        vertical[i].clear();
    }
    nx = 0;
}

void myread(void)
{
    int i;
    scanf("%d", &n);
    for(i = 1;i <= n*3;i++)
    {
        int xi, yi;
        scanf("%d%d", &xi, &yi);
        P[i] = (pnt){xi, yi, i};
        xs[nx++] = xi;
    }
    sort(xs, xs+nx);
    nx = unique(xs, xs+nx) - xs;
    for(i = 1;i <= n;i++)
        vertical[getid(P[i].x)].pb(P[i].id);
}

void mywork(void)
{
    int i;
    for(i = 0;i < nx;i++)
    {
        int cnt = vertical[i].size();
        assert(cnt > 0 && cnt < 3);
        if(1 == cnt)
        {
            assert(i+1 < nx);
            int after = vertical[i+1].size();
            assert(after > 0 && after < 3);
            if(1 == after)
            {
                assert(i+2 < nx);
                int aafter = vertical[i+2].size();
                assert(aafter > 0 && aafter < 3);
                if(aafter == 1)
                {
                    printf("%d %d %d\n", vertical[i][0], vertical[i+1][0], vertical[i+2][0]);
                    i += 2;
                } else {
                    printf("%d %d %d\n", vertical[i][0], vertical[i+1][0], vertical[i+2][1]);
                    vertical[i+2].pop_back();
                    i++;
                }
            } else {
                printf("%d %d %d\n", vertical[i][0], vertical[i+1][0], vertical[i+1][1]);
                i++;
            }
        } else if (2 == cnt) {
            assert(i+1 < nx);
            int after = vertical[i+1].size();
            assert(after > 0 && after < 3);
            if(after == 1)
            {
                printf("%d %d %d\n", vertical[i][0], vertical[i][1], vertical[i+1][0]);
                i++;
            } else {
                printf("%d %d %d\n", vertical[i][0], vertical[i][1], vertical[i+1][1]);
                vertical[i+1].pop_back();
                i++;
            }
        }
    }
}

void proc(void)
{
    myclear();
    myread();
    mywork();
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while(T--) proc();
    return 0;
}
