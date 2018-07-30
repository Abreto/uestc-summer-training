/* 牛客网暑期ACM多校训练营（第二场）. Probem H, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <algorithm>
#include <utility>

using namespace std;
typedef long long int ll;
#define neginf  (1ll<<63)
struct pli
{
    ll first; int second;
    pli(void):first(neginf),second(0){}
    pli(ll aa, int bb):first(aa),second(bb){}
};
#define mp pli

#define MAXN    (400004)
struct edge {
    int v;
    edge *n;
    edge(void):v(0),n(NULL){}
    edge(int vv, edge *nn):v(vv),n(nn){}
}E[MAXN<<1];
int ne;
edge *front[MAXN];
void add_edge(int u, int v)
{
    E[ne] = edge(v, u[front]);
    u[front] = E+ne;
    ne++;
}

int n;
ll a[MAXN];
ll dp[MAXN][4][2];
#define SAVE_MAX_N  4
pli mv[MAXN][4][2][SAVE_MAX_N]; /* max values of [j][k] in sons of u */
void outmv(int u, int j, int k)
{
    printf("%d,%d,%d:", u, j, k);
    for(int i = 0;i < SAVE_MAX_N;i++)
        printf("(%lld,%d)", mv[u][j][k][i].first, mv[u][j][k][i].second);
    puts("");
}

void myinit(void)
{
    int i, j, k;
    for(i = 0;i <= n;i++)
    {
        for(j = 0;j < 4;j++)
        {
            dp[i][j][0] = dp[i][j][1] = neginf;
            for(k = 0;k < SAVE_MAX_N;k++)
                mv[i][j][0][k] = mv[i][j][1][k] = mp(neginf, 0);
        }
    }
}

/**
 * dp[v][j][k] <- val
 * insert val to mv[u][j][k]
 **/
void updmv(int u, int j, int k, ll val, int v)
{
    dp[v][j][k] = max(dp[v][j][k], val);
    val = dp[v][j][k];
    for(int i = 0;i < SAVE_MAX_N;i++)
    {
        if(val == mv[u][j][k][i].first && v == mv[u][j][k][i].second) return;
        if(val > mv[u][j][k][i].first)
        {
            pli last = mv[u][j][k][SAVE_MAX_N-1];
            for(int l = SAVE_MAX_N-1;l > i;l--)
                mv[u][j][k][l] = mv[u][j][k][l-1];
            mv[u][j][k][i] = mp(val, v);
            //outmv(u,j,k);
            /* remove v */
            for(int l = i+1;l < SAVE_MAX_N;l++)
                if(mv[u][j][k][l].second == v)
                {
                    for(;l < SAVE_MAX_N-1;l++)
                        mv[u][j][k][l] = mv[u][j][k][l+1];
                    mv[u][j][k][SAVE_MAX_N-1] = last;
                    break;
                }
            return;
        }
    }
}
ll getmax2(int u, int j1, int k1, int j2, int k2)
{
    int i1 = 0, i2 = 0;
    ll ret = neginf;
    for(i1 = 0;i1 < 3;i1++)
        for(i2 = 0;i2 < 3;i2++)
        {
            if(mv[u][j1][k1][i1].second != mv[u][j2][k2][i2].second && mv[u][j1][k1][i1].second != 0 && mv[u][j2][k2][i2].second != 0)
                ret = max(ret, mv[u][j1][k1][i1].first + mv[u][j2][k2][i2].first);
        }
    return ret;
}
ll getmax3(int u, int j[], int k[])
{
    int i[3] = {0};
    ll ret = neginf;
    for(i[0] = 0;i[0] < 3;i[0]++)
    for(i[1] = 0;i[1] < 3;i[1]++)
    for(i[2] = 0;i[2] < 3;i[2]++)
    {
        pli c[3];
        for(int l = 0;l < 3;l++) c[l] = mv[u][j[l]][k[l]][i[l]];
        if(c[0].second == 0 || c[1].second == 0 || c[2].second == 0) continue;
        if(c[0].second != c[1].second && c[0].second != c[2]. second && c[1].second != c[2].second)
            ret = max(ret, c[0].first + c[1].first + c[2].first);
    }
    return ret;
}
#define REP(offset, limit) for(i[offset]=0;i[offset]<limit;i[offset]++)
ll getmax4(int u, int j[], int k[])
{
    int i[4] = {0};
    ll ret = neginf;
    REP(0,4) REP(1,4) REP(2,4) REP(3,4)
    {
        ll sum = 0;
        pli c[4];
        for(int l = 0;l < 4;l++)
        {
            c[l] = mv[u][j[l]][k[l]][i[l]];
            if(0 == c[l].second) goto next_conbination;
        }
        for(int l = 0;l < 4;l++)
            for(int h = 0;h < 4;h++)
                if(l != h && c[l].second == c[h].second)
                    goto next_conbination;
        for(int l = 0;l < 4;l++)
            sum += c[l].first;
        ret = max(ret, sum);
next_conbination:;
    }
    return ret;
}

