/* UESTC 2017 Summer Training #22. Problem A, by Abreto<m@abreto.net> */
#include <stdio.h>

#define MAXN    100000

typedef struct
{
    int l,r;
    int cnt;    /* number of 1 */
}node_t;

node_t merge(node_t n1, node_t n2)
{
    node_t ans;
    ans.l = n1.l; ans.r = n2.r;
    ans.cnt = n1.cnt + n2.cnt;
    return ans;
}

typedef struct
{
  int marked; /* Optional */
  int as;   /* 1 or 0 */
}lazy_t;

int A[MAXN];
int MI;
node_t nodes[MAXN<<2];
lazy_t marks[MAXN<<2];

void maintain_leaf(int o, int idx)
{
    nodes[o].l = nodes[o].r = idx;
    nodes[o].cnt = (A[idx] >= MI);
}
void maintain(int o)
{
    nodes[o] = merge(nodes[o<<1], nodes[o<<1|1]);
}

/* Usage: build(1,1,n); */
void build(int o, int l, int r) /* [l,r] */
{
    marks[o].marked = 0;
    if( r <= l )
    {
        maintain_leaf(o, l);
    } else {
        int mid = l+r>>1;
        build(o<<1, l, mid);
        build(o<<1|1, mid+1, r);
        maintain(o);
    }
}

/* Modify all elements in [l,r] */
void mark(lazy_t act, int o)
{
    nodes[o].cnt = (1 == act.as) ? (nodes[o].r - nodes[o].l + 1) : 0;
    marks[o].as = act.as;
    marks[o].marked = 1;
}

/* Pass cached updates. */
void pushdown(int o)
{
    if( marks[o].marked )
    {
        mark(marks[o], o<<1);
        mark(marks[o], o<<1|1);
        marks[o].marked = 0;
    }
}

/* Do act on all elements in [L,R] */
void sas(int L, int R, lazy_t act, int o, int l, int r)
{
    if( L <= l && r <= R )
    {
        mark(act, o);
    } else if (L <= R) {
        int mid = (l+r)>>1;
        pushdown(o);
        if( L <= mid ) sas(L, R, act, o<<1, l, mid);
        if( R > mid ) sas(L, R, act, o<<1|1, mid+1, r);
        maintain(o);
    }
}

int q1(int L, int R, int o, int l, int r) /* how many 1s */
{
    if(L <= l && r <= R)
    {
        return nodes[o].cnt;
    } else if (L <= R) {
        int mid = (l+r)>>1;
        pushdown(o);
        if(R <= mid) return q1(L, R, o<<1, l, mid);
        else if (L > mid) return q1(L, R, o<<1|1, mid+1, r);
        else return q1(L, R, o<<1, l, mid)+q1(L, R, o<<1|1, mid+1, r);
    }
}

int n, m;
int ql[MAXN], qr[MAXN];

int check()
{
    int i = 0;
    build(1,1,n);
    for(i = 0;i < m;++i)
    {
        int L = ql[i], R = qr[i];
        int re = (L>R);
        int cnt = 0;
        if(re){int t = R; R = L; L = t;}
        cnt = q1(L,R,1,1,n);
        sas(L, R, (lazy_t){1,0}, 1,1,n);
        if(0 == re) sas(R-cnt+1, R, (lazy_t){1,1}, 1,1,n);
        else sas(L, L+cnt-1, (lazy_t){1,1}, 1,1,n);
    }
    return q1((n+1)/2,(n+1)/2,1,1,n);
}

int handle(void)
{
    int l = 1, r = n;
    while(l <= r)
    {
        MI = (l+r)>>1;
        if(check()) l = MI+1;
        else r = MI-1;
    }
    return l-1;
}

int main(void)
{
    int i = 0;
    scanf("%d %d", &n, &m);
    for(i = 1;i <= n;++i)
        scanf("%d", A+i);
    for(i = 0;i < m;++i)
        scanf("%d %d", ql+i, qr+i);
    printf("%d\n", handle());
    return 0;
}
