/* UESTC 2017 Summer Training #8 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <math.h>

#define MAXN    1024

int gcd(int a, int b) {return (0==b)?a:gcd(b,a%b);}

typedef struct
{
    int t, b; /* t/b */
}frac_t;
frac_t mul(frac_t f1, frac_t f2)
{
    int nt = f1.t*f2.t, nb = f1.b*f2.b;
    int g = gcd(nt,nb);
    return (frac_t){nt/g, nb/g};
}
int same(frac_t f1, frac_t f2)
{
    return (f1.t==f2.t)&&(f1.b==f2.b); /* INTENTION */
}
typedef struct
{
    int id;
    int nxt;
}egde_t;
int dir[MAXN];
frac_t ratio[MAXN];
int front[MAXN];
egde_t edg[MAXN*MAXN];
int nedges;
void add_edge(int u, int v)
{
    int newedge = ++nedges;
    edg[newedge].id = v;
    edg[newedge].nxt = u[front];
    u[front] = newedge;
}

int n;
int x[MAXN], y[MAXN];
int r[MAXN];

int isconj(int i, int j)
{
    int dx = x[i]-x[j], dy = y[i]-y[j];
    int d2 = dx*dx+dy*dy;
    int r2 = r[i]*r[i]+2*r[i]*r[j]+r[j]*r[j];
    return (d2==r2);
}

void build_graph(void)
{
    int i = 0, j = 0;
    for(i = 1;i <= n;++i)
        for(j = 1;j <= n;++j)
            if(i != j && isconj(i,j))
            {
                add_edge(i, j);
                add_edge(j, i);
            }
}

int vis[MAXN];

int dfs(int u)
{
    int e = u[front];
    int t = 0;
    vis[u] = 1;
    while(e)
    {
        int v = edg[e].id;
        if(vis[v])
        {
            if(dir[v] == dir[u]) return 0;
            if(!same(ratio[v], mul(ratio[u], (frac_t){r[u], r[v]}))) return 0;
        } else {
            dir[v] = -dir[u];
            ratio[v] = mul(ratio[u], (frac_t){r[u], r[v]});
            t = dfs(v);
            if(0 == t) return 0;
        }
        e = edg[e].nxt;
    }
    return 1;
}

int main(void)
{
    int i = 0;
    int t = 0;

    scanf("%d", &n);
    for(i = 1;i <= n;++i)
        scanf("%d %d %d", x+i, y+i, r+i);
    build_graph();
    ratio[1] = (frac_t){1,1}; dir[1] = 1;
    t = dfs(1);

    if(0 == t) puts("The input gear cannot move.");
    else if (0 == vis[n]) puts("The input gear is not connected to the output gear.");
    else
    {
        if(-1 == dir[n]) putchar('-');
        printf("%d:%d\n", ratio[n].t, ratio[n].b);
    }

    return 0;
}
