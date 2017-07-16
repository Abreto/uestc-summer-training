/* UESTC 2017 Summer Training #8 Div.2. Problem D, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <set>
#include <utility>

using namespace std;
typedef set< pair<int,int> > spii;

#define MAXN    512
#define MAXV    (MAXN*MAXN)

struct egde_t
{
    int id;
    int nxt;
};

int front[MAXV];
egde_t edg[MAXV<<3];
int nedges;
void add_edge(int u, int v)
{
    int newedge = ++nedges;
    edg[newedge].id = v;
    edg[newedge].nxt = u[front];
    u[front] = newedge;
}

int d[MAXV];
int vis[MAXN];
int solid[MAXV];

int dijstra(int s, int t)
{
    int v = s[front];
    spii q;
    q.insert(make_pair(0, s));
    while(!q.empty())
    {
        auto it = q.begin();
        int u = it->second;
        int v = u[front];
        q.erase(it);
        solid[u] = 1;
        /*printf("solid %d with %d\n", u, d[u]);*/
        if(u == t) break;
        while(v)
        {
            int w = edg[v].id;
            if(!solid[w])
            {
                if( (0==d[w]) || (d[u] + 1 < d[w]) )
                {
                    q.erase(make_pair(d[w],w));
                    d[w] = d[u] + 1;
                    q.insert(make_pair(d[w],w));
                }
            }
            v = edg[v].nxt;
        }
    }
    return d[t];
}

int m, n;
char gird[MAXN][MAXN];

#define HASH(x,y)   (1+(x)*n+(y))

void build_graph(void)
{
    int i = 0, j = 0, k = 0;
    int d[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};
    for(i = 0;i < m;++i)
        for(j = 0;j < n;++j)
        {
            int l = gird[i][j] - '0';
            if(0 == l) continue;
            for(k = 0;k < 4;++k)
            {
                int nx = i + l*d[k][0], ny = j + l*d[k][1];
                if(nx >= 0 && nx < m && ny >= 0 && ny < n)
                    add_edge(HASH(i,j), HASH(nx,ny));
            }
        }
}

void print_graph()
{
    int i = 0;
    for(i = 1;i <= HASH(m-1,n-1);++i)
    {
        int u = i[front];
        printf("%d:", i);
        while(u)
        {
            printf(" %d", edg[u].id);
            u = edg[u].nxt;
        }
        puts("");
    }
}

int main(void)
{
    int i = 0;
    int t = 0;
    scanf("%d%d", &m, &n);
    for(i = 0;i < m;++i)
        scanf("%s", gird[i]);
    build_graph();
    t = dijstra(HASH(0,0), HASH(m-1,n-1));
    if(t) printf("%d\n", t);
    else puts("IMPOSSIBLE");
    return 0;
}
