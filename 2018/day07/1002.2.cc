/* Multi-Univ #1. 1002 */
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <utility>

#define MAXN    100001

using namespace std;

struct pii
{
    int fi, se; /* left, unclosed */
    int d;
    int id;
    pii(void):fi(0),se(0),id(-1){d = 0;}
    pii(int f, int s, int i):fi(f),se(s),id(i){d = se - fi;}
}ss[MAXN];
#define mp pii

int n;
int used[MAXN];

bool compar(const pii &x, const pii &y)
{
    if(x.d == y.d) return ( min(x.se,y.fi) > min(x.fi,y.se) );
    else return x.d > y.d;
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
        ss[j] = mp(left, unclosed, j);
        used[j] = 0;
    }
    sort(ss, ss+n, compar);
    int unclosed = 0;
    for(i = 0;i < n;i++)
    {
        // printf("consider (%d,%d)#%d\n", ss[i].fi, ss[i].se, ss[i].id);
        if(unclosed > 0 && ss[i].fi > 0)
        {
            ans += (min(unclosed, ss[i].fi) << 1);
            unclosed = max(0, unclosed - ss[i].fi);
        }
        unclosed += ss[i].se;
    }
    printf("%d\n", ans);
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while(T--) proc();
    return 0;
}
