#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

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
    static const int maxx = maxn * 6;
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

    static const int threshold = 447;
    struct train
    {
        int id;
        int lid, rid;
        train(void){}
        train(int ii, int l, int r):id(ii),lid(l),rid(r){}
        bool operator<(const train &o) const
        {
            return (rid < o.rid);
        }
    };
    int nl, ul[maxn];
    int lid(int l)
    {
        return lower_bound(ul, ul + nl, l) - ul;
    }
    int block_flag;
    int nblock;
    int max_lid[threshold+10];
    vector<train> trs[threshold+10];
    void init_block(void)
    {
        int i;
        nl = 0;
        for(i = 1;i <= n;i++)
        {
            ul[nl++] = l[i];
        }
        sort(ul, ul+nl); nl = unique(ul, ul+nl) - ul;
        memset(max_lid, 0, sizeof(max_lid));
        if(nl <= threshold)
        {
            block_flag = 0;
            nblock = nl;
            for(i = 0;i < nblock;i++) trs[i].clear();
            for(i = 1;i <= n;i++)
            {
                int Li = lid(l[i]), L = xid(l[i]);
                max_lid[Li] = max(max_lid[Li], L);
                trs[Li].push_back(train(i, L, xid(r[i])));
            }
        } else {
            int block_sz = (nl + threshold - 1) / threshold;
            block_flag = 1;
            nblock = (nl + block_sz - 1) / block_sz;
            for(i = 0;i < nblock;i++) trs[i].clear();
            for(i = 1;i <= n;i++)
            {
                int Li = lid(l[i]), L = xid(l[i]);
                int bid = Li / block_sz;
                // max_lid[Li] = max(max_lid[Li], L);
                max_lid[bid] = max(max_lid[bid], L);
                trs[bid].push_back(train(i, L, xid(r[i])));
                assert(bid < nblock);
            }
        }
        assert(nblock < threshold+10);
        for(i = 0;i < nblock;i++)
            sort(trs[i].begin(), trs[i].end());
    }

    int sum[maxx<<2]; ll prod[maxx<<2];
    // int add[maxn<<2]; ll mul[maxn<<2];
    void build(int o = 1, int l = 1, int r = nx)
    {
        sum[o] /* = add[o] */ = 0;
        prod[o] /* = mul[o] */ = 1ll;
        if(l < r)
        {
            int mid = (l+r)>>1;
            build(o<<1, l, mid);
            build(o<<1|1, mid+1, r);
        }
    }
    void mark(int delta, ll ratio, int o)
    {
        sum[o] += delta;
        prod[o] = (prod[o] * ratio) % mod;
    }
    void pushdown(int o)
    {
        if((sum[o] > 0) || (prod[o] > 1))
        {
            mark(sum[o], prod[o], o<<1);
            mark(sum[o], prod[o], o<<1|1);
            sum[o] = 0;
            prod[o] = 1ll;
        }
    }
    void upd(int L, int R, int delta, ll ratio, int o = 1, int l = 1, int r = nx)
    {
        if(R < L) return;
        if(R < l || r < L) return;
        if(L <= l && r <= R)
        {
            mark(delta, ratio, o);
        } else {
            int mid = (l+r)>>1;
            pushdown(o);
            if(L <= mid) upd(L, R, delta, ratio, o<<1, l, mid);
            if(R > mid) upd(L, R, delta, ratio, o<<1|1, mid+1, r);
        }
    }
    void qry(int &s, ll &pro, int p, int o = 1, int l = 1, int r = nx)
    {
        if(p < l || r < p) return;
        if(l == p && p == r)
        {
            s = sum[o];
            pro = prod[o];
        } else {
            int mid = (l+r)>>1;
            pushdown(o);
            if(p <= mid) qry(s, pro, p, o<<1, l, mid);
            else qry(s, pro, p, o<<1|1, mid+1, r);
        }
    }
    void disolve(int attack_id, int attack_pos)
    {
        int block_id;
        int resolved = 0;
        for(block_id = 0;(block_id < nblock) && (max_lid[block_id] <= attack_pos);++block_id)
        {
            while(!trs[block_id].empty())
            {
                auto back = trs[block_id].back();
                if(back.rid < attack_pos) break;
                ans[back.id] = attack_id;
                upd(back.lid, back.rid, -1, qow(back.id, mod-2));
                trs[block_id].pop_back();
                resolved++;
            }
        }
        if(block_id < nblock)
        {
            while(!trs[block_id].empty())
            {
                auto back = trs[block_id].back();
                if(back.rid < attack_pos) break;
                if(back.lid > attack_pos) continue;
                ans[back.id] = attack_id;
                upd(back.lid, back.rid, -1, qow(back.id, mod-2));
                trs[block_id].pop_back();
                resolved++;
            }
        }
        assert(resolved > 0);
    }
    void clear(void)
    {
        nx = 0;
        memset(ans, 0, sizeof(ans));
    }

    void proc(void)
    {
        int i;
        io >> n >> m;
        clear();
        for(i = 1;i <= n;i++)
        {
            io>>l[i]>>r[i];
            xs[nx++] = l[i]-1;
            xs[nx++] = l[i];
            xs[nx++] = l[i]+1;
            xs[nx++] = r[i]-1;
            xs[nx++] = r[i];
            xs[nx++] = r[i]+1;
        }
        discreate();
        build();
        for(i = 1;i <= n;i++)
        {
            int L = xid(l[i]), R = xid(r[i]);
            upd(L, R, 1, (ll)i);
        }
        init_block();
        int res = 0;
        for(i = 1;i <= m;i++)
        {
            int xi;
            int s = 0; ll pro = 1ll;
            io>>xi;
            xi ^= res;
            int Xi = xid(xi);
            // io<<"attacking "<<xi<<' '<<Xi<<io.endl;
            qry(s, pro, Xi);
            io<<s<<io.endl;
            if (s) disolve(i, Xi);
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
