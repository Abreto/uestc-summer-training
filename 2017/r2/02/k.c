/* UESTC 2017 Summer Training Round2 #02 Div.2. Problem K, by . */
#include <stdio.h>

#define MAXN    200001
#define inf     1000000000000000000ll

typedef long long int ll;
ll min(ll a, ll b){return (a<b)?a:b;}

typedef struct
{
    int v;
    ll w;
    int n;
}edge_t;
int nE;
edge_t E[MAXN<<1];
int front[MAXN];
void add_edge(int u, int v, ll w)
{
    int ne = ++nE;
    E[ne] = (edge_t){v,w,u[front]};
    u[front] = ne;
}

int n;
ll dp[MAXN][4]; /* 0 for phi, 1 for purple, 2 for cian */
int type[MAXN];

#define CUTREQUIRED(t1,t2)  ((0!=(t1)*(t2))&&((t1)!=(t2)))
int vis[MAXN];
void dfs(int u)
{
    int i = 0;
    int e = 0;
    int notleaf = 0;
    vis[u] = 1;
    for(e=u[front];e;e=E[e].n)
        if(!vis[E[e].v])
            dfs(E[e].v),(notleaf=1);
    if(!notleaf)
    {
        int i = 0;
        for(i = 0;i < 3;++i)
            dp[u][i] = inf;
        dp[u][type[u]] = 0;
    } else {
        if(0 == type[u])
        {
            for(e=u[front];e;e=E[e].n)
            {
                int v = E[e].v; ll w = E[e].w;
                dp[u][0] += min(dp[v][0],min(dp[v][1]+w,dp[v][2]+w));
                dp[u][0] = min(dp[u][0], inf);
            }
            for(e=u[front];e;e=E[e].n)
            {
                int v = E[e].v; ll w = E[e].w;
                dp[u][1] += min(dp[v][0],min(dp[v][1],dp[v][2]+w));
                dp[u][1] = min(dp[u][1], inf);
            }
            for(e=u[front];e;e=E[e].n)
            {
                int v = E[e].v; ll w = E[e].w;
                dp[u][2] += min(dp[v][0],min(dp[v][1]+w,dp[v][2]));
                dp[u][2] = min(dp[u][2], inf);
            }
        } else {
            dp[u][0] = dp[u][3-type[u]] = inf;
            for(e=u[front];e;e=E[e].n)
            {
                int v = E[e].v; ll w = E[e].w;
                dp[u][type[u]] += min(dp[v][0],min(dp[v][1]+w*CUTREQUIRED(1,type[u]),dp[v][2]+w*CUTREQUIRED(2,type[u])));
                dp[u][type[u]] = min(dp[u][type[u]], inf);
            }
        }
    }
    /*printf("after %d(%d): %lld, %lld, %lld\n", u, type[u], dp[u][0], dp[u][1], dp[u][2]);*/
}

int main(void)
{
    int i = 0, j = 0, k = 0;
    ll ans = inf;
    scanf("%d", &n);
    for(i = 1;i < n;++i)
    {
        int ui = 0, wi = 0, vi = 0;
        scanf("%d%d%d", &ui, &vi, &wi);
        add_edge(ui,vi,wi); add_edge(vi,ui,wi);
    }
    for(i = 1;i < 3;++i)
    {
        scanf("%d", &j);
        while(j--)
        {
            scanf("%d", &k);
            type[k] = i;
        }
    }
    dfs(1);
    for(i = 0;i < 3;++i)
        ans = min(ans, dp[1][i]);
    printf("%lld\n", ans);
    return 0;
}
