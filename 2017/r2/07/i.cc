/* UESTC 2017 Summer Training #23 Div.2. Problem I, by Abreto<m@abreto.net> */
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define INPUTFILE   "I.in"

#define EPS (1e-9)
#define INF (1e9)
bool fe(double a, double b){return ((a-b>=-EPS)&&(a-b<=EPS));}
bool fl(double a, double b){return (a-b<-EPS);}
bool fle(double a, double b){return (a-b<=EPS);}
double myabs(double x){return fe(x,0.0)?0.0:((x<EPS)?(-x):x);}

typedef double T;
struct point
{
    T x, y;
    point():x(0),y(0){}
    point(T xx, T yy):x(xx),y(yy){}
    T mag2(void){return (x*x+y*y);}
    T mag(void){return sqrt(mag2());}
    T X(point b){return (x*b.y-y*b.x);}
    T& operator[](int i){if(0==i)return x;else return y;}
    friend point operator+(point a, point b){return point(a.x+b.x, a.y+b.y);}
    friend point operator-(point a, point b){return point(a.x-b.x, a.y-b.y);}
    friend T operator*(point a, point b){return (a.x*b.x+a.y*b.y);}
    friend bool operator==(point a, point b){return fe(a.x,b.x)&&fe(a.y,b.y);}
};

int n;
point P[128];

double dis(point A, point P, point Q) /* A->PQ */
{
    double in1 = (Q-P)*(A-P), in2 = (P-Q)*(A-Q);
    if(fl(in1,0.0) || fl(in2,0.0)) return min((A-P).mag2(), (A-Q).mag2());
    else
    {
        double out = (P-A).X(Q-A);
        return out*out / (P-Q).mag2();
    }
}

int pinp(point A)
{
    int i = 0;
    point vp[128];
    for(i = 0;i < n;++i)
        vp[i] = P[i] - A;
    vp[n] = vp[0];
    for(i = 0;i < n;++i)
        if( fl(vp[i].X(vp[i+1]),0.0) )
            return 0;
    return 1;
}

double f(double x, double y)
{
    int i = 0;
    double ret = INF;
    double flag = -1.0;
    if(pinp(point(x,y))) flag = 1.0;
    for(i = 0;i < n;++i)
        ret = min(ret, dis(point(x,y), P[i], P[i+1]));
    return ret*flag;
}

double trisea(double x, double yl, double yr)
{
    double l = yl, r = yr;
    while(r - l > EPS)
    {
        double mid = (l+r)/2.0;
        double mmid = (mid+r)/2.0;
        if(f(x,mid) > f(x,mmid))
            r = mmid;
        else
            l = mid;
    }
    return f(x,l);
}

double sea(double xl, double xr, double yl, double yr)
{
    double l = xl, r = xr;
    while(r-l > EPS)
    {
        double mid = (l+r)/2.0;
        double mmid = (mid+r)/2.0;
        if(trisea(mid,yl,yr) > trisea(mmid,yl,yr))
            r = mmid;
        else
            l = mid;
    }
    return trisea(l,yl,yr);
}

double solve(void)
{
    int i = 0;
    int xi = 0, yi = 0;
    int minx = 10000, maxx = 0, miny = 10000, maxy = 0;
    for(i = 0;i < n;++i)
    {
        scanf("%d %d", &xi, &yi);
        P[i] = point(xi,yi);
        minx = min(minx, xi); maxx = max(maxx, xi);
        miny = min(miny, yi); maxy = max(maxy, yi);
    }
    P[n] = P[0];
    return sqrt(sea(minx, maxx, miny, maxy));
}

int main(void)
{
#ifndef ABDEBUG
    freopen(INPUTFILE, "r", stdin);
#endif
    while(EOF != scanf("%d", &n) && n)
        printf("%.8lf\n", solve());
    return 0;
}
