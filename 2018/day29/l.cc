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

#include <queue>
#include <cstdlib>

using namespace std;
const int inf = 0x3fffffff;
#define MAXM    (2001000)
#define MAXN    (1 << 10)

namespace mcmf
{

    //Use stack instead of queue when get TLE
    int L,N;
    int K;
    struct edges {
      int to,next,cap,flow,cost;
    } edge[MAXM];
    struct nodes {
      int dis,pre,head;
      bool visit;
    } node[MAXN];
    void init(int n) {
      N=n;
      L=0;
      for (int i=0; i<N; i++)
        node[i].head=-1;
    }
    void add_edge(int x,int y,int cap,int cost) {
      // fprintf(stderr, "add edge %d->%d with %d(%d)\n", x, y, cap, cost);
      edge[L].to=y;
      edge[L].cap=cap;
      edge[L].cost=cost;
      edge[L].flow=0;
      edge[L].next=node[x].head;
      node[x].head=L++;
      edge[L].to=x;
      edge[L].cap=0;
      edge[L].cost=-cost;
      edge[L].flow=0;
      edge[L].next=node[y].head;
      node[y].head=L++;
    }
    bool spfa(int s,int t) {
      queue <int> q;
      for (int i=0; i<N; i++) {
        node[i].dis=0x3fffffff;
        node[i].pre=-1;
        node[i].visit=0;
      }
      node[s].dis=0;
      node[s].visit=1;
      q.push(s);
      while (!q.empty()) {
        int u=q.front();
        node[u].visit=0;
        for (int i=node[u].head; i!=-1; i=edge[i].next) {
          int v=edge[i].to;
          if (edge[i].cap>edge[i].flow &&
              node[v].dis>node[u].dis+edge[i].cost) {
            node[v].dis=node[u].dis+edge[i].cost;
            node[v].pre=i;
            if (!node[v].visit) {
              node[v].visit=1;
              q.push(v);
            }
          }
        }
        q.pop();
      }
      if (node[t].pre==-1)
        return 0;
      else
        return 1;
    }
    int mcmf(int s,int t,int &cost) {
      int flow=0;
      while (spfa(s,t)) {
        int max=inf;
        for (int i=node[t].pre; i!=-1; i=node[edge[i^1].to].pre) {
          if (max>edge[i].cap-edge[i].flow)
            max=edge[i].cap-edge[i].flow;
        }
        for (int i=node[t].pre; i!=-1; i=node[edge[i^1].to].pre) {
          edge[i].flow+=max;
          edge[i^1].flow-=max;
          cost+=edge[i].cost*max;
        }
        flow+=max;
      }
      return flow;
    }

    void main(void)
    {
        int n, m, K, W;
        static int st[MAXN], tt[MAXN], w[MAXN], op[MAXN];
        io >> n >> m >> K >> W;
        init(2 * m + 10);
        int s = 0, sp = 1, t = N - 1;
        add_edge(s, sp, K, 0);
        for (int i = 1; i <= m; i++)
        {
            io >> st[i] >> tt[i] >> w[i] >> op[i];
            add_edge(sp, i << 1, 1, 0);
            add_edge(i << 1, i << 1 | 1, 1, -w[i]);
            add_edge(i << 1 | 1, t, 1, 0);
        }
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= m; j++)
                if (tt[i] <= st[j])
                    add_edge(i << 1 | 1, j << 1, 1, ((op[i] == op[j])) * W);
        int cost = 0;
        mcmf(s, t, cost); // fprintf(stderr, "%d|\n", f);
        io << (-cost) << io.endl;
    }

}

class ac_machine
{
public:
    int wa(void)
    {
        int T;
        io >> T;
        while (T--) mcmf::main();
        return 0;
    }
};

int main(void)
{
    return (new ac_machine())->wa();
}
