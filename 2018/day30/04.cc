#include <cstdio>

class abio
{
    static const unsigned BUF_SZ = 65536;
    FILE *istream, *ostream;
    char ibuf[BUF_SZ], obuf[BUF_SZ];
    bool reached_eof;
    size_t ip, isz;
    size_t op, osz;
    inline void clear_ibuf(void) { ip = isz = 0u; }
    inline void clear_obuf(void) { op = osz = 0u; }
    inline void clear_buffer(void)
    {
        reached_eof = false;
        clear_ibuf();
        clear_obuf();
    }
    inline size_t read_buffer(void)
    {
        isz = std::fread(ibuf, sizeof(char), BUF_SZ, istream);
        ip = 0;
        return isz;
    }
    inline size_t write_buffer(void)
    {
        if(osz)
        {
            size_t ret = std::fwrite(obuf+op, sizeof(char), osz-op, ostream);
            op += ret;
            if(op == osz) clear_obuf();
            return ret;
        }
        return 0;
    }
    inline abio &reach_eof(void)
    {
        reached_eof = true;
        return (*this);
    }
public:
    static const char endl = '\n';
    abio(FILE *input = stdin, FILE *output = stdout)
    {
        this->istream = input;
        this->ostream = output;
        clear_buffer();
    }
    abio(const char *input, const char *output)
    {
        this->istream = std::fopen(input, "r");
        this->istream = std::fopen(output, "w+");
        clear_buffer();
    }
    ~abio(void)
    {
        write_buffer();
        std::fclose(istream);
        std::fclose(ostream);
    }
    operator bool() const
    {
        return (!reached_eof);
    }
    inline int getchar(void)
    {
        if(isz == ip) read_buffer();
        if(isz == ip) return EOF;
        return ibuf[ip++];
    }
    inline int putchar(int ch)
    {
        if(osz == BUF_SZ) write_buffer();
        if(osz == BUF_SZ) return EOF;
        return (obuf[osz++] = ch);
    }
    abio &read_int(int &x)
    {
        int flag = 0, ch = getchar();
        for (;(EOF!=ch)&&((ch<'0')||(ch>'9'));ch=getchar()) if ('-' == ch) flag = 1;
        if (EOF == ch) return (this->reach_eof()); x = 0;
        for (;(ch>='0')&&(ch<='9');ch=getchar()) x = x * 10 + (ch - '0');
        if ( flag ) x *= (-1);
        return (*this);
    }
    abio &read_ll(long long int &x)
    {
        int flag = 0, ch = getchar();
        for (;(EOF!=ch)&&((ch<'0')||(ch>'9'));ch=getchar()) if ('-' == ch) flag = 1;
        if (EOF == ch) return (this->reach_eof()); x = 0ll;
        for (;(ch>='0')&&(ch<='9');ch=getchar()) x = x * 10ll + (ch - '0');
        if ( flag ) x *= (-1ll);
        return (*this);
    }
    abio &read_unsigned(unsigned &x)
    {
        int ch = getchar();
        for(;(EOF != ch) && ((ch < '0') || (ch > '9'));ch = getchar());
        if (EOF == ch) return (this->reach_eof()); x = 0u;
        for(;(ch >= '0') && (ch <= '9');ch = getchar()) x = x * 10u + (ch - '0');
        return (*this);
    }
    abio &read_ull(unsigned long long int &x)
    {
        int ch = getchar();
        for(;(EOF != ch) && ((ch < '0') || (ch > '9'));ch = getchar());
        if (EOF == ch) return (this->reach_eof()); x = 0ull;
        for(;(ch >= '0') && (ch <= '9');ch = getchar()) x = x * 10ull + (ch - '0');
        return (*this);
    }
    /* set interrupt as '\n' to read a whole line. */
    abio &read_s(char *s, const char interrupt = ' ')
    {
        int ch = getchar();
        while((EOF!=ch)&&(ch<'!'||ch>'~'))ch=getchar();
        if(EOF==ch) return (this->reach_eof());
        for(;(EOF!=ch)&&(interrupt!=ch)&&(ch>=' '&&ch<='~');ch=getchar())(*s++)=ch;
        (*s)=0;
        return (*this);
    }
    abio &write_int(int x, char append = 0)
    {
        int d[20],nd=0;
        if(0==x) putchar('0');
        if(x<0){putchar('-');x=-x;}
        while(x){d[nd++]=x%10;x/=10;}
        while(nd--)putchar('0'+d[nd]);
        if(append)putchar(append);
        return (*this);
    }
    abio &write_ll(long long int x, char append = 0)
    {
        int d[20],nd=0;
        if(0==x) putchar('0');
        if(x<0){putchar('-');x=-x;}
        while(x){d[nd++]=x%10;x/=10;}
        while(nd--)putchar('0'+d[nd]);
        if(append)putchar(append);
        return (*this);
    }
    abio &write_unsigned(unsigned x, char append = 0)
    {
        int d[20],nd=0;
        if(0==x) putchar('0');
        while(x){d[nd++]=x%10;x/=10;}
        while(nd--)putchar('0'+d[nd]);
        if(append)putchar(append);
        return (*this);
    }
    abio &write_ull(unsigned long long int x, char append = 0)
    {
        int d[20],nd=0;
        if(0==x) putchar('0');
        while(x){d[nd++]=x%10;x/=10;}
        while(nd--)putchar('0'+d[nd]);
        if(append)putchar(append);
        return (*this);
    }
    abio &write_s(const char *s, char append = 0)
    {
        while(*s) putchar(*s++);
        if(append) putchar(append);
        return (*this);
    }
    abio &operator>>(char &ch)
    {
        ch = getchar();
        if(EOF==ch) return (this->reach_eof());
        return (*this);
    }
    abio &operator>>(int &x) { return read_int(x); }
    abio &operator>>(long long int &x) { return read_ll(x); }
    abio &operator>>(unsigned &x) { return read_unsigned(x); }
    abio &operator>>(unsigned long long int &x) { return read_ull(x); }
    abio &operator>>(char *s) { return read_s(s); }
    abio &operator<<(const char ch) { putchar(ch); return (*this); }
    abio &operator<<(const int x) { return write_int(x); }
    abio &operator<<(const long long int x) { return write_ll(x); }
    abio &operator<<(const unsigned x) { return write_unsigned(x); }
    abio &operator<<(const unsigned long long int x) { return write_ull(x); }
    abio &operator<<(const char *s) { return write_s(s); }
}io;

