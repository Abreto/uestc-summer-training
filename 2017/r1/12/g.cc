/* UESTC 2017 Summer Training #12 Div.2. Problem G, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#define GET(x,i)    (((x)>>(i))&1)

#define MAXN    16
#define MAXV    (MAXN*MAXN)

int d[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
int dn[8][2] = {{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};
int knd[128][8][2];
int nknd[128];
int otd[128][8];
int notd[128];

void init(void)
{
    int i = 0, j = 0;
    nknd['K'] = 8;
    for(i = 0;i < 8;++i)
        for(j = 0;j < 2;++j)
            knd['K'][i][j] = d[i][j];
    nknd['N'] = 8;
    for(i = 0;i < 8;++i)
        for(j = 0;j < 2;++j)
            knd['N'][i][j] = dn[i][j];
    notd['Q'] = 8;
    for(i = 0;i < 8;++i)
        otd['Q'][i] = i;
    notd['R'] = 4;
    otd['R'][0] = 1; otd['R'][1] = 3;
    otd['R'][2] = 4; otd['R'][3] = 6;
    notd['B'] = 4;
    otd['B'][0] = 0; otd['B'][1] = 2;
    otd['B'][2] = 5; otd['B'][3] = 7;
}

int w, h;
int gird[MAXN][MAXN];
int G[MAXV][MAXV];
int deg[MAXV];
int npie;
int pie2v[16];

#define HASH(i,j) ((i)*w+j+1)

void add_edge(int u, int v)
{
    if(!G[u][v])
    {
        G[u][v] = G[v][u] = 1;
        deg[u]++;
        deg[v]++;
    }
}

void clear(void)
{
    memset(G, 0, sizeof(G));
    memset(deg, 0, sizeof(deg));
    npie = 0;
}

void cc(int x, int y, int xx, int yy)
{
    if(xx >= 0 && xx < h && yy >= 0 && yy < w)
    {
        if('E' != gird[xx][yy])
            add_edge(HASH(x,y), HASH(xx,yy));
    }
}

void handle(int x, int y)
{
    int p = gird[x][y];
    if('K' == p || 'N' == p)
    {
        for(int i = 0;i < 8;++i)
        {
            int nx = x+knd[p][i][0], ny = y+knd[p][i][1];
            cc(x,y,nx,ny);
        }
    } else {
        for(int i = 0;i < notd[p];++i)
        {
            int dx = d[otd[p][i]][0], dy = d[otd[p][i]][1];
            int nx = 0, ny = 0;
            for((nx=x+dx),(ny=y+dy);nx >= 0 && nx < h && ny >= 0 && ny < w;(nx+=dx),(ny+=dy))
                cc(x,y,nx,ny);
        }
    }
}

int rm(void)
{
    int i = 0, j = 0;
    int s = 0, ans = (1<<npie);
    int maxpie = 0;
    for(s = 1;s < ans;++s)
    {
        int ones[16] = {0};
        int nones = 0;
        int ok = 1;
        for(i = 0;i < npie;++i)
            if(GET(s,i))
                ones[nones++] = i;
        for(i = 0;i < nones;++i)
        {
            for(j = 0;j < nones;++j)
                if(i!=j && G[pie2v[ones[i]]][pie2v[ones[j]]])
                {
                    ok = 0;
                    break;
                }
        }
        if(ok && nones > maxpie) maxpie = nones;
    }
    return npie-maxpie;
}

void proccess(void)
{
    int i = 0, j = 0;
    char piece[4];
    scanf("%d", &w);
    scanf("%d", &h);
    for(i = 0;i < h;++i)
        for(j = 0;j < w;++j)
        {
            scanf("%s", piece);
            gird[i][j] = piece[0];
        }
    for(i = 0;i < h;++i)
        for(j = 0;j < w;++j)
            if('E' != gird[i][j])
            {
                pie2v[npie++] = HASH(i,j);
                handle(i,j);
            }
    printf("Minimum Number of Pieces to be removed: %d\n", rm());
}

int main(void)
{
    char sep[8] = {0};
    init();
    while(EOF!=scanf("%s", sep))
    {
        clear();
        proccess();
        scanf("%s", sep);
    }
    return 0;
}
