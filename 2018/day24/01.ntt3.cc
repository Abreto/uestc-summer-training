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

//NTT
#include <cassert>
#include    <iostream>
#include    <cstdio>
#include    <cstdlib>
#include    <algorithm>
#include    <vector>
#include    <cstring>
#include    <queue>
#include    <complex>
#include    <stack>
#define LL long long int
#define ls (x << 1)
#define rs (x << 1 | 1)
#define MID int mid=(l+r)>>1
using namespace std;

const int N = 524288;
const int Mod = 998244353;
int n,m,L,R[N],g[N],a[N],b[N];

inline int QPow(int d,int z)
{
  int ans=1;
  for(;z;z>>=1,d=1ll*d*d%Mod)
    if(z&1)ans=1ll*ans*d%Mod;
  return ans;
}

inline void NTT(long long int *A,int f)
{
  for(int i=0;i<n;++i)if(i<R[i])swap(A[i],A[R[i]]);
  for(int i=1;i<n;i<<=1){
    int gn=QPow(3,(Mod-1)/(i<<1)),x,y;
    for(int j=0;j<n;j+=(i<<1)){
      int g=1;
      for(int k=0;k<i;++k,g=1ll*g*gn%Mod){
    x=A[j+k];y=1ll*g*A[i+j+k]%Mod;
    A[j+k]=(x+y)%Mod;A[i+j+k]=(x-y+Mod)%Mod;
      }
    }
  }
  if(f==1)return;reverse(A+1,A+n);
  int y=QPow(n,Mod-2);
  for(int i=0;i<n;++i)A[i]=1ll*A[i]*y%Mod;
}

class ac_machine
{
    typedef long long int ll;
    static const int maxn = 524288;
    static const int maxl = 18;
    int len, w;
    int tn, tm, tk;
    ll f[maxn];
    ll ans[maxn];
    void tle(void)
    {
        io >> tn >> tm >> tk;
        for (n = 1, L = 0;n <= tk;n <<= 1) ++L;
        for (w = 0;(1 << (w+1)) <= tm;w++);
        assert(w < maxl); assert(len < maxn);
        for (int i = 0;i < n;i++)
        {
            f[i] = (i < tn);
            ans[i] = 1;
        }
        for(int i=0;i<n;++i)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
        NTT(f, 1);
        int target = tm;
        for (int i = 0 ; target ; i++)
        {
            for (int j = 0;j < n;j++)
                f[j] = (f[j] * f[j]) % Mod;
            if (target & 1)
            {
                for (int j = 0;j < n;j++)
                    ans[j] = (ans[j] * f[j]) % Mod;
            }
            target >>= 1;
        }
        NTT(ans, -1);
        // for (int i = 0;i < len;i++) fprintf(stderr, "%lld ", ans[i]); fputs("\n", stderr);
        io << ans[tk] << io.endl;
    }
public:
    int wa(void)
    {
        int T;
        io >> T;
        while (T--) tle();
        return 0;
    }
};

int main(void)
{
    return (new ac_machine())->wa();
}
