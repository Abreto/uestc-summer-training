/* UESTC 2017 Summer Training #4 Div.2. Problem A, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long int ll;
struct record
{
    int a,b,c;
    record(int aa,int bb,int cc):a(aa),b(bb),c(cc){}
};
struct point
{
    int id;
    ll x, y;
    point():id(0),x(0),y(0){}
    point(int ii, ll xx, ll yy):id(ii),x(xx),y(yy){}
    point(ll xx, ll yy):id(0),x(xx),y(yy){}
    friend point operator-(point a, point b){return point(a.x-b.x, a.y-b.y);}
    friend ll operator*(point a, point b){return (a.x*b.x+a.y*b.y);}
    ll mag2(void){return (x*x+y*y);}
    ll det(point b){return (x*b.y-y*b.x);}
    bool operator<(point b);
};

typedef vector<point> vp;

int N;
vp src;
vp conv;
vector<record> ans;
point O;

bool point::operator<(point b)
{
    point oa = *this-O, ob = b-O;
    ll t = oa.det(ob);
    if(0 == t) return (0 == oa.mag2());
    return (t > 0);
}

void handle(void)
{
    int top = 0;
    O = src[0];
    for(auto p : src)
        if((p.x < O.x )|| (p.x == O.x && p.y < O.y))
            O = p;
    sort(src.begin(), src.end());
    conv.push_back(src[0]);conv.push_back(src[1]); top=1;
    for(int i = 2;i < N;++i)
    {
        ans.push_back(record(O.id, src[i].id, src[i-1].id));
        while( (conv[top]-conv[top-1]).det(src[i]-conv[top]) < 0 )
        {
            ans.push_back(record(src[i].id, conv[top].id, conv[top-1].id));
            conv.pop_back(); --top;
        }
        conv.push_back(src[i]); ++top;
    }
}

int main(void)
{
    ll xi = 0, yi = 0;
    scanf("%d", &N);
    for(int i = 0;i < N;++i)
    {
        scanf("%lld%lld", &xi, &yi);
        src.push_back(point(i+1, xi, yi));
    }
    handle();
    printf("%lu\n", ans.size());
    for(auto one : ans)
        printf("%d %d %d\n", one.a, one.b, one.c);
    return 0;
}
