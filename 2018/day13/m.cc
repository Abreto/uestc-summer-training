/**
 * 2018 Multi-University Training Contest 3.
 * Problem 100x,
 * by Abreto<m@abreto.net>.
 **/
#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define inf (0x3f3f3f3f)

class abio
{
    static const unsigned BUF_SZ = 65535;
    FILE *istream, *ostream;
    char ibuf[BUF_SZ], obuf[BUF_SZ];
    size_t ip, isz;
    size_t op, osz;
    inline void clear_ibuf(void)
    {
        ip = isz = 0u;
    }
    inline void clear_obuf(void)
    {
        op = osz = 0u;
    }
    inline void clear_buffer(void)
    {
        clear_ibuf();
        clear_obuf();
    }
    inline size_t read_buffer(void)
    {
        isz = fread(ibuf, sizeof(char), BUF_SZ, istream);
        ip = 0;
        return isz;
    }
    inline size_t write_buffer(void)
    {
        if(osz)
        {
            size_t ret = fwrite(obuf+op, sizeof(char), osz-op, ostream);
            op += ret;
            if(op == osz) clear_obuf();
            return ret;
        }
        return 0;
    }
public:
    abio(FILE *input = stdin, FILE *output = stdout)
    {
        this->istream = input;
        this->ostream = output;
        clear_buffer();
    }
    abio(const char *input, const char *output)
    {
        this->istream = fopen(input, "r");
        this->istream = fopen(output, "w+");
        clear_buffer();
    }
    ~abio(void)
    {
        write_buffer();
        fclose(istream);
        fclose(ostream);
    }
    inline int getchar(void)
    {
        if(0 == isz || isz == ip) read_buffer();
        if(0 == isz || isz == ip) return EOF;
        return ibuf[ip++];
    }
    inline int putchar(int ch)
    {
        if(osz == BUF_SZ) write_buffer();
        if(osz == BUF_SZ) return EOF;
        return (obuf[osz++] = ch);
    }
    inline int read_int(int &x)
    {
        int flag = 0, ch;
        x = 0;
        while((EOF!=(ch=getchar()))&&(('-'!=ch)&&((ch<'0')||(ch>'9'))));
        if(EOF==ch) return EOF;
        if('-'==ch){flag=1;ch=getchar();}
        if(EOF==ch) return EOF;
        for(;(((ch>='0')&&(ch<='9')));ch=getchar()){x*=10;x+=(ch-'0');}
        if(flag)x*=(-1);
        return 1;
    }
    inline long long int read_ll(long long int &x)
    {
        int flag = 0, ch;
        x = 0ll;
        while((EOF!=(ch=getchar()))&&(('-'!=ch)&&((ch<'0')||(ch>'9'))));
        if(EOF==ch) return EOF;
        if('-'==ch){flag=1;ch=getchar();}
        if(EOF==ch) return EOF;
        for(;(((ch>='0')&&(ch<='9')));ch=getchar()){x*=(10ll);x+=(ch-'0');}
        if(flag)x*=(-1ll);
        return 1;
    }
    inline void write_ll(long long int x, char append = 0)
    {
        int d[20],nd=0;
        if(0==x) putchar('0');
        if(x<0){putchar('-');x=-x;}
        while(x){d[nd++]=x%10;x/=10;}
        while(nd--)putchar('0'+d[nd]);
        if(append)putchar(append);
    }
}io;

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
    static const int MAXSQK = 101;
    int n;
    Matrix g, d[MAXSQK], d100[MAXSQK];
    int dis[MAXN][MAXN], f[MAXN][MAXN];
    ac_machine(void)
    {
        init();
    }
    inline void clear(void)
    {
        g.initvalue();
        d[0].initvalue();
        d100[0].initvalue();
        for(int i = 1;i <= n;i++)
                d[0].e[i][i] = d100[0].e[i][i] = 0;
    }
    void init(void)
    {
        ;
    }
    inline void prepare(void)
    {
        int i, j, k;
        g.setn(n);
        d[0].setn(n);
        d100[0].setn(n);
        for(k = 1;k < MAXSQK;k++)
        {
            d[k].setn(n);
            d[k] = g * d[k-1];
        }
        d100[1].setn(n); d100[1] = d[100];
        for(k = 2;k < MAXSQK;k++)
        {
            d100[k].setn(n);
            d100[k] = d[100] * d100[k-1];
        }
        for(i = 1;i <= n;i++)
            for(j = 1;j <= n;j++)
                dis[i][j] = (i==j) ? (0) : (g.e[i][j]);
        for(k = 1;k <= n;k++)
            for(i = 1;i <= n;i++)
                for(j = 1;j <= n;j++)
                    dis[i][j] = min(dis[i][j], dis[i][k]+dis[k][j]);
        for(k = 0;k < MAXSQK;k++)
        {
            for(i = 1;i <= n;i++)
                for(j = 1;j <= n;j++)
                {
                    f[i][j] = inf;
                    // d[k].e[i][j] = min(d[k].e[i][j], d[k+1].e[i][j]);
                    // d100[k].e[i][j] = min(d100[k].e[i][j], d100[k+1].e[i][j]);
                }
            for(i = 1;i <= n;i++)
                for(j = 1;j <= n;j++)
                    for(int l = 1;l <= n;l++)
                        f[i][j] = min(f[i][j], d[k].e[i][l] + dis[l][j]);
            for(i = 1;i <= n;i++)
                for(j = 1;j <= n;j++)
                    d[k].e[i][j] = f[i][j];
        }
    }
    void scan(FILE *stream)
    {
        int m;
        io.read_int(n); io.read_int(m);
        //scanf("%d%d", &n, &m);
        clear();
        while(m--)
        {
            int ui, vi, wi;
            io.read_int(ui);
            io.read_int(vi);
            io.read_int(wi);
            // scanf("%d%d%d", &ui, &vi, &wi);
            g.e[ui][vi] = min(g.e[ui][vi], wi);
        }
    }
    int ask(int u, int v, int a, int b)
    {
        int ret = inf;
        for(int i = 1;i <= n;i++)
            ret = min(ret, d100[a].e[u][i] + d[b].e[i][v]);
        return ret;
    }
    int ac(void)
    {
        int q;
        prepare();
        io.read_int(q);
        // scanf("%d", &q);
        while(q--)
        {
            int si, ti, ki;
            io.read_int(si); io.read_int(ti); io.read_int(ki);
            //scanf("%d%d%d", &si, &ti, &ki);
            assert(ki <= 10000);
            int ans = ask(si, ti, ki / 100, ki % 100);
            io.write_ll((ans>=inf)?(-1):ans, '\n');
            // printf("%d\n", (ans >= inf) ? -1 : ans );
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
