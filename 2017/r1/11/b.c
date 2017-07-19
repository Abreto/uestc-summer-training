/* UESTC 2017 Summer Training #11 Div.2. Problem B, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define INPUTFILE   "courier.in"
#define OUTPUTFILE  "courier.out"

#define MAXN    1024
#define BORD    (MAXN<<2)

typedef struct
{
    int id;
    int nxt;
    int del;
}egde_t;
int front[MAXN<<3];
egde_t edg[MAXN<<5];
int d[MAXN<<3];
int nedges;
void add_edge(int u, int v)
{
    int newedge = ++nedges;
    edg[newedge].id = v;
    edg[newedge].nxt = u[front];
    edg[newedge].del = 0;
    u[front] = newedge;
    d[u]++; d[v]++;
}
void del_edge(int u, int v)
{
    int e = 0;
    for(e=u[front];e;e=edg[e].nxt)
        if(edg[e].id==v)
        {
            edg[e].del = 1;
            d[u]--; d[v]--;
            return;
        }
}

int N;
int path[MAXN<<2];
int l;

void add2path(int u)
{
    if(u < BORD)
        path[l++] = u;
}

void build_graph(void)
{
    int i = 0, j = 0, k = 0;
    for(i = 1;i <= N;++i)
    {
        for(j = 4*i-3;j <= 4*i;++j)
        {
            add_edge(j, BORD+j);
            add_edge(BORD+j, j);
        }
        for(j = 4*i-3;j < 4*i;++j)
            for(k = j+1;k <= 4*i;++k)
            {
                add_edge(BORD+j, BORD+k);
                add_edge(BORD+k, BORD+j);
            }
    }
}

void euler(int x)
{
    if(d[x])
    {
        int e = 0;
        for(e=x[front];e;e=edg[e].nxt)
            if(!edg[e].del)
            {
                int v = edg[e].id;
                del_edge(x,v); del_edge(v,x);
                euler(v);
            }
    }
    add2path(x);
}

int main(void)
{
    int i = 0, j = 0, k = 0;
    int ok = 0;
    //freopen(INPUTFILE, "r", stdin);
    //freopen(OUTPUTFILE, "w+", stdout);
    scanf("%d", &N);
    for(i = 0;i < (N<<1);++i)
    {
        scanf("%d%d", &j, &k);
        add_edge(j,k);
        add_edge(k,j);
    }
    build_graph();
    euler(BORD+1);
    if(l != 4*N) puts("No");
    else
    {
        puts("Yes");
        for(i = 0;i < l;++i)
            printf("%d ", path[i]);
        puts("");
    }
    return 0;
}
