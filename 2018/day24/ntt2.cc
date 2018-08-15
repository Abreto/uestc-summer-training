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

const int N = 300010;
const int Mod = 998244353;
int n,m,L,R[N],g[N],a[N],b[N];

int gi()
{
  int x=0,res=1;char ch=getchar();
  while(ch>'9'||ch<'0'){if(ch=='-')res*=-1;ch=getchar();}
  while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
  return x*res;
}

inline int QPow(int d,int z)
{
  int ans=1;
  for(;z;z>>=1,d=1ll*d*d%Mod)
    if(z&1)ans=1ll*ans*d%Mod;
  return ans;
}

inline void NTT(int *A,int f)
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

int main()
{
  n=gi();m=gi();
  for(int i=0;i<=n;++i)a[i]=gi();
  for(int i=0;i<=m;++i)b[i]=gi();
  m+=n;for(n=1;n<=m;n<<=1)++L;
  for(int i=0;i<n;++i)R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
  NTT(a,1);NTT(b,1);
  for(int i=0;i<n;++i)a[i]=1ll*a[i]*b[i]%Mod;
  NTT(a,-1);
  for(int i=0;i<=m;++i)printf("%d ",a[i]);
  printf("\n");
  return 0;
}