#include <cmath>
#include <algorithm>
using namespace std;
typedef double abfloat;

const int maxn = 100100;
const abfloat inf = 1e30;
const abfloat eps = 1e-9;

int N;
int A, B;
abfloat dA, dB;
int Rs[maxn];
inline int /* 1 -> N */ rid(int r) { return lower_bound(Rs, Rs + N, r) - Rs + 2; }
struct abp
{
    int L, R;
    abp(int l = 0, int r = 0) : L(l), R(r) { }
    bool operator<(const abp &o) const { return L < o.L; }
}p[maxn];

abfloat w[maxn][2];
struct segtree
{
    static int n;
    static void setn(int nn) { n = nn; }
    abfloat mv[maxn << 2];
    abfloat add[maxn << 2], mk[maxn << 2];
    void maintain(int o)
    {
        mv[o] = min(mv[o << 1], mv[o << 1 | 1]);
    }
    void addall(int o, abfloat delta)
    {
        mv[o] += delta;
        add[o] += delta;
    }
    void mkall(int o, abfloat tobe)
    {
        mv[o] = tobe;
        mk[o] = tobe;
        add[o] = 0.;
    }
    void pushdown(int o)
    {
        /* mk is considered before add */
        if (mk[o] > eps)
        {
            mkall(o << 1, mk[o]);
            mkall(o << 1 | 1, mk[o]);
            mk[o] = 0.;
        }
        if (add[o] > eps)
        {
            addall(o << 1, add[o]);
            addall(o << 1 | 1, add[o]);
            add[o] = 0.;
        }
    }
    void build(int o = 1, int l = 1, int r = n)
    {
        if (r < l) return;
        mv[o] = inf;
        add[o] = mk[o] = 0.;
        if (l < r)
        {
            int mid = (l + r) >> 1;
            build(o<<1, l, mid);
            build(o<<1|1, mid+1, r);
        }
    }
    abfloat qry(int L = 1, int R = n, int o = 1, int l = 1, int r = n)
    {
        if (R < l || r < L) return inf;
        if (L <= l && r <= R)
        {
            return mv[o];
        } else {
            int mid = (l + r) >> 1;
            pushdown(o);
            return min(qry(L, R, o<<1, l, mid), qry(L, R, o<<1|1, mid+1, r));
        }
    }
    void upd(int pos, abfloat v, int o = 1, int l = 1, int r = n)
    {
        if (pos < l || r < pos) return;
        if (l == pos && pos == r)
        {
            mv[o] = min(mv[o], v);
        } else {
            int mid = (l + r) >> 1;
            pushdown(o);
            if (pos <= mid) upd(pos, v, o << 1, l, mid);
            else upd(pos, v, o << 1 | 1, mid + 1, r);
            maintain(o);
        }
    }
    void debug(int o = 1, int l = 1, int r = n)
    {
        if (r < l) return;
        // fprintf(stderr, "(%d,%d): %lf, %lf, %lf\n", l, r, mv[o], add[o], mk[o]);
        if (l < r)
        {
            int mid = (l + r) >> 1;
            debug(o << 1, l, mid);
            debug(o << 1 | 1, mid + 1, r);
        }
    }
}f[2];
int segtree::n;

