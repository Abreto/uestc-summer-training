/* Petrozavodsk Summer Training Camp 2016. Problem D, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

#define MAXN    200000
#define MAXM    200000

struct edge
{
    int v, w, n;
    edge():v(0),w(0),n(0){}
    edge(int vv, int nn):v(vv),w(1),n(nn){}
};
int nE;
edge E[(MAXM<<1)+2];
int front[MAXN+1];
int outdeg[MAXN+1];
void add_edge(int u, int v)
{
    int ne = ++nE;
    E[ne] = edge(v,u[front]);
    u[front] = ne;
    outdeg[u]++;
}
void del_edge(int u, int v)
{
    for(int e = u[front];e;e = E[e].n)
        if(E[e].v == v)
        {
            E[e].w = 0;
            outdeg[u]--;
            break;
        }
}

int n, m, d;

int del[MAXN+1];
void delete_vertexes(void)
{
    int i = 0;
    queue<int> q;
    for(i = 1;i <= n;++i)
        if(outdeg[i] < d)
            q.push(i);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        if(0 == del[u])
        {
            for(int e = u[front];e;e = E[e].n)
                if(E[e].w)
                {
                    int v = E[e].v;
                    del_edge(v,u);
                    if(outdeg[v] < d)
                        q.push(v);
                }
            del[u] = 1;
        }
    }
}

char vis[MAXN+1];
vector<int> visited;
void dfs(int u)
{
    if(0 == vis[u])
    {
        vis[u] = 1;
        visited.push_back(u);
        for(int e = u[front];e;e = E[e].n)
            if(E[e].w && (!vis[E[e].v]))
                dfs(E[e].v);
    }
}

int main(void)
{
    int i = 0;
    int ans = 0;
    vector<int> vtx;
    scanf("%d %d %d", &n, &m, &d);
    for(i = 0;i < m;++i)
    {
        int ai, bi;
        scanf("%d %d", &ai, &bi);
        add_edge(ai, bi);
        add_edge(bi, ai);
    }
    delete_vertexes();
    for(i = 1;i <= n;++i)
        if(0 == del[i] && 0 == vis[i])
        {
            visited.clear();
            dfs(i);
            if(visited.size() > vtx.size())
                vtx = visited;
        }
    if(0 == vtx.size()) puts("NIE");
    else
    {
        int len = vtx.size();
        printf("%d\n", len);
        sort(vtx.begin(), vtx.end());
        printf("%d", vtx[0]);
        for(i = 1;i < len;++i)
            printf(" %d", vtx[i]);
        puts("");
    }
    return 0;
}
