#include <cstdio>

using namespace std;

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
    inline abio &read_int(int &x)
    {
        int flag = 0, ch;
        x = 0;
        while((EOF!=(ch=getchar()))&&(('-'!=ch)&&((ch<'0')||(ch>'9'))));
        if(EOF==ch) return (*this);
        if('-'==ch){flag=1;ch=getchar();}
        if(EOF==ch) return (*this);
        for(;(((ch>='0')&&(ch<='9')));ch=getchar()){x*=10;x+=(ch-'0');}
        if(flag)x*=(-1);
        return (*this);
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

typedef struct acmachine
{
    typedef long long int ll;
    static const int MAXL = 16;
    int L;
    int A[MAXL];
    ll sum[MAXL<<2][MAXL<<2];
    void pre(void)
    {
        int i, j, k;
        k = 0;
        for(i = 0;i < (L<<2);i++)
        {
            for(j = 0;j <= i;j++)
            {
                if(j < (L<<1) && (i-j) < (L<<1)) sum[j][i-j] = A[k];
                k = (k+1) % L;
            }
        }
        L <<= 1;
        for(i = 0;i < L;i++)
        {
            for(j = 0;j < L;j++)
            {
                if(i) sum[i][j] += sum[i-1][j];
                if(j) sum[i][j] += sum[i][j-1];
                if(i&&j) sum[i][j] -= sum[i-1][j-1];
            }
        }
    }
    ll f(int x, int y)
    {
        if(x < 0 || y < 0) return 0;
        return  sum[L-1][L-1] * (x/L) * (y/L) +
                sum[L-1][y%L] * (x/L) +
                sum[x%L][L-1] * (y/L) +
                sum[x%L][y%L];
    }
    void scan(void)
    {
        int i;
        io.read_int(L);
        // scanf("%d", &L);
        for(i = 0;i < L;i++)
            io.read_int(A[i]);
            // scanf("%d", A+i);
    }
    int ac(void)
    {
        int Q;
        pre();
        io.read_int(Q);
        // scanf("%d", &Q);
        while(Q--)
        {
            int x0, y0, x1, y1;
            io.read_int(x0).read_int(y0).read_int(x1).read_int(y1);
            // scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
            io.write_ll(f(x1,y1) - f(x1,y0-1) - f(x0-1,y1) + f(x0-1,y0-1), '\n');
            // printf("%lld\n", f(x1,y1) - f(x1,y0-1) - f(x0-1,y1) + f(x0-1,y0-1));
        }
        return 0;
    }
}am;

int main(void)
{
    am *app = new am();
    int T;
    io.read_int(T);
    // scanf("%d", &T);
    while(T--)
    {
        app->scan();
        app->ac();
    }
    return 0;
}
