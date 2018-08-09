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
    abio &operator>>(char *s) { return read_s(s); }
    abio &operator<<(const char ch) { putchar(ch); return (*this); }
    abio &operator<<(const int x) { return write_int(x); }
    abio &operator<<(const long long int x) { return write_ll(x); }
    abio &operator<<(const char *s) { return write_s(s); }
}io;

#include <utility>
#include <bitset>

namespace abhash
{
    const int maxn = 1<<20;
    using namespace std;
    typedef unsigned long long ull;
    typedef pair<ull,ull> hash_t;
    ull xP[2][maxn]; ull seed[2] = {233, 772002}, p[2] = {998244353, 1000000007};
    void init(void)
    {
        xP[0][0] = xP[1][0] = 1;
        for(int i = 1;i < maxn;i++)
        {
            for(int j = 0;j < 2;j++)
            {
                xP[j][i] = (xP[j][i-1] * seed[j]) % p[j];
            }
        }
    }
    hash_t hash(const bitset<(1<<18)> &bits, int len)
    {
        ull h[2] = {0};
        for(int j = 0;j < 2;j++)
        {
            // h[j] = len;
            for(int i = 0;i < len;i++)
                if ( bits.test(i) )
                    h[j] = (h[j] + xP[j][i]) % p[j];
        }
        return make_pair(h[0], h[1]);
    }
}

#include <map>

using namespace std;


class ac_machine
{
    static const int maxs = (1<<18);
    static constexpr int val[3][2][2] = {
        {
            {0 & 0, 0 & 1},
            {1 & 0, 1 & 1}
        },
        {
            {0 | 0, 0 | 1},
            {1 | 0, 1 | 1}
        },
        {
            {0 ^ 0, 0 ^ 1},
            {1 ^ 0, 1 ^ 1}
        }
    };
    typedef abhash::hash_t hash_t;
    int n, N;
    char s[maxs+10];
    map< hash_t, int > dp;
    bitset<(1<<18)> bits[32];
    int dfs(int v)
    {
        if (0 == v) return (bits[0][0] == 1);
        int len = (1 << v);
        hash_t h = abhash::hash(bits[v], len);
        if ( dp.find(h) != dp.end() ) return dp[h];
        int ret = 0;
        for(int op = 0;op < 3;op++)
        {
            for(int i = 0;i < len;i += 2)
            {
                bits[v - 1][i >> 1] = val[ op ][ bits[v][i] ][ bits[v][i+1] ];
            }
            ret += dfs(v - 1);
        }
        return (dp[h] = ret);
    }
public:
    int wa(void)
    {
        int i;
        abhash::init();
        io >> n; N = (1<<n);
        io >> s;
        for(i = 0;i < N;i++)
        {
            bits[n][i] = s[i] - '0';
        }
        io << dfs(n) << io.endl;
        return 0;
    }
};
constexpr int ac_machine::val[3][2][2];


int main(void)
{
    return (new ac_machine())->wa();
}
