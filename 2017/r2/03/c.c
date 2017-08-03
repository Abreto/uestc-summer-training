/* UESTC 2017 Summer Training Round2 #03 Div.2. Problem , by . */
#include <stdio.h>

#define MAXN    100001

#define inf     (MAXN<<2)

int min(int a, int b) {return (a<b)?a:b;}

typedef struct
{
    int l,r;
    int mindeg;
}node_t;

node_t merge(node_t n1, node_t n2)
{
    node_t ans;
    ans.l = n1.l; ans.r = n2.r;
    ans.mindeg = min(n1.mindeg, n2.mindeg);
    return ans;
}

typedef struct
{
  int marked; /* Optional */
  int delta;
}lazy_t;

int A[MAXN];
node_t nodes[MAXN<<2];
lazy_t marks[MAXN<<2];

void maintain_leaf(int o, int idx)
{
    nodes[o].l = nodes[o].r = idx;
    nodes[o].mindeg = A[idx];
}
void maintain(int o)
{
    nodes[o] = merge(nodes[o<<1], nodes[o<<1|1]);
}

/* Usage: build(1,1,n); */
void build(int o, int l, int r) /* [l,r] */
{
    if( r <= l )
    {
        maintain_leaf(o, l);
    } else {
        int mid = l+r>>1;
        build(o<<1, l, mid);
        build(o<<1|1, mid+1, r);
        maintain(o);
    }
    marks[o] = (lazy_t){0,0};
}

/* Modify all elements in [l,r] */
void mark(lazy_t act, int o)
{
    nodes[o].mindeg += act.delta;
    marks[o].delta += act.delta;
    if(nodes[o].mindeg > inf) nodes[o].mindeg = inf;
    if(marks[o].delta > inf) marks[o].delta = inf;
    marks[o].marked = 1;
}

/* Pass cached updates. */
void pushdown(int o)
{
    if( marks[o].marked )
    {
        mark(marks[o], o<<1);
        mark(marks[o], o<<1|1);
        marks[o] = (lazy_t){0,0};
    }
}

/* Do act on all elements in [L,R] */
void update(int L, int R, lazy_t act, int o, int l, int r)
{
    if(l > r) return;
    if( L <= l && r <= R )
    {
        mark(act, o);
    } else {
        int mid = (l+r)>>1;
        pushdown(o);
        if( L <= mid ) update(L, R, act, o<<1, l, mid);
        if( R > mid ) update(L, R, act, o<<1|1, mid+1, r);
        maintain(o);
    }
}

int query(int o, int l, int r)
{
    if(r <= l) return l;
    else
    {
        int mid = (l+r)>>1;
        pushdown(o);
        if(0 == nodes[o<<1|1].mindeg) return query(o<<1|1,mid+1,r);
        else return query(o<<1,l,mid);
    }
}

typedef struct
{
    int v;
    int n;
}edge_t;
int nE;
edge_t E[MAXN];
int front[MAXN];
void add_del(int u, int v)
{
    int ne = ++nE;
    E[ne] = (edge_t){v, u[front]};
    u[front] = ne;
}

int N, M;
int top[MAXN];

void clear(void)
{
    int i = 0;
    nE = 0;
    for(i =0 ;i <= N;++i)
        i[front] = 0;
    for(i = 1;i <= N;++i)
        A[i] = i-1;
    build(1,1,N);
}

void proccess(void)
{
    int i = 0;
    int a = 0, b = 0;
    while(M--)
    {
        scanf("%d %d", &a, &b);
        add_del(a,b);
        update(b,b, (lazy_t){1,-1}, 1,1,N);
    }
    for(i = 0;i < N;++i)
    {
        int u = query(1,1,N);
        int e = u[front];
        top[i] = u;
        update(u,u, (lazy_t){1,inf}, 1,1,N);
        update(u+1,N, (lazy_t){1,-1}, 1,1,N);
        while(e)
        {
            int v = E[e].v;
            update(v,v, (lazy_t){1,1}, 1,1,N);
            e = E[e].n;
        }
    }
    printf("%d", *top);
    for(i = 1;i < N;++i)
        printf(" %d", top[i]);
    puts("");
}

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d %d", &N, &M);
        clear();
        proccess();
    }
    return 0;
}
