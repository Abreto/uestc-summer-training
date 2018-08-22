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

#include <vector>
#include <cstring>

using namespace std;
typedef vector<int> vi;
#define pb push_back

const int maxn = 100000;
const int maxt = 6.5e7 + 10;

struct __
{
    vi d[maxn + 10];
    __(void)
    {
        for (int i = 1; i <= maxn; i++)
            for (int j = i; j <= maxn; j += i)
                d[j].pb(i);
    }
    vi &operator[](const unsigned &pos) { return d[pos]; }
}_;

int n;
int ans[maxn + 10];

int mv;
int top;
int rt[maxn + 10];
int ls[maxt], rs[maxt];
void ins(int pos, int &o, int l = 1, int r = mv)
{
    if (pos < l || r < pos) return;
    if (0 == o) o = ++top;
    if (l == pos && pos == r)
    {
        ls[o] = rs[o] = 0;
    } else {
        int mid = (l + r) >> 1;
        ins(pos, ls[o], l, mid);
        ins(pos, rs[o], mid + 1, r);
    }
}

void uni(int fa, int &a, int b, int l = 1, int r = mv)
{
    if (0 == a) { a = b; return; }
    if (0 == b) { return; }
    if (l == r)
    {
        ans[fa] = max(ans[fa], l);
    } else {
        int mid = (l + r) >> 1;
        uni(fa, ls[a], ls[b], l ,mid);
        uni(fa, rs[a], rs[b], mid + 1, r);
    }
}

void abinit(void)
{
    memset(ans, -1, sizeof ans);
    top = 0;
    mv = 100000;
}

void abwork(void)
{
    static int f[maxn + 10];
    io >> n;
    for (int i = 2; i <= n; i++)
        io >> f[i];
    for (int i = 1; i <= n; i++)
    {
        int vi;
        io >> vi;
        for (auto d : _[vi])
        {
            // fprintf(stderr, "insert %d to %d\n", d, vi);
            ins(d, rt[i]);
        }
    }
    for (int i = n; i > 1; i--)
    {
        // fprintf(stderr, "uni %d to %d\n", i, f[i]);
        uni(f[i], rt[f[i]], rt[i]);
    }
    for (int i = 1; i <= n; i++)
        io << ans[i] << io.endl;
}

class ac_machine
{
    void proc(void)
    {
        abinit();
        abwork();
    }
public:
    int wa(void)
    {
        // int t;
        // io >> t;
        // while (t--) proc();
        proc();
        return 0;
    }
};

int main(void)
{
    return (new ac_machine())->wa();
}
