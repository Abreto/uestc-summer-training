/* UESTC 2017 Summer Training #26 Div.2. Problem A, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define PROB    "athletic"

void init(void)
{
#ifndef ABDEBUG
    freopen(PROB ".in", "r", stdin);
    freopen(PROB ".out", "w+", stdout);
#endif
}

#define MAXN    200000

typedef struct
{
    int v,n;
}edge_t;
edge_t E[MAXN<<1];
int nE;
int front[MAXN+1];
int par[MAXN+1];
void add_edge(int u,int v)
{
    int ne = ++nE;
    E[ne] = (edge_t){v,u[front]};
    u[front] = ne;
}
#define fore(u) for(e=u[front];e;e=E[e].n)if(E[e].v!=par[u])
int mymax(int a, int b) {return (a>b)?a:b;}

int n, m;
int type[MAXN+1];
int dp[MAXN+1][2];  /* [][0] for not, [][1] for give. -1 means cannot. */

int vis[MAXN+1];
void dfs(int u)
{
    if(!vis[u])
    {
        int e = 0;
        int notleaf = 0;
        vis[u] = 1;
        for(e = u[front];e;e = E[e].n)
            if(!vis[E[e].v])
            {
                par[E[e].v] = u;
                dfs(E[e].v);
                notleaf = 1;
            }
        if(notleaf) /* assume that [][1] <= [][0] */
        {
            int i = 0;
            {   /* calculate dp[u][0] */
                if(0 == type[u])
                {
                    int ncan = 0;
                    dp[u][0] = 0;
                    fore(u)
                    {
                        int v = E[e].v;
                        dp[u][0] += dp[v][0];
                        if(/*dp[v][1] != -1 && */dp[v][0] == dp[v][1]) ncan++;
                    }
                    if(ncan > 1)
                        dp[u][0]++;
                } else {
                    int ncan = 0;
                    dp[u][0] = 0;
                    fore(u)
                    {
                        int v = E[e].v;
                        dp[u][0] += dp[v][0];
                        if(/*dp[v][1] != -1 && */dp[v][0] == dp[v][1]) ncan++;
                    }
                    if(ncan > 0)
                        dp[u][0]++;
                }
            }
            {   /* calculate dp[u][1] */
                if(0 == type[u])
                {
                    int mindelta = MAXN+1;
                    int mindeltaid = -1;
                    dp[u][1] = 0;
                    fore(u)
                    {
                        int v = E[e].v;
                        dp[u][1] += dp[v][0];
                        if( (-1 != dp[v][1]) && (dp[v][0] - dp[v][1] < mindelta) )
                        {
                            mindelta = dp[v][0] - dp[v][1];
                            mindeltaid = v;
                        }
                    }
                    if(-1 == mindeltaid)
                    {
                        dp[u][1] = -1;
                    } else {
                        dp[u][1] -= mindelta;
                    }
                } else {
                    dp[u][1] = 0;
                    fore(u)
                    {
                        dp[u][1] += dp[E[e].v][0];
                    }
                }
            }
        } else {    /* this is leaf */
            dp[u][0] = dp[u][1] = 0;
            if(0 == type[u]) dp[u][1] = -1;
        }
    }
}

void proc(void)
{
    int i = 0;
    scanf("%d", &n);
    for(i = 1;i < n;++i)
    {
        int a,b;
        scanf("%d %d", &a, &b);
        add_edge(a,b); add_edge(b,a);
    }
    scanf("%d", &m);
    while(m--)
    {
        scanf("%d", &i);
        type[i] = 1;
    }
    dfs(1);
    printf("%d\n", dp[1][0]);
}

int main(void)
{
    init();
    proc();
    return 0;
}
