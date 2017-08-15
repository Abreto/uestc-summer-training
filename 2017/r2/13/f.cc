#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20020;
const int MAXM = 100010;
struct Edge
{
int to,next;
}edge[MAXM];
int head[MAXN],tot;
void init()
{
tot = 0;
memset(head,-1,sizeof(head));
}
void addedge(int u,int v)
{
edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
bool vis[MAXN];//染色标记,为true表示选择
int S[MAXN],top;//栈
bool dfs(int u)
{
if(vis[u^1])return false;
if(vis[u])return true;
vis[u] = true;
S[top++] = u;
for(int i = head[u];i != -1;i = edge[i].next)
if(!dfs(edge[i].to))
return false;
return true;
}
bool Twosat(int n)
{
memset(vis,false,sizeof(vis));
for(int i = 0;i < n;i += 2)
{
if(vis[i] || vis[i^1])continue;
top = 0;
if(!dfs(i))
{
while(top)vis[S[--top]] = false;
if(!dfs(i^1)) return false;
}
}
return true;
}

int n, r, l;
int have[1024][1024];

void dont(int u, int v)
{
    u--; v--;
    addedge(u, v^1);
    addedge(v, u^1);
}

void imlazy(int lid, int ni, int nj, int d)
{
    if(ni >= 1 && ni <= n && nj >= 1 && nj <= n)
    {
        if( have[ni][nj] )
        {
            int llid = have[ni][nj];
            dont(lid*2+d, llid*2+d);
        }
    }
}

int main(void)
{
    int i = 0, j = 0;
    int ri = 0, ci = 0;
    init();
    scanf("%d %d %d", &n, &r, &l);
    for(i = 1;i <= l;++i)
    {
        scanf("%d %d", &ri, &ci);
        have[ri][ci] = i;
    }
    for(i = 1;i <= n;++i)
        for(j = 1;j <= n;++j)
            if(have[i][j])
            {
                int w = 0;
                for(w = 1;w <= 2*r;++w)
                {
                    imlazy(have[i][j], i-w,j, 0); //imlazy(have[i][j], i+w,j);
                    imlazy(have[i][j], i,j-w,-1); //imlazy(have[i][j], i,j+w);
                }
            }
    if( Twosat(2*l) )
        puts("YES");
    else
        puts("NO");
    return 0;
}