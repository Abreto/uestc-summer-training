#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>

using namespace std;

#define MAXN    (100010)
#define RPWENEED    (128)

inline int range_random(int l = 1, int r = 1000000000)
{
    int w = r - l + 1;
    return l + (rand() % w);
}

set<int> selected;
set<int> solid;
int solidsum;
vector<int> couldbechanged;

int n;
int edges[MAXN][2];
int change[MAXN];
int newlabel[MAXN];
int xorsum[MAXN];

void needrp(void)
{
    selected.clear();
    for(auto u : couldbechanged)
    {
        int candidate;
        do
        {
            candidate = range_random();
        }while((solid.find(candidate)!=solid.end()) || (selected.find(candidate)!=selected.end()));
        selected.insert(candidate);
        newlabel[u] = candidate;
    }
}

int check(void)
{
    int xsum = n;
    xsum ^= solidsum;
    for(auto u : couldbechanged)
        if(xorsum[u])
            xsum ^= newlabel[u];
    if(0 == xsum) return 1;
    for(auto u : couldbechanged)
        if(xorsum[u])
        {
            /* arrange u */
            int want2be = xsum ^ newlabel[u];
            if(want2be < 1 || want2be > 1000000000) continue;
            if((solid.find(want2be)==solid.end()) && (selected.find(want2be)==selected.end()))
            {
                newlabel[u] = want2be;
                return 1;
            }
        }
    return 0;
}

void scan(int x)
{
    xorsum[x] ^= x;
    if(0 == change[x]) solidsum ^= x;
}

int main(void)
{
    int i;
    srand(772002);
    scanf("%d", &n);
    for(i = 1;i <= n;i++)
    {
        scanf("%d", change+i);
        if(1 == change[i]) couldbechanged.push_back(i);
        else solid.insert(i);
        newlabel[i] = i;
    }
    for(i = 1;i < n;i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        edges[i][0] = u;
        edges[i][1] = v;
        scan(u); scan(v);
    }
    for(i = 0;i < RPWENEED;i++)
    {
        needrp();
        if( check() )
        {
            printf("%d\n", n);
            for(int j = 1;j < n;j++)
                printf("%d %d\n", newlabel[edges[j][0]], newlabel[edges[j][1]]);
            return 0;
        }
    }
    puts("-1");
    return 0;
}