void dfs(int u, int f)
{
    int is_leaf = 1;
    for(edge *e = u[front];e;e = e->n)
    {
        if(e->v != f)
        {
            dfs(e->v, u);
            is_leaf = 0;
        }
    }
    if(is_leaf)
    {
        updmv(f, 1, 1, a[u], u);
        updmv(f, 1, 0, a[u], u);
    } else {
        /* calculate [*][1] */ {
            ll maxv = 0;
            /* [1][1] */
            maxv = mv[u][1][1][0].first;
            updmv(f, 1, 1, a[u]+maxv, u);
            /* [2][1] */
            maxv = mv[u][2][1][0].first;
            maxv = max(maxv, getmax2(u, 1,1, 1,0));
            updmv(f, 2, 1, a[u]+maxv, u);
            /* [3][1] */
            maxv = mv[u][3][1][0].first;
            maxv = max(maxv, getmax2(u, 2,1, 1,0));
            maxv = max(maxv, getmax2(u, 1,1, 2,0));
            int js[] = {1,1,1}, ks[] = {1,0,0};
            maxv = max(maxv, getmax3(u, js, ks));
            updmv(f, 3, 1, a[u]+maxv, u);
        }
        /* calculate [*][0] */ {
            ll maxv = 0;
            for(int i = 1;i <= 3;i++)
                updmv(f, i, 0, dp[u][i][1], u);
            /* [1][0] */
            updmv(f, 1, 0, mv[u][1][0][0].first, u);
            updmv(f, 1, 0, a[u]+getmax2(u, 1,1, 1,1), u);
            /* [2][0] */ {
                maxv = mv[u][2][0][0].first;
                maxv = max(maxv, getmax2(u, 1,0, 1,0));
                int js[] = {1,1,1}, ks[] = {1,1,0};
                maxv = max(maxv, a[u]+getmax3(u, js, ks));
                maxv = max(maxv, a[u]+getmax2(u, 2,1, 1,1));
                updmv(f, 2, 0, maxv, u);
            }
            /* [3][0] */ {
                /* no connection with u */ {
                    maxv = mv[u][3][0][0].first;
                    maxv = max(maxv, getmax2(u, 2,0, 1,0));
                    int js[] = {1,1,1}, ks[] = {0,0,0};
                    maxv = max(maxv, getmax3(u, js, ks));
                    updmv(f, 3, 0, maxv, u);
                }
                /* conjuction through u */ {
                    maxv = getmax2(u, 2,1, 2,1);
                    {
                        int js[] = {2,1,1}, ks[] = {1,1,0};
                        maxv = max(maxv, getmax3(u, js, ks));
                    }
                    {
                        int js[] = {1,1,2}, ks[] = {1,1,0};
                        maxv = max(maxv, getmax3(u, js, ks));
                    }
                    {
                        int js[] = {1,1,1,1}, ks[] = {1,1,0,0};
                        maxv = max(maxv, getmax4(u, js, ks));
                    }
                    updmv(f, 3, 0, a[u]+maxv, u);
                }
            }
        }
    }
    //printf("visited %d\n", u);
    //printf("0: %lld %lld %lld\n", dp[u][1][0], dp[u][2][0], dp[u][3][0]);
    //printf("1: %lld %lld %lld\n", dp[u][1][1], dp[u][2][1], dp[u][3][1]);
}

int main(void)
{
    int i, u, v;
    scanf("%d", &n);
    for(i = 1;i <= n;i++)
        scanf("%lld", a+i);
    for(i = 1;i < n;i++)
    {
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    myinit();
    dfs(1, 0);
    ll ans = dp[1][3][0];
    if(ans < 0) ans = 0;
    printf("%lld\n", dp[1][3][0]);
    return 0;
}
