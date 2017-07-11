/* UESTC 2017 Summer Training #3 Div.2. Problem L, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

int mymin(int a, int b) {return (a<b)?a:b;}

#define MAXN    50010
#define MAXB    256

typedef long long int ll;

int n;
int a[MAXN], b[MAXN];
int onechunk, nchunks;
ll chunkans[MAXB][MAXB];

/* CHUNK i (indexed from 1) */
#define CHUNKL(i)   ((((i)-1)*onechunk)+1)
#define CHUNKR(i)   ((i)*onechunk)
#define CHUNKBOUND(i,l,r)   ((l=CHUNKL(i)),(r=mymin(n,CHUNKR(i))))
#define CHUNKID(pos)    ((((pos)-1)/onechunk)+1)

void mapa(void)
{
    int i = 0;
    int *p = 0;
    for(i = 0;i < n;++i)
        b[i] = a[i+1];
    sort(b, b+n);
    p = unique(b, b+n);
    for(i = 1;i <= n;++i)
        a[i] = lower_bound(b, p, a[i]) - b + 1;
}

int fen[MAXB<<1][MAXN]; /* 0 reserved. */
#define LOWBIT(x)   ((x)&(-(x)))
void fclear(int fx)
{
    int i = 0;
    for(i = 0;i <= n;++i) fen[fx][i] = 0;
}
void fupd(int fx, int i, int d)
{
    while(i <= n)
    {
        fen[fx][i] += d;
        i += LOWBIT(i);
    }
}
int fq(int fx, int i) /* how many not greater than i: (0,i] */
{
    int ret = 0;
    while(i > 0)
    {
        ret += fen[fx][i];
        i -= LOWBIT(i);
    }
    return ret;
}
int fqi(int fx, int l, int r) /* how many in [l,r] */
{
    return (l>r)? 0 : (fq(fx,r)-fq(fx,l-1));
}

void initbit(void)
{
    int i = 0, j = 0;
    int bl = 0, br = 0;
    for(i = 1;i <= nchunks;++i)
    {
        CHUNKBOUND(i, bl, br);
        for(j = 0;j <= n;++j)
            fen[i][j] = fen[i-1][j];
        for(j = bl;j <= br;++j)
            fupd(i, a[j], 1);
    }
}

void calcans(void)
{
    int i = 0, j = 0, k = 0;
    for(i = 1;i <= nchunks;++i)
    {
        for(j = i;j <= nchunks;++j)
        {
            int jl = 0, jr = 0; CHUNKBOUND(j, jl, jr);
            chunkans[i][j] = chunkans[i][j-1];
            for(k = jl;k <= jr;++k)
            {
                chunkans[i][j] += fqi(MAXB+i, a[k]+1, n);
                fupd(MAXB+i, a[k], 1);
            }
        }
    }
}

void init(void)
{
    onechunk = ceil(sqrt(n));
    nchunks = (n-1) / onechunk + 1;
    mapa();
    initbit();
    calcans();
}

ll bruteforce(int l, int r)
{
    ll ret = 0;
    fclear(0);
    while(l <= r)
    {
        ret += fqi(0, a[l]+1, n);
        fupd(0, a[l], 1);
        l++;
    }
    return ret;
}

ll query(int ql, int qr)
{
    int cl = CHUNKID(ql), cr = CHUNKID(qr);
    if(cr - cl < 2) return bruteforce(ql, qr);
    else {
        int i = 0;
        ll ret = chunkans[cl+1][cr-1];
        ll clr = CHUNKR(cl), crl = CHUNKL(cr);
        for(i = clr;i >= ql;i--)
        {
            ret += fqi(cr-1, 1, a[i]-1) - fqi(cl, 1, a[i]-1);
            fupd(cr-1, a[i], 1);
        }
        for(i = crl;i <= qr;++i)
        {
            ret += fqi(cr-1, a[i]+1, n) - fqi(cl, a[i]+1, n);
            fupd(cr-1, a[i], 1);
        }
        for(i = crl;i <= qr;++i) fupd(cr-1, a[i], -1);
        for(i = clr;i >= ql;i--) fupd(cr-1, a[i], -1);
        return ret;
    }
}

int main(void)
{
    int i = 0, m = 0;
    ll ql = 0, qr = 0;
    ll lans = 0;

    scanf("%d", &n);
    for(i = 1;i <= n;++i)
        scanf("%d", a+i);

    init();

    lans = 0;
    scanf("%d", &m);
    while(m--)
    {
        scanf("%lld%lld", &ql, &qr);
        ql ^= lans; qr ^= lans;
        printf("%lld\n", lans=query(ql,qr));
    }

    return 0;
}
