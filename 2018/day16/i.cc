#include <cstdio>
#include <vector>
#include <algorithm>

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
    abio &read_int(int &x)
    {
        int flag = 0, ch = getchar();
        if(EOF == ch) return (this->reach_eof());
        x = 0;
        while((EOF!=ch)&&(('-'!=ch)&&((ch<'0')||(ch>'9'))))ch=getchar();
        if(EOF==ch) return (this->reach_eof());
        if('-'==ch){flag=1;ch=getchar();}
        //if(EOF==ch) return (this->reach_eof());
        for(;(((ch>='0')&&(ch<='9')));ch=getchar()){x*=10;x+=(ch-'0');}
        //if(EOF==ch)this->reach_eof();
        if(flag)x*=(-1);
        return (*this);
    }
    abio &read_ll(long long int &x)
    {
        int flag = 0, ch = getchar();
        if(EOF == ch) return (this->reach_eof());
        x = 0ll;
        while((EOF!=ch)&&(('-'!=ch)&&((ch<'0')||(ch>'9'))))ch=getchar();
        if(EOF==ch) return (this->reach_eof());
        if('-'==ch){flag=1;ch=getchar();}
        //if(EOF==ch) return (this->reach_eof());
        for(;(((ch>='0')&&(ch<='9')));ch=getchar()){x*=(10ll);x+=(ch-'0');}
        //if(EOF==ch)this->reach_eof();
        if(flag)x*=(-1);
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

class acmachine
{
    typedef long long int ll;
    static const ll mod = 998244353;
    static const int maxn = 100101;
    ll n;
    static struct P
    {
        int x, y;
        bool operator<(const P &q) const
        {
            return (x == q.x) ? (y < q.y) : (x > q.x);
        }
    }p[maxn];
    static int ny, ys[maxn];
    ll discreate(void)
    {
        int i, j;
        sort(ys, ys+ny);
        for(i = 0;i < ny;i++) printf("%d\n", ys[i]);
        ll cnt = 0;
        ll ret = 0ll;
        for(i = 0;i < ny;i=j)
        {
            for(j = i+1;(j < ny) && (ys[j] == ys[i]);j++);
            /* now i~(j-1) have eq y */
            cnt = j - i;
            ll delta = (cnt * (ll)(i)) % mod;
            printf("%d,%d,%lld\n", i, j, delta);
            ret = (ret + delta) % mod;
        }
        ny = unique(ys, ys+ny) - ys;
        return ret;
    }
    int id(int y)
    {
        return lower_bound(ys, ys+ny, y) - ys + 1;  /* to satisify segment tree */
    }
    static int sum[maxn<<2];
    void build(int o = 1, int l = 1, int r = ny)
    {
        sum[o] = 0;
        if(l < r)
        {
            int mid = (l+r)>>1;
            build(o<<1, l, mid);
            build(o<<1|1, mid+1, r);
        }
    }
    void upd(int p, int o = 1, int l = 1, int r = ny)
    {
        if(p < l || r < p) return;
        if(l == p && p == r)
        {
            sum[o]++;
        } else {
            int mid = (l+r)>>1;
            if(p <= mid) upd(p, o<<1, l, mid);
            if(p > mid) upd(p, o<<1|1, mid+1, r);
            sum[o] = sum[o<<1] + sum[o<<1|1];
        }
    }
    int qry(int L, int R, int o = 1, int l = 1, int r = ny)
    {
        if(R < L) return 0;
        if(R < l || r < L) return 0;
        if(L <= l && r <= R)
        {
            return sum[o];
        } else {
            int mid = (l+r)>>1;
            return qry(L, R, o<<1, l, mid) + qry(L, R, o<<1|1, mid+1, r);
        }
    }
public:
    int wa()
    {
        int i;
        scanf("%lld", &n);
        // io>>n;
        ny = 0;
        for(i = 0;i < n;i++)
        {
            scanf("%d%d", &(p[i].x), &(p[i].y));
            // io>>p[i].x>>p[i].y;
            ys[ny++] = p[i].y;
        }
        ll ans = discreate();
        ans = (n + ans) % mod;
        sort(p, p+n);
        build();
        int lastx = p[0].x;
        vector<int> xs;
        for(i = 0;i < n;i++)
        {
            if(p[i].x != lastx)
            {
                lastx = p[i].x;
                for(auto x : xs)
                    upd(x);
                xs.clear();
            }
            int sep = id(p[i].y);
            ll up = qry(sep+1, ny);
            ll down = qry(1, sep-1);
            ll delta = (up * down) % mod;
            ans = (ans + delta) % mod;
            xs.push_back(sep);
        }
        printf("%lld\n", ans);
        // io<<ans<<io.endl;
        return 0;
    }
}app;

int acmachine::ny, acmachine::ys[maxn];
acmachine::P acmachine::p[maxn];
int acmachine::sum[maxn<<2];

int main(void)
{
    return (app.wa());
}
