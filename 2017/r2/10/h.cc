#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<string>
#include<stack>
#define inf 0x3f3f3f3f
#define esp 1e-10
using namespace std;
long long read(){
    long long x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

template <int STMAX = 1000000>
struct segment_tree
{
    struct node_t
    {
        static inline node_t merge(node_t n1, node_t n2)
        {
            node_t ans;
            ans.l = n1.l; ans.r = n2.r;
            ans.minp = min(n1.minp,n2.minp);
            return ans;
        }

        /* Data field */
        int l,r;
		int minp;
    }nodes[(STMAX+1)<<2];

    inline void maintain_leaf(int o, int idx)
    {
        nodes[o].l = nodes[o].r = idx;
        nodes[o].minp = -1;
    }
    inline void maintain(int o)
    {
        nodes[o] = node_t::merge(nodes[o<<1], nodes[o<<1|1]);
    }

    /* Usage: build(1,1,n); */
    void build(int o, int l, int r) /* [l,r] */
    {
        if( r <= l )
        {
            maintain_leaf(o, l);
        } else {
            int mid = l+r>>1;
            build(o<<1, l, mid);
            build(o<<1|1, mid+1, r);
            maintain(o);
        }
    }

    void upd(int pos, int app, int o, int l, int r)
    {
        if( l == r )
        {
			nodes[o].minp = app;
        } else if (l <= r) {
            int mid = (l+r)>>1;
            if( pos <= mid ) upd(pos, app, o<<1, l, mid);
            else if( pos > mid ) upd(pos, app, o<<1|1, mid+1, r);
            maintain(o);
        }
    }

    int qry(int L, int o, int l, int r)
    {
        if(l == r)
            return l;
        else
        {
            int mid = (l+r)>>1;
			if( nodes[o<<1].minp < L )
				return qry(L, o<<1, l, mid);
			else
				return qry(L, o<<1|1, mid+1, r);
        }
    }

    int N;

    segment_tree(void):N(STMAX){}
    segment_tree(int n):N(n){}
    void build(int n){N = n+1; build(1,1,N);}
    void update(int p, int a) {upd(p+1,a,1,1,N);}
    int query(int L) {return qry(L,1,1,N)-1;}
};
typedef segment_tree<100050> st;

int sg[100050];
int a[100050],c[100050];
st app;

void get(int pos)
{
	int nl = pos - c[pos];
	sg[pos] = app.query(nl);
	app.update(sg[pos],pos);
}

int main(){
	int n=read();
	app.build(100001);
	sg[0]=0; app.update(0,0);
	for(int i=1;i<n;i++){
		c[i]=read(); a[i]=read()&1;
	}
	int ans=0;
	for (int i=1;i<n;i++){
		get(i);
		ans= ans ^ (sg[i]*a[i]);
	}
	if (ans)	cout<<"First"<<endl;
	else		cout<<"Second"<<endl;
	return 0;
}

