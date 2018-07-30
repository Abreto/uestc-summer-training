/**
 * 2018 Multi-University Training Contest 3.
 * Problem 100x,
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define inf (0x3f3f3f3f)

struct Matrix {
    static const int MAXN = 51;
    int e[MAXN][MAXN], n;

    inline void setn(int n) { this->n = n; }
    inline void initvalue() { memset(e, 0x3F, sizeof(e)); }

    Matrix operator = (const Matrix& o) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) 
                e[i][j] = o.e[i][j];
        return *this;
    }
    Matrix operator * (const Matrix& o) {
        Matrix m;
        m.initvalue();
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
                m.e[i][j] = min(m.e[i][j], e[i][k] + o.e[k][j]);
        return m;
    }
};

struct ac_machine
{
    static const int MAXN = 51;
    static const int MAXK = 10001;
    int n;
    Matrix g, d;
    int ans[MAXN][MAXN][MAXK];
    ac_machine(void)
    {
        init();
    }
    inline void clear(void)
    {
        g.initvalue();
        d.initvalue();
        for(int i = 1;i <= n;i++)
        {
            d.e[i][i] = 0;
        }
        for(int k = MAXK;k > 0;k--)
            for(int i = 1;i <= n;i++)
                for(int j = 1;j <= n;j++)
                    ans[i][j][k] = inf;
    }
    void init(void)
    {
        ;
    }
    inline void prepare(void)
    {
        int i, j, k;
        g.setn(n); d.setn(n);
        for(k = 0;k <= MAXK;k++)
        {
            if(k) d = g * d;
            // if(1){
            // printf("%d: \n", k);
            for(i = 1;i <= n;i++)
            {
                for(j = 1;j <= n;j++)
                {
                    // printf("%d ", d.e[i][j]);
                    ans[i][j][k] = d.e[i][j];
                }
                // puts("");
            }
            // }
        }
        for(k = MAXK-1;k > 0;k--)
        {
            // printf("%d: \n", k);
            for(i = 1;i <= n;i++)
            {
                for(j = 1;j <= n;j++)
                {
                    ans[i][j][k] = min(ans[i][j][k], ans[i][j][k+1]);
                    // printf("%d ", ans[i][j][k]);
                }
                // puts("");
            }
        }
    }
    void scan(FILE *stream)
    {
        int m, q;
        fscanf(stream, "%d%d", &n, &m);
        clear();
        while(m--)
        {
            int ui, vi, wi;
            fscanf(stream, "%d%d%d", &ui, &vi, &wi);
            g.e[ui][vi] = min(g.e[ui][vi], wi);
        }
    }
    int ac(void)
    {
        int q;
        prepare();
        fscanf(stdin, "%d", &q);
        while(q--)
        {
            int si, ti, ki;
            scanf("%d%d%d", &si, &ti, &ki);
            int ret = ans[si][ti][ki];
            printf("%d\n", (ret >= inf) ? -1 : ret );
        }
        return 0;
    }
};

int main(void)
{
    ac_machine *app = new ac_machine();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        app->scan(stdin);
        app->ac();
    }
    return 0;
}
