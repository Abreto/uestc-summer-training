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

#include <set>
#include <bitset>
#include <map>
#include <string>

using namespace std;
// typedef bitset<(1<<18)> __bits_t;
typedef string __bits_t;

struct bits_t
{
    int n;
    __bits_t bits;
    bits_t(int nn = 0) : n(nn) { bits.resize(1<<nn, 0); }
    void setn(int nn) { n = nn; bits.resize(1<<nn, 0); }
    bool operator<(const bits_t &b) const
    {
        if( n != b.n ) return n < b.n;
        for(int i = 0;i < (1<<n);i++)
            if(bits[i] != b.bits[i])
                return bits[i] < b.bits[i];
        return false;
    }
    void display(void) const
    {
        for(int i = 0;i < (1<<n);i++) fprintf(stderr, "%d", bits[i]);
        fprintf(stderr, "\n");
    }
};

#define MAXVERT 10240
int nvertices;
map< bits_t, int > ids;
string tobits[MAXVERT];
int getId( bits_t &x )
{
    if( ids.find(x) == ids.end() )
    {
        ids[x] = ++nvertices;
        assert(nvertices < MAXVERT);
        tobits[nvertices] = x.bits;
    }
    return ids[x];
}
int tree[MAXVERT];
set< int > next_floor[2];

class ac_machine
{
    static const int maxs = (1<<18);
    static constexpr int op[3][2][2] = {
        {   /* & */
            {0 & 0, 0 & 1},
            {1 & 0, 1 & 1},
        },
        {   /* | */
            {0 | 0, 0 | 1},
            {1 | 0, 1 | 1},
        },
        {   /* ^ */
            {0 ^ 0, 0 ^ 1},
            {1 ^ 0, 1 ^ 1},
        }
    };
    int n, N;
    char s[maxs+10];
public:
    int wa(void)
    {
        int i, j, w;
        io >> n; N = (1 << n);
        io >> s;
        bits_t bits(n);
        for(i = 0;i < N;i++)
        {
            bits.bits[i] = s[i] - '0';
        }
        tree[getId(bits)] = 1; next_floor[(n & 1) ^ 1].insert(getId(bits));
        for(w = n;w > 0;w--)
        {
            next_floor[w & 1].clear();
            for (auto v : next_floor[(w & 1) ^ 1])
            {
                // v.display();
                int base = tree[v];
                bits_t newbits[3];
                for(j = 0;j < 3;j++) newbits[j].setn( w - 1 );
                for(i = 0;i < (1<<w);i += 2)
                {
                    for(j = 0;j < 3;j++)
                    {
                        newbits[j].bits[i >> 1] = op[j][ tobits[v][i] ][ tobits[v][i+1] ];
                    }
                }
                for(j = 0;j < 3;j++)
                {
                    int id = getId(newbits[j]);
                    tree[id] += base;
                    next_floor[w & 1].insert(id);
                }
            }
        }
        bits.setn(0); bits.bits[0] = 1;
        io << tree[getId(bits)] << io.endl;
        // if( tree.finds( bits ) == tree.end() ) tree[bits] = 0;
        return 0;
    }
};
constexpr int ac_machine::op[3][2][2];

int main(void)
{
    return (new ac_machine())->wa();
}
