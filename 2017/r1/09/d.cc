/* UESTC 2017 Summer Training #9 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cstring>
#include <set>
#include <queue>
#include <utility>

using namespace std;

#define INPUTFILE   "input.txt"
#define OUTPUTFILE  "output.txt"
#define MAXN 1024

struct
{
    int v;
    int n;
}edg[MAXN<<1];
int nedg;
int front[MAXN];
void add_edge(int u, int v)
{
    int newnode = ++nedg;
    edg[newnode].v = v;
    edg[newnode].n = u[front];
    u[front] = newnode;
}

int mex(set<int>& app)
{
    int i = 0;
    for(i = 0;app.count(i);++i);
    return i;
}

int n;
int fire[MAXN];
int sg[MAXN];

void bfs(void)
{
    queue< pair<int,int> > q;
    fire[1] = 1;
    q.push(make_pair(1,1));
    while(!q.empty())
    {
        pair<int,int> p = q.front();
        int u = p.first; int day = p.second+1;
        int e = u[front];
        int canmove = 0;
        q.pop();
        while(e)
        {
            int v = edg[e].v;
            if(!fire[v])
            {
                fire[v] = day;
                q.push(make_pair(v,day));
                canmove = 1;
            } else if ( fire[v] > fire[u] )
                canmove = 1;
            e = edg[e].n;
        }
        if(!canmove) sg[u] = 0;
    }
}

int dfs(int u)
{
    if(sg[u] > -1) return sg[u];
    int e = u[front];
    set<int> app;
    while(e)
    {
        int v = edg[e].v;
        if(fire[v] > fire[u])
            app.insert(dfs(v));
        e = edg[e].n;
    }
    return (sg[u]=mex(app));
}

void proccess(void)
{
    int m = 0;
    int ai = 0, bi = 0;
    scanf("%d%d", &n, &m);
    while(m--)
    {
        scanf("%d%d", &ai, &bi);
        add_edge(ai, bi);
        add_edge(bi, ai);
    }
    memset(sg, -1, sizeof(sg));
    bfs();
    printf("%s\n", (0==dfs(1))?"Nikolay":"Vladimir");
}

int main(void)
{
    //freopen(INPUTFILE, "r", stdin);
    //freopen(OUTPUTFILE, "w+", stdout);
    proccess();
    return 0;
}
