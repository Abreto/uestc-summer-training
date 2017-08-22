/* UESTC 2017 Summer Training #33 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
const double eps=1e-10;
ll dcmp(ll x)
{  
    return (0==x)?0:(x<0?-1:1);
}  
struct Point
{  
    ll x,y;  
    Point(){}  
    Point(ll x,ll y):x(x),y(y){}  
    bool operator<(const Point &B)const  
    {  
        return (x-B.x)<0 || ((x-B.x)==0 && (y-B.y)<0);  
    }  
    bool operator==(const Point &B)const  
    {  
        return dcmp(x-B.x)==0 && dcmp(y-B.y)==0;  
    }  
};  
typedef Point Vector;
Vector operator-(Point A,Point B)  
{  
    return Vector(A.x-B.x,A.y-B.y);  
}  
ll Cross(Vector A,Vector B)  
{  
    return A.x*B.y-A.y*B.x;  
}  
int ConvexHull(Point *p,int n,Point *ch)  
{  
    sort(p,p+n);  
    n=unique(p,p+n)-p;
    int m=0;  
    for(int i=0;i<n;i++)  
    {  
        while(m>1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])<=0) m--;  
        ch[m++]=p[i];  
    }  
    int k=m;  
    for(int i=n-2;i>=0;i--)  
    {  
        while(m>k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])<=0 ) m--;  
        ch[m++]=p[i];  
    }  
    if(n>1) m--;  
    return m;  
}  
  
const int maxn=400004;
Point p[maxn],ch[maxn];  
ll dist2(Point a,Point b)//返回距离的平方  
{  
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);  
}  
int proc(void)
{  
    int n;  
    scanf("%d",&n);
    for(int i=0;i<n;++i)  
    {
        ll x, y, w;
        scanf("%lld%lld%lld", &x, &y, &w);
        p[4*i] = Point(x,y);
        p[4*i+1] = Point(x,y+w);
        p[4*i+2] = Point(x+w,y);
        p[4*i+3] = Point(x+w,y+w);
    }
    n <<= 2;
    int m=ConvexHull(p,n,ch);
    if(m==2)
    {  
        printf("%lld", dist2(ch[0],ch[1]));
    }
    else  
    {  
        ll ans=0xffffffffffffffff;
        for(int i=0;i<m;i++)
            for(int j=i+1;j<m;j++)
                ans=max(ans,dist2(ch[i],ch[j]));
        printf("%lld\n", ans);
    }
    return 0;  
}

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--) proc();
    return 0;
}
