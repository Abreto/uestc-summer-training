/* UESTC 2017 Summer Training #14 Div.2. Problem E, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <queue>
#include <functional>
#include <utility>

using namespace std;
#define mp make_pair
typedef pair<int,int> pii;

int main(void)
{
    int n = 0, k = 0;
    int ti = 0;
    int cure = 0, maxe = 0;
    priority_queue<pii, vector<pii>, greater<pii> > q;
    scanf("%d %d", &n, &k);
    while(n--)
    {
        scanf("%d", &ti);
        q.push(mp(ti,1));
        q.push(mp(ti+1000,-1));
    }
    while(!q.empty())
    {
        pii p = q.top();
        cure += p.second;
        if(cure > maxe) maxe = cure;
        q.pop();
    }
    printf("%d\n", (maxe-1)/k+1);
    return 0;
}
