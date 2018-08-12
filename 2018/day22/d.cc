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
#include <cassert>
#include <algorithm>

using namespace std;
typedef long long int ll;
#define pb push_back

struct abnhalls
{
    ll num[64];
    abnhalls(void)
    {
        num[0] = 1ll;
        for(int i = 1;i <= 36;i++)
        {
            num[i] = num[i-1] * 3ll;
        }
    }
    ll operator[](const unsigned &pos) const
    {
        return num[pos];
    }
}nhalls;

struct hall
{
    ll r, t;    /* level, theta */
    hall(ll nr = 0, ll nt = 0) : r(nr), t(nt) {}
    void s(void)
    {
        t++;
        if (t >= nhalls[r]) t -= nhalls[r];
    }
    void a(void)
    {
        t--;
        if (t < 0) t += nhalls[r];
    }
    void g(void)
    {
        r--;
        t /= 3;
    }
    void c(void)
    {
        r++;
        t *= 3;
    }
    void scan(const char *routes)
    {
        char dir;
        r = 0; t = 0;
        while ( (dir = *routes) )
        {
            if ('g' == dir)
            {
                assert( 0 == t % 3ll );
                r--;
                t /= 3ll;
            } else if ('c' == dir) {
                r++;
                t *= 3ll;
            } else {
                ll circle = nhalls[r];
                if('s' == dir) {
                    t++;
                    if (t >= circle) t -= circle;
                } else {
                    assert('a' == dir);
                    t--;
                    if (t < 0ll) t += circle;
                }
            }
            routes++;
        }
    }
    ll t_at(int nr)
    {
        ll ret = t;
        assert(nr >= r);
        while (nr > r)
        {
            ret *= 3ll;
            nr--;
        }
        return ret;
    }
};

struct abreverse
{
    char abmap[256];
    abreverse(void)
    {
        abmap[ 'g' ] = 'c';
        abmap[ 'c' ] = 'g';
        abmap[ 's' ] = 'a';
        abmap[ 'a' ] = 's';
    }
    char operator[](const int &pos) const
    {
        return abmap[pos];
    }
}rev;

class ac_machine
{
    static const int maxlen = 64;
    char sr[maxlen], tr[maxlen];
    hall s, t;
    vector<char> go[2];
    ll rdis(ll a, ll b, ll cir)
    {
        ll delta = a - b + cir;
        delta %= cir;
        return min(delta, cir - delta);
    }
public:
    int wa(void)
    {
        io >> sr >> tr;
        s.scan(sr); t.scan(tr);
        // fprintf(stderr, "(%lld,%lld)\n", s.r, s.t);
        // fprintf(stderr, "(%lld,%lld)\n", t.r, t.t);
        while ( !(s.r == t.r && rdis(s.t, t.t, nhalls[s.r]) <= 5) )
        {
            int reversed = 0;
            hall *outer = &s, *inner = &t;
            if ( s.r < t.r )
            {
                outer = &t;
                inner = &s;
                reversed = 1;
            }
            // fprintf(stderr, "rev: %d, o(%lld,%lld), i(%lld,%lld)\n", reversed, outer->r, outer->t, inner->r, inner->t);
            if ((outer->r) > (inner->r))
            {
                ll nh = nhalls[outer->r];
                ll target = inner->t_at(outer->r);
                ll compar = (target - (outer->t) + nh) % nh;
                if ( (compar<<1) <= nh )
                {
                    /* s */
                    while ( (outer->t) % 3 )
                    {
                        outer->s();
                        go[reversed].pb('s');
                    }
                    outer->g();
                    go[reversed].pb('g');
                } else {
                    /* a */
                    while ((outer->t) % 3)
                    {
                        outer->a();
                        go[reversed].pb('a');
                    }
                    outer->g();
                    go[reversed].pb('g');
                }
            } else if (outer->r == inner->r) {
                ll nh = nhalls[outer->r];
                ll compar = ((inner->t) - (outer->t) + nh) % nh;
                if ( (compar<<1) <= nh )
                {
                    /* s */
                    while( (outer->t) % 3 )
                    {
                        outer->s();
                        go[reversed].pb('s');
                    }
                    outer->g();
                    go[reversed].pb('g');
                } else {
                    /* a */
                    while( (outer->t) % 3 )
                    {
                        outer->a();
                        go[reversed].pb('a');
                    }
                    outer->g();
                    go[reversed].pb('g');
                }
            } else {
                assert(0);
            }
        }
        if (s.t != t.t)
        {
            ll nh = nhalls[s.r];
            ll compar = (t.t - s.t + nh) % nh;
            // fprintf(stderr, "nh: %lld, com: %lld\n", nh, compar);
            if ( (compar<<1) <= nh )
            {
                while( s.t != t.t )
                {
                    s.s();
                    go[0].pb('s');
                }
            } else {
                while( s.t != t.t )
                {
                    s.a();
                    go[0].pb('a');
                }
            }
        }
        for(auto d : go[0])
        {
            io << d;
        }
        if(go[1].size())
        {
            for(auto it = go[1].end();it != go[1].begin();it--)
            {
                io << rev[*(it-1)];
            }
        }
        io << io.endl;
        return 0;
    }
};

int main(void)
{
    return (new ac_machine())->wa();
}
