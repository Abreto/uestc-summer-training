#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

class abio
{
    static const unsigned BUF_SZ = 10240;
    FILE *istream, *ostream;
    char ibuf[BUF_SZ], obuf[BUF_SZ];
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
        clear_ibuf();
        clear_obuf();
    }
    inline size_t read_buffer(void)
    {
        isz = fread(ibuf, sizeof(char), BUF_SZ, istream);
        // for(ip=0;ip<isz;ip++) printf("%c(%x)|",ibuf[ip],ibuf[ip]);
        // puts("");
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
    inline int getchar(void)
    {
        if(0 == isz || isz == ip) read_buffer();
        if(0 == isz || isz == ip) return EOF;
        // printf("%lu:%c|\n", ip, ibuf[ip]);
        return ibuf[ip++];
    }
    inline int putchar(int ch)
    {
        if(osz == BUF_SZ) write_buffer();
        if(osz == BUF_SZ) return EOF;
        return (obuf[osz++] = ch);
    }
    inline int read_int(int &x)
    {
        int flag = 0, ch;
        x = 0;
        while((EOF!=(ch=getchar()))&&(('-'!=ch)&&((ch<'0')||(ch>'9'))));
        if(EOF==ch) return EOF;
        if('-'==ch){flag=1;ch=getchar();}
        if(EOF==ch) return EOF;
        for(;(((ch>='0')&&(ch<='9')));ch=getchar()){x*=10;x+=(ch-'0');}
        if(flag)x*=(-1);
        // printf("read-|%d|-\n", x);
        return 1;
    }
    inline long long int read_ll(long long int &x)
    {
        int flag = 0, ch;
        x = 0ll;
        while((EOF!=(ch=getchar()))&&(('-'!=ch)&&((ch<'0')||(ch>'9'))));
        if(EOF==ch) return EOF;
        if('-'==ch){flag=1;ch=getchar();}
        if(EOF==ch) return EOF;
        for(;(((ch>='0')&&(ch<='9')));ch=getchar()){x*=(10ll);x+=(ch-'0');}
        if(flag)x*=(-1ll);
        // printf("llread-|%lld|-\n", x);
        return 1;
    }
    inline void write_ll(long long int x, char append = 0)
    {
        int d[20],nd=0;
        if(0==x) putchar('0');
        if(x<0){putchar('-');x=-x;}
        while(x){d[nd++]=x%10;x/=10;}
        while(nd--)putchar('0'+d[nd]);
        if(append)putchar(append);
    }
};

abio io;
typedef long long int ll;
int n, m, k, T;
long long int p, q, r, mod, a;
const int maxn = 1001010;

struct node{
    int posi, val;
}arr[maxn*10];
deque<node> que, que2;
int main(){
    io.read_int(T); // scanf("%d", &T);
    while(T--){
        long long int ansA = 0, ansB = 0;
        io.read_int(n); io.read_int(m); io.read_int(k);
        io.read_ll(p); io.read_ll(q); io.read_ll(r);
        io.read_ll(mod);
        // scanf("%d%d%d%lld%lld%lld%lld", &n, &m, &k, &p, &q, &r, &mod);
        for(int i = 1; i <= k; i ++){
            io.read_int(arr[i].val); // scanf("%lld", &arr[i].val);
            arr[i].posi = i;
        }
        for(int i = k+1; i <= n; i ++){
            arr[i].val = (arr[i-1].val * p + q * i + r) % mod;
            arr[i].posi = i;
        }
    
        for(int i = 1; i <= m; i ++){
            while(!que.empty() && que.back().val <= arr[i].val) que.pop_back();
            que.push_back(arr[i]);
        }
        
        ansA = que.front().val ^ 1;
        //printf("1 : %lld\n", que.front().val);
        for(int i = 2; i <= n-m+1; i ++){
            while(!que.empty() && que.front().posi < i) que.pop_front();
            while(!que.empty() && que.back().val <= arr[i+m-1].val) que.pop_back();
            que.push_back(arr[i+m-1]);
            ansA = (ansA + (que.front().val ^ i));
            //printf("%d : %lld\n", i , que.front().val);
        }
        //return 0;
        
        for(int i = n; i > n-m+1; i --){
            while(!que2.empty() && que2.back().val <= arr[i].val) que2.pop_back();
            que2.push_back(arr[i]);
        }
        
        for(int i = n-m+1; i > 0; i --){
            while(!que2.empty() && que2.front().posi >= i+m) que2.pop_front();
            while(!que2.empty() && que2.back().val <= arr[i].val) que2.pop_back();
            que2.push_back(arr[i]);
            ansB = (ansB + (que2.size() ^ i));
        }
        while(!que.empty()) que.pop_back();
        while(!que2.empty()) que2.pop_back();
        io.write_ll(ansA, ' ');
        io.write_ll(ansB, '\n');
        // printf("%lld %lld\n", ansA, ansB);
    }
    return 0;
}

