/* UESTC 2017 Summer Training #8 Div.2. Problem F, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <set>

using namespace std;

#define MAXN    100001

int n;
int s[MAXN];

int valid(int X)
{
    int i = 0;
    multiset<int> si;
    for(i = 0;i < n;++i)
        si.insert(s[i]);
    while(!si.empty())
    {
        auto fit = si.begin();
        int f = *fit;
        si.erase(fit);
        auto sit = si.lower_bound(X-f);
        if(sit == si.end()) return 0;
        si.erase(sit);
    }
    return 1;
}

int ans(void)
{
    int l = 2, r = 2000000;
    while(r - l)
    {
        int mid = (l+r)/2+1;
        /*int t = valid(mid);
        printf("%d:%s\n", mid, t?"ok":"failed");*/
        if(valid(mid))
            l = mid;
        else
            r = mid-1;
    }
    return l;
}

int main(void)
{
    int i = 0;
    scanf("%d", &n);
    for(i = 0;i < n;++i)
        scanf("%d", s+i);
    printf("%d\n", ans());
    return 0;
}
