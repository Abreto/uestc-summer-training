#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<map>
#include<queue>
#include<vector>
using namespace std;
const int maxn = 1001010;
int n,m, point[maxn];

struct node
{
    long long int ai,bi;
    long long int min_b, max_a;
    long long int cost;
}a[maxn];

struct edge_{
    int u,v;
    long long int c;
    friend bool operator <(edge_ aa, edge_ bb){
        return aa.c < bb.c;
    }
}edge[maxn];

int father(int x){return (point[x] == -1) ? x : (point[x] = father(point[x]));}

int merage(int x, int y, long long int val){
    int xx, yy;
    if((xx = father(x)) == (yy = father(y))) return 1;
    long long int tem_min, tem_max, tem_cost;
    tem_min = min(a[yy].min_b, a[xx].min_b);
    tem_max = max(a[xx].max_a, a[yy].max_a);
    tem_max = max(tem_max, val);
    tem_cost = min(a[xx].cost+a[yy].cost, tem_min * tem_max);
    
    point[xx] = yy;
    a[yy].min_b = tem_min;
    a[yy].max_a = tem_max;
    a[yy].cost = tem_cost;
    return 0;
}

void Kruskal()
{
    for(int k = 1; k <= m; k++)
    {
        if(merage(edge[k].u, edge[k].v, edge[k].c))
            continue;
    }
    
}
int rem[maxn];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= n; i ++){
        scanf("%lld%lld",&a[i].ai,&a[i].bi);
        a[i].min_b = a[i].bi, a[i].max_a = a[i].ai;
        a[i].cost = a[i].bi * a[i].ai;
    }
    for(int i = 1; i <= m; i++)
        scanf("%d%d%lld",&edge[i].u,&edge[i].v,&edge[i].c);
    sort(edge+1,edge+1+m);
    
    memset(point, -1, sizeof(point));
    Kruskal();
    long long int ans = 0;
    for(int i = 1; i <= n; i ++){
        int xx = father(i);
        if(rem[xx])
            continue;
        rem[xx] = 1;
        ans += a[xx].cost;
    }
    printf("%lld",ans);
    return 0;
}
