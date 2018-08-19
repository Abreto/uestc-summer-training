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

#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

typedef long long int ll;
typedef vector<int> vi;
#define pb push_back
const int maxn = 100100;
const ll p = 998244353;
inline void add(ll &dest, ll delta)
{
    dest = dest + delta;
    if (dest < 0) dest += p;
    if (dest > p) dest -= p;
}
//inline void mul(ll &dest, ll times) { dest = (dest * times) % p; }
inline void mul(ll &dest, ll times)
{
    dest = dest * times;
    dest -= dest / p * p;
}
ll qow(ll a, ll x)
{
    ll ret = 1ll;
    while (x)
    {
        if (1 & x) mul(ret, a);
        mul(a, a);
        x >>= 1;
    }
    return ret;
}

struct __
{
    vi divs[maxn];
    __(void)
    {
        for (int i = 2; i < maxn; i++)
        {
            for (int j = i; j < maxn; j += i)
            {
                divs[j].pb(i);
            }
        }
    }
    vi &operator[](unsigned pos) { return divs[pos]; }
}_;

class ac_machine
{
    int n, M;
    int have[maxn];
    int cnt[maxn];  /* appearence of divisor */
    vi divs;
    ll f[maxn];
    bool in_div(int x)
    {
        auto p = lower_bound(divs.begin(), divs.end(), x);
        return ((p != divs.end()) && (x == (*p)));
    }
    ll calc(ll m)
    {
        divs.clear();
        for (int i = 1; i * i <= m; i++)
        {
            if (m % i) continue;
            int j = m / i;
            divs.pb(i);
            if (j != i) divs.pb(j);
        }
        sort(divs.begin(), divs.end()); // unique(divs.begin(), divs.end()); // comment this if get TLE
        ll ret = 0ll;
        for (auto it = divs.end(); it != divs.begin(); it--)
        {
            ll d = *(it - 1);
            // assert(d < maxn);
            f[d] = qow(1ll + m, cnt[d]);
            add(f[d], p - 1);
            // for (int i = (d << 1); i <= m; i += d)
                // if (in_div(i))
                    // add(f[d], p - f[i]);
            for (auto kd = _[m / d].begin(); kd != _[m / d].end(); kd++)
                add(f[d], p - f[(*kd) * d]);
            add(ret, f[d] * d % p);
        }
        for (auto it = divs.begin(); it != divs.end(); it++)
        {
            f[ *it ] = 0;
        }
        // fprintf(stderr, "calc(%lld) is %lld\n", m, ret);
        return ret;
    }
    void proc(void)
    {
        int i, j;
        io >> n >> M;
        memset(have, 0, sizeof have); memset(cnt, 0, sizeof cnt);
        for (i = 0; i < n; i++)
        {
            int Bi;
            io >> Bi;
            have[Bi] ++;
        }
        for (i = 1; i < maxn; i++)
        {
            for (j = i; j < maxn; j += i)
            {
                cnt[i] += have[j];
            }
        }
        int ans = 0;
        // fprintf(stderr, "M is %d\n", M);
        for (i = 1; i <= M; i++)
        {
            // fprintf(stderr, "calculating %d\n", i);
            ll wi = calc(i);
            mul(wi, qow(i, p - 2));
            ans ^= wi;
        }
        io << ans << io.endl;
    }
public:
    int wa(void)
    {
        int t;
        io >> t;
        while (t--) proc();
        return 0;
    }
};

int main(void)
{
    return (new ac_machine())->wa();
}
