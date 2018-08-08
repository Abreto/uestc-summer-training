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

namespace two_sat
{

const int MAXN = 200020;
int sol0[MAXN], sol1[MAXN];

struct LogVar {
    int index;
    bool pre;
    LogVar(int _index = 0, bool _pre = false):index(_index), pre(_pre) {}
};

struct BinExp {
    LogVar p, q;
    BinExp(LogVar _p = LogVar(), LogVar _q = LogVar()) : p(_p), q(_q) {}
};

}

#include <cassert>
#include <cstring>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#define MAXN 200020
#define MAXM 400040
#define eps 1e-5
using namespace std;
struct Edge
{
	int from, to, next;
}edge[MAXM];//原图
int head[MAXN], edgenum;
vector<int> G[MAXN];//缩点后新图
int in[MAXN];//新图SCC的入度
int low[MAXN], dfn[MAXN];//通过子女节点所能到达的最低深度优先数  深度优先数
int dfs_clock;//时间戳
int sccno[MAXN], scc_cnt;//sccno[i]表示i属于哪个SCC  scc_cnt是SCC计数器
stack<int> S;//存储当前SCC的点
bool Instack[MAXN];//判断点是否在栈里面
int color[MAXN];//染色
int fp[MAXN];//建立对应SCC编号的映射
int solid[MAXN];
void init()
{
	edgenum = 0;
	memset(head, -1, sizeof(head));
    memset(solid, 0, sizeof(solid));
}
void addEdge(int u, int v)
{
	Edge E = {u, v, head[u]};
	edge[edgenum] = E;
	head[u] = edgenum++;
}
void tarjan(int u, int fa)//求SCC
{
	int v;
	low[u] = dfn[u] = ++dfs_clock;
	S.push(u);
	Instack[u] = true;
	for(int i = head[u]; i != -1; i = edge[i].next)
	{
		v = edge[i].to;
		if(!dfn[v])
		{
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
		}
		else if(Instack[v])
		low[u] = min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u])
	{
		scc_cnt++;
		for(;;)
		{
			v = S.top(); S.pop();
			Instack[v] = false;
			sccno[v] = scc_cnt;
			if(v == u) break;
		}
	}
}
void find_cut(int l, int r)
{
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn));
	memset(sccno, 0, sizeof(sccno));
	memset(Instack, false, sizeof(Instack));
	dfs_clock = scc_cnt = 0;
	for(int i = l; i <= r; i++)
	if(!dfn[i]) tarjan(i, -1);
}
void suodian()//缩点 + 反向建图
{
	for(int i = 1; i <= scc_cnt; i++) G[i].clear(), in[i] = 0;
	for(int i = 0; i < edgenum; i++)
	{
		int u = sccno[edge[i].from];
		int v = sccno[edge[i].to];
		if(u != v)
        {
            G[v].push_back(u), in[u]++; //反向建图
        }
	}
}


int N;

namespace disjoint
{

int f[MAXN];

void init(void)
{
    for(int i = 0;i < (N*2);i++)
    {
        f[i] = i;
    }
}

int find(int i)
{
    return (i == f[i]) ? i : (f[i] = find(f[i]));
}

void uni(int i, int j)
{
    int fi = find(i), fj = find(j);
    f[fi] = fj;
}

bool same(int i, int j)
{
    return find(i) == find(j);
}

}

// int tin[MAXN];
void toposort(void)//拓扑排序 + 染色
{
	queue<int> Q;
    disjoint::init();
	memset(color, 0, sizeof(color));
	for(int i = 1; i <= scc_cnt; i++)
    {
        // tin[i] = in[i];
        if(in[i] == 0) Q.push(i);
    }
	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		if(color[u] == 0)//没有颜色
		{
			color[u] = 1;//染色
			color[fp[u]] = 2;
		} else {
            if( disjoint::same(u, fp[u]) )
                solid[u] = solid[fp[u]] = 1;
        }
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
            if(--in[v] == 0)//入度减一
            {
                disjoint::uni(v, u);
                Q.push(v);
            }
		}
	}
}


void solve()
{
	memset(fp, 0, sizeof(fp));
	for(int i = 0; i < N; i++)
	{
		if(sccno[2*i] == sccno[2*i + 1])
		{
            assert(0);
		}
		else
		{
			fp[sccno[2*i]] = sccno[2*i + 1];
			fp[sccno[2*i + 1]] = sccno[2*i];
		}
	}
	suodian();//缩点
	toposort();//拓扑排序 + 染色
	/*printf("一组可行解:\n");
	for(int i = 1; i < N; i++)
	{
		if(color[sccno[2*i]] == 1)//可行解
		printf("");
	}
	printf("\n");*/
    int ans[2] = {0};
    for(int i = 0;i < N;i++)
    {
        if( solid[sccno[i<<1]] )
        {
            if(1 == color[sccno[i<<1]]) ans[0]++;
            else if(1 == color[sccno[i<<1|1]]) ans[1]++;
        }
    }
    io << ans[0] << ' ' << ans[1] << io.endl;
}

class ac_machine
{
    void getMap()//建图
    {
        int i;
        int x; char s[16];
        io >> N;
        for(i = 0;i < N;i++)
        {
            io >> x >> s;
            addEdge(i<<1, (x<<1) + ('w' == s[0]));
            addEdge((x<<1) + ('v' == s[0]), i<<1|1);
        }
    }
    void proc(void)
    {
        init();//初始化
        getMap();//建图
        // find_cut(1, 2*N-1);//找SCC change to 0 if get WA
        find_cut(0, 2*N-1);
        solve();//判断是否存在可行解 或者 输出一组可行解
    }
public:
    int wa(void)
    {
        int T;
        io >> T;
        while(T--) proc();
        return 0;
    }
};

int main(void)
{
    return (new ac_machine())->wa();
}
