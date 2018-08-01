#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

class abio
{
    static const unsigned BUF_SZ = 65535;
    FILE *istream, *ostream;
    char ibuf[BUF_SZ], obuf[BUF_SZ];
    bool reached_eof;
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
        if(EOF==ch) return (this->reach_eof());
        for(;(((ch>='0')&&(ch<='9')));ch=getchar()){x*=10;x+=(ch-'0');}
        if(EOF==ch)this->reach_eof();
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
        if(EOF==ch) return (this->reach_eof());
        for(;(((ch>='0')&&(ch<='9')));ch=getchar()){x*=(10ll);x+=(ch-'0');}
        if(EOF==ch)this->reach_eof();
        if(flag)x*=(-1);
        return (*this);
    }
    abio &read_s(char *str, char interrupt = ' ')
    {
        int ch = getchar();
        if(EOF == ch) return (this->reach_eof());
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
}io;

typedef struct ac_machine
{
    typedef long long int ll;
    static const int MAXN = 100010;
    static const int MOD = 1000000007;
    ll fact[MAXN], fiv[MAXN], inv[MAXN];
    void pre(void)
    {
        ll i;
        fact[0] = fact[1] = 1;
        fiv[0] = fiv[1] = 1;
        inv[1] = 1;
        for(i = 2ll;i < MAXN;i++)
        {
            fact[i] = (i * fact[i-1]) % MOD;
            inv[i] = (MOD - MOD/i) * inv[MOD%i] % MOD;
            fiv[i] = (inv[i] * fiv[i-1]) % MOD;
        }
    }
    ll C(int n, int k)
    {
        ll ret = fact[n];
        ret = (ret * fiv[n-k]) % MOD;
        return (ret * fiv[k]) % MOD;
    }

    struct Q
    {
        static size_t block;
        int id;
        int n, m;
        bool operator<(const Q &o) const
        {
            int nb = m / block, no = o.m / block;
            if(nb == no) return (n < o.n);
            else return nb < no;
        }
    }q[MAXN];
    int T;
    int ans[MAXN];
    ll n, m, current_ans;
    void bruteforce(void)
    {
        int i;
        n = q[0].n; m = -1ll;
        current_ans = 0ll;
        for(i = 0;i < T;i++)
        {
            const Q &qi = q[i];
            /* 先扩大区间，再减小区间 */
            while(n < qi.n)
            {
                current_ans = (2ll * current_ans) % MOD;
                current_ans = (current_ans - C(n,m) + MOD) % MOD;
                n++;
            }
            while(m > qi.m)
            {
                current_ans = (current_ans - C(n,m) + MOD) % MOD;
                m--;
            }
            while(n > qi.n)
            {
                n--;
                current_ans = (current_ans + C(n,m)) % MOD;
                current_ans = (current_ans * inv[2]) % MOD;
            }
            while(m < qi.m)
            {
                m++;
                current_ans = (current_ans + C(n,m)) % MOD;
            }
            ans[qi.id] = current_ans;
        }
    }
    int wa(void)
    {
        int i;
        int n, m;
        pre();
        io.read_int(T);
        Q::block = (int)sqrt(T);
        for(i = 0;i < T;i++)
        {
            q[i].id = i;
            io.read_int(q[i].n).read_int(q[i].m);
        }
        sort(q, q+T);
        bruteforce();
        for(i = 0;i < T;i++)
            io.write_ll(ans[i], '\n');
        return 0;
    }
}am;

size_t am::Q::block;
am app;

int main(void)
{
    return app.wa();
}
