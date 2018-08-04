#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <utility>

using namespace std;

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

class ac_machine
{
    typedef long long int ll;
    static const ll mod = 998244353;
    static const int maxn = 200020;
    static const int maxx = maxn;
    ll qow(ll a, ll p)
    {
        ll ret = 1ll;
        while(p)
        {
            if ( 1 & p ) ret = ( ret * a ) % mod;
            a = (a * a) % mod;
            p >>= 1;
        }
        return ret;
    }

    int n, m;
    int l[maxn], r[maxn];
    int ans[maxn];
    static int nx, xs[maxx];
    void discreate(void)
    {
        sort(xs, xs+nx);
        nx = unique(xs, xs+nx) - xs;
        // for(int i = 0;i < nx;i++) io<<xs[i]<<io.endl;
    }
    int xid(int x)
    {
        return lower_bound(xs, xs+nx, x) - xs + 1;  /** satisify segment tree */
    }

    /* (r, id) */
    typedef pair<int,int> pii;
    #define mp make_pair
    #define fi first
    #define se second
    int maxo;
    vector<pii> tree[maxx<<2];
    #define pb push_back
    void build(int o = 1, int l = 1, int r = nx)
    {
        maxo = max(maxo, o);
        tree[o].clear();
        if(l < r)
        {
            int mid = (l+r)>>1;
            build(o<<1, l, mid);
            build(o<<1|1, mid+1, r);
        }
    }
    void insert(int p, int ri, int id, int o = 1, int l = 1, int r = nx)
    {
        if (p < l || r < p) return;
        tree[o].pb(mp(ri,id));
        if (l < r)
        {
            int mid = (l+r)>>1;
            if(p <= mid) insert(p, ri, id, o<<1, l, mid);
            else insert(p, ri, id, o<<1|1, mid+1, r);
        }
    }
    void attack(int &sum, ll &prod, int aid, int L, int R, int x, int o = 1, int l = 1, int r = nx)
    {
        if(R < L) return;
        if(R < l || r < L) return;
        if(L <= l && r <= R)
        {
            while((!tree[o].empty()) && (tree[o].back().fi >= x))
            {
                auto back = tree[o].back();
                if(0 == ans[back.se])
                {
                    sum++;
                    prod = (prod * (ll)(back.se)) % mod;
                    ans[back.se] = aid;
                }
                tree[o].pop_back();
            }
        }
        else
        {
            int mid = (l+r)>>1;
            if(L <= mid) attack(sum, prod, aid, L, R, x, o<<1, l, mid);
            if(R > mid) attack(sum, prod, aid, L, R, x, o<<1|1, mid+1, r);
        }
    }

    void clear(void)
    {
        maxo = 0;
        nx = 0;
        memset(ans, 0, sizeof(ans));
    }

    void proc(void)
    {
        int i;
        io >> n >> m;
        clear();
        nx = 0;
        for(i = 1;i <= n;i++)
        {
            io>>l[i]>>r[i];
            xs[nx++] = l[i];
        }
        discreate();
        build();
        for(i = 1;i <= n;i++)
        {
            insert(xid(l[i]), r[i], i);
        }
        for(i = 1;i <= maxo;i++) sort(tree[i].begin(), tree[i].end());
        int res = 0;
        for(i = 1;i <= m;i++)
        {
            int xi;
            int s = 0; ll pro = 1ll;
            io>>xi;
            xi ^= res;
            int Xi = upper_bound(xs, xs+nx, xi) - xs;
            // io<<"attacking "<<xi<<' '<<Xi<<io.endl;
            attack(s, pro, i, 1, Xi, xi);
            io<<s<<io.endl;
            res = (s ? pro : 0);
        }
        for(i = 1;i < n;i++)
            io<<ans[i]<<' ';
        io<<ans[n]<<io.endl;
    }
public:
    int wa(void)
    {
        int T, casid = 1;
        io >> T;
        while(T--)
        {
            io << "Case #" << casid << ':' << io.endl; casid++;
            proc();
        }
        return 0;
    }
};

int ac_machine::nx, ac_machine::xs[maxx];

int main(void)
{
    return (new ac_machine())->wa();
}
