/* Multi-Univ #1. 1002 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>

#define MAXN    100001

using namespace std;

struct pii
{
    int fi, se; /* left, unclosed */
    int id;
    pii(void):fi(0),se(0),id(-1){}
    pii(int f, int s, int i):fi(f),se(s),id(i){}
}ss[2][MAXN];
#define mp pii

int n;
int used[MAXN];

bool compar1(const pii &x, const pii &y)
{
    if(x.se == y.se) return x.fi < y.fi;
    else return x.se > y.se;
}
bool compar2(const pii &x, const pii &y)
{
    if(x.fi == y.fi) return x.se > y.se;
    else return x.fi < y.fi;
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
        ss[0][j] = mp(left, unclosed, j);
        ss[1][j] = mp(left, unclosed, j);
        used[j] = 0;
    }
    sort(ss[0], ss[0]+n, compar1);
    sort(ss[1], ss[1]+n, compar2);
    int idx[2] = {0, 0};
    int consider = 0;
    int unclosed = 0;
    while(idx[0] < n && idx[1] < n)
    {
        pii current = ss[consider][idx[consider]];
        printf("consider (%d,%d)#%d\n", current.fi, current.se, current.id);
        if(used[ current.id ])
        {
            idx[consider]++;
        } else {
            int available = current.fi;
            if( unclosed > 0 && available > 0 )
            {
                ans += (min(unclosed, available)<<1);
                unclosed = max(0, unclosed - available);
            }
            unclosed += current.se;
            used[current.id] = 1;
            idx[consider]++;
            consider ^= 1;
        }
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
