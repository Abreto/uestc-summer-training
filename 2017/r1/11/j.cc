/* UESTC 2017 Summer Training #11 Div.2. Problem J, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

#define GET(x,i)    (((x)>>(i))&1)
#define SET(x,i)    ((x)|(1<<(i)))
#define ERA(x,i)    ((x)^(1<<(i)))
int lg(int x)
{
    int ret = 0;
    for(x;x;x>>=1) ret+=x&1;
    return ret;
}

#define PI  (acos(-1.0))
#define EPS (1e-9)
#define INF (2e9)
bool fe(double a, double b){return ((a-b>=-EPS)&&(a-b<=EPS));}
bool fl(double a, double b){return (a-b<-EPS);}
bool fle(double a, double b){return (a-b<=EPS);}

typedef double T;
struct point
{
    T x, y;
    point():x(0),y(0){}
    point(T xx, T yy):x(xx),y(yy){}
    T mag2(void){return (x*x+y*y);}
    T X(point b){return (x*b.y-y*b.x);}
    T& operator[](int i){if(0==i)return x;else return y;}
    friend point operator+(point a, point b){return point(a.x+b.x, a.y+b.y);}
    friend point operator-(point a, point b){return point(a.x-b.x, a.y-b.y);}
    friend T operator*(point a, point b){return (a.x*b.x+a.y*b.y);}
    friend bool operator==(point a, point b){return fe(a.x,b.x)&&fe(a.y,b.y);}
};

struct light
{
    point v;
    double a;
    light(){}
    light(point vv, double aa):v(vv),a(aa){;}
    double on(double x) const
    {
        double tanb = (x-v.x)/v.y;
        double beta = atan(tanb);
        double theta = a+beta;
        if(theta-EPS > PI/2.0) return INF;
        double k = tan(theta)-tanb;
        return k*v.y;
    }
};

#define MAXN    32

int n;
double dest;
light lgts[MAXN];
int del[MAXN];
double dp_m[1<<20];

double dp(int s)
{
    if(dp_m[s]>EPS) return dp_m[s];
    else
    {
        int i = 0;
        int sle = lg(s);
        if(1 == sle)
        {
            for(i = 0;i < n;++i)
                if(1 == GET(s,i))
                {
                    dp_m[s] = lgts[i].on(0.0);
                    break;
                }
        } else {
            double ml = 0.0;
            for(i = 0;i < n;++i)
                if(1 == GET(s,i))
                {
                    double t = dp(ERA(s,i))+lgts[i].on(dp(ERA(s,i)));
                    if(t > ml-EPS) ml = t;
                }
            dp_m[s] = ml;
        }
        return dp_m[s];
    }
}

int main(void)
{
    int i = 0, j = 0;
    int l = 0, r = 0;
    int xi = 0, yi = 0, ai = 0; double dai = 0.0;
    scanf("%d%d%d", &n, &l, &r);
    dest = r-l;
    for(i = 0;i < n;++i)
    {
        scanf("%d%d%d", &xi, &yi, &ai);
        dai = ai;
        lgts[i] = light(point(1.0*xi-1.0*l,1.0*yi),dai*PI/180.0);
    }
    printf("%.12lf\n", min(dp((1<<n)-1),dest));
    return 0;
}
