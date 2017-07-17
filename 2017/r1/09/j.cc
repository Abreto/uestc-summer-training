/* UESTC 2017 Summer Training #9 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

typedef pair<int,int> pii;
#define mp  make_pair

#define MAXN    128
#define oo  (0x7fffffff)

struct edge
{
    int v;
    int w;
    int n;
};
edge edg[MAXN<<1];
int nedg;
int indegree[MAXN];
int front[MAXN];
int find_edge(int u, int v)
{
    int e = u[front];
    while(e)
    {
        if(edg[e].v == v) return e;
        e = edg[e].n;
    }
    return 0;
}
void add_edge(int u, int v, int w)
{
    int e = find_edge(u,v);
    if(0==e)
    {
        int newnode = ++nedg;
        edg[newnode].v = v;
        edg[newnode].w = w;
        edg[newnode].n = u[front];
        u[front] = newnode;
        indegree[v]++;
    } else {
        edg[e].w = (w < edg[e].w)?w:(edg[e].w);
    }
}

int n, m;

char inq[MAXN];
int vis[MAXN];
int d[MAXN];
int spfa(int s)
{
    queue<int> q;
    memset(inq, 0, sizeof(inq));
    memset(d, -1, sizeof(d));
    memset(vis, 0, sizeof(vis));
    d[s] = 0; inq[s] = 1;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        printf("proc %d..\n", u);
        inq[u] = 0;
        if(vis[u]++ > n+1)
            return 1;
        for(int e = front[u];e;e = edg[e].n)
        {
            int v = edg[e].v, w = edg[e].w;
            if( -1==d[v] || d[u] + w < d[v] )
            {
                d[v] = d[u] + w;
                if(!inq[v])
                {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return 0;
}

void clear(void)
{
    int i = 0;
    nedg = 0;
    for(i = 0;i <= n;++i)
        front[i] = 0;
    memset(indegree, 0, sizeof(indegree));
}

void proccess(void)
{
    int i = 0;
    int si = 0, ni = 0, ki = 0;
    char oi[8] = {0};
    int failed = 0;
    while(m--)
    {
        scanf("%d %d %s %d", &si, &ni, oi, &ki);
        if('g' == oi[0])
        {
            add_edge(si+ni, si-1, -ki-1);
        } else {
            add_edge(si-1, si+ni, ki-1);
        }
    }
    for(i = 0;i <= n;++i)
        if(spfa(i))
        {
            failed = 1;
            break;
        }
    printf("%s\n", failed?"successful conspiracy":"lamentable kingdom");
}

int main(void)
{
    while(EOF!=scanf("%d%d", &n, &m) && n)
    {
        clear();
        proccess();
    }
    return 0;
}
