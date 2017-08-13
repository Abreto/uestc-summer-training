/* UESTC 2017 Summer Training #28 Div.2. Problem C, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXV    512
#define MAXE    60001
struct edge
{
    int v, n;
};
int nE;
edge E[MAXE<<1];
int front[MAXV];
void add_edge(int u, int v)
{
    int ne = ++nE;
    E[ne].v = v; E[ne].n = u[front];
    u[front] = ne;
}

#define MAXN    512
int N, M, I;
int age[MAXN];
int position[MAXN];
int manage[MAXN][MAXN];

int vis[MAXN];
void __dfs(int s, int u)
{
    if(s != u) manage[s][u] = 1;
    vis[u] = 1;
    for(int e = u[front];e;e = E[e].n)
        if(!vis[E[e].v])
            __dfs(s, E[e].v);
}

void dfs(int s)
{
    memset(vis, 0, sizeof(vis));
    __dfs(s,s);
}

void init(void)
{
    int i = 0;
    for(i = 1;i <= N;++i)
        dfs(i);
    for(i = 1;i <= N;++i)
        position[i] = i;
}

int main(void)
{
    int i = 0;
    scanf("%d %d %d", &N, &M, &I);
    for(i = 1;i <= N;++i)
        scanf("%d", age+i);
    for(i = 0;i < M;++i)
    {
        int X, Y;
        scanf("%d %d", &X, &Y);
        add_edge(X,Y);
    }
    init();
    while(I--)
    {
        char op[4] = {0};
        scanf("%s", op);
        if('T' == op[0])
        {
            int A, B;
            scanf("%d %d", &A, &B);
            swap(position[A], position[B]);
        } else if ('P' == op[0]) {
            int E;
            int minage = 128;
            scanf("%d", &E);
            for(i = 1;i <= N;++i)
                if(manage[position[i]][position[E]] && age[i] < minage)
                    minage = age[i];
            if(128 == minage) puts("*");
            else printf("%d\n", minage);
        }
    }
    return 0;
}