class ac_machine
{
public:
    int wa(void)
    {
        // io >> A >> B >> N;
        scanf("%d%d%d", &A, &B, &N);
        dA = A; dB = B;
        for (int i = 0; i < N; i++)
        {
            // io >> p[i].L;
            scanf("%d", &(p[i].L));
        }
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &(p[i].R));
            // io >> p[i].R;
            Rs[i] = p[i].R;
        }
        sort(Rs, Rs + N); sort(p, p + N);
        for (int i = 0; i < N; i++)
        {
            abfloat dx = p[i].L - p[i].R;
            w[i][0] = sqrt(dx * dx + dB * dB);
            w[i][1] = dB + min(p[i].L + p[i].R, A - p[i].L + A - p[i].R);
            // fprintf(stderr, "%d: %lf, %lf\n", i, w[i][0], w[i][1]);
            p[i].R = rid(p[i].R);
            // fprintf(stderr, "%d: %d,%d\n", i, p[i].L, p[i].R);
        }
        segtree::setn(N + 1);
        for (int i = 0; i < 2; i++) f[i].build();
        for (int i = 0; i < 2; i++) f[i].upd(1, w[0][i]);
        // f[0].debug(); f[1].debug();
        for (int i = 1; i < N; i++)
        {
            int j;
            abfloat m[2];
            for (j = 0; j < 2; j++) m[j] = f[j].qry(1, p[i].R - 1);
            // fprintf(stderr, "%lf, %lf\n", m[0], m[1]);
            // fprintf(stderr, "after qry\n"); f[0].debug(); f[1].debug();
            if (p[i - 1].R > p[i].R)
                for (j = 0; j < 2; j++) f[j].mkall(1, inf);
            // fprintf(stderr, "after mkall\n"); f[0].debug(); f[1].debug();
            for (j = 0; j < 2; j++) f[j].upd(p[i - 1].R, m[j ^ 1]);
            // fprintf(stderr, "after upd\n"); f[0].debug(); f[1].debug();
            for (j = 0; j < 2; j++) f[j].addall(1, w[i][j]);
            // fprintf(stderr, "after add\n"); f[0].debug(); f[1].debug();
        }
        abfloat ans = min(f[0].mv[1], f[1].mv[1]);
        // fprintf(stderr, "after qry\n"); f[0].debug(); f[1].debug();
        if (ans >= inf - eps) puts("-1");
        else printf("%.14lf\n", ans);
        return 0;
    }
};

int main(void)
{
    return (new ac_machine())->wa();
}
