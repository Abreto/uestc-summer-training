/* UESTC 2017 Summer Training Round2 #03 Div.2. Problem , by . */
#include <cstdio>
#include <queue>
#include <utility>
#include <cstring>
#include <functional>

using namespace std;

#define INPUTFILE   "algoritm.in"
#define OUTPUTFILE  "algoritm.out"

#define MAXN    100001

typedef long long int ll;
typedef pair<int,int> pii;
typedef priority_queue<pii, vector<pii>, greater<pii> > pq;

struct edge
{
    int id;
    int v,n;
    ll w;
    edge(){}
    edge(int ii, int vv,int ww,int nn):id(ii),v(vv),w(ww),n(nn){}
};
int nE;
edge E[MAXN<<1];
int front[MAXN];
void add_edge(int id, int u, int v, ll w)
{
    int ne = ++nE;
    E[ne] = edge(id, v,w,u[front]);
    u[front] = ne;
}

int N, M;
int par[MAXN];
int reach[MAXN];
vector<int> out[MAXN];
int putededge[MAXN<<1];
int ans[MAXN<<1];
int nans;
int outvis[MAXN];

ll d[MAXN];
int solid[MAXN];
void dijstra(int s)
{
    int i = 0;
    int v = s[front];
    pq q;
    q.push(make_pair(0, s));
    while(!q.empty())
    {
        auto it = q.top();
        int u = it.second;
        int v = u[front];
        q.pop();
        if(solid[u]) continue;
        solid[u] = 1;
        while(v)
        {
            int w = E[v].v;
            if(!solid[w])
            {
                if( (0==d[w]) || (d[u] + E[v].w < d[w]) )
                {
                    par[w] = u;
                    reach[w] = v;
                    d[w] = d[u] + E[v].w;
                    q.push(make_pair(d[w],w));
                }
            }
            v = E[v].n;
        }
    }
    for(i = 1;i <= N;++i)
        out[par[i]].push_back(reach[i]);
}

void clear()
{
    int i = 0;
    nE = 0;
    nans = 0;
    memset(front, 0, sizeof(front));
    memset(d, 0, sizeof(ll)*(N+1));
    memset(solid, 0, sizeof(int)*(N+1));
    memset(putededge, 0, sizeof(int)*(M+1));
    memset(outvis, 0 , sizeof(int)*(N+1));
    for(i = 1;i <= N;++i)
        out[i].clear();
}

void proccess(void)
{
    int i = 0;
    int x = 0, y = 0; ll c = 0;
    queue<int> q;
    for(i = 1;i <= M;++i)
    {
        scanf("%d %d %lld", &x, &y, &c); /* !!I64d */
        add_edge(i, x, y, c);
    }
    dijstra(1);
    q.push(1);
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        outvis[u] = 1;
        for(auto e:out[u])
        {
            ans[nans++] = E[e].id;
            putededge[E[e].id] = 1;
            if(!outvis[E[e].v])
                q.push(E[e].v);
        }
    }
    for(i = 1;i <= M;++i)
        if(!putededge[i])
            ans[nans++] = i;
    printf("%d", ans[0]);
    for(i = 1;i < nans;++i)
        printf(" %d", ans[i]);
    puts("");
}

int main(void)
{
    int T = 0;
    freopen(INPUTFILE, "r", stdin);
    freopen(OUTPUTFILE, "w+", stdout);
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d %d", &N, &M);
        clear();
        proccess();
    }
    return 0;
}
