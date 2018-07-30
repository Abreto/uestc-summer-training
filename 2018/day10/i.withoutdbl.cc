#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define eps (1e-9)
#define inf (1e9)
template < typename T = double >
struct dbl
{
    T x;
    dbl(void):x(0.0){}
    template <typename U>
    dbl(U a):x((T)a){}
    inline char sgn(void){return ((x>=-eps)&&(x<=eps))?(0):((x>eps)?(1):(-1));}
    inline T tabs(void){return ((x>=-eps)&&(x<=eps))?(0.0):((x>eps)?(x):(-x));}
    inline dbl abs(void){return dbl(tabs());}
    template <typename U> inline dbl &operator=(const U b) {x=(T)b;return (*this);}
    inline T *operator&(void) {return &x;}
    inline dbl operator-(void) const {return dbl(-x);}
    inline dbl operator+(const dbl &b) const {return dbl(x+b.x);}
    inline dbl operator-(const dbl &b) const {return dbl(x-b.x);}
    inline dbl operator*(const dbl &b) const {return dbl(x*b.x);}
    inline dbl operator/(const dbl &b) const {return dbl(x/b.x);}
    template <typename U> inline dbl operator^(U b) const {T ret=1.0,base=x;while(b){if(b&1)ret*=base;base*=base;b>>=1;}return dbl(ret);}
    inline dbl operator+=(const dbl &b) {return dbl(x+=b.x);}
    inline dbl operator-=(const dbl &b) {return dbl(x-=b.x);}
    inline dbl operator*=(const dbl &b) {return dbl(x*=b.x);}
    inline dbl operator/=(const dbl &b) {return dbl(x/=b.x);}
    template <typename U> inline dbl operator^=(const U &b) {dbl tmp=(*this)^b;*this=tmp;return tmp;}
    inline bool operator==(const dbl &b) const {return (0 == ((*this)-b).sgn());}
    inline bool operator!=(const dbl &b) const {return (0 != ((*this)-b).sgn());}
    inline bool operator<(const dbl &b) const {return (-1 == ((*this)-b).sgn());}
    inline bool operator<=(const dbl &b) const {return (((*this)==b) || ((*this)<b));}
    inline bool operator>(const dbl &b) const {return (b < (*this));}
    inline bool operator>=(const dbl &b) const {return (((*this)==b) || ((*this)>b));}
    template <typename U> inline operator U() const {return (U)x;}
    inline char operator[](unsigned n) {if(n >= 0){long long int ret=x;while(n--){ret/=10;}return (ret%10);}else{T ret=x;n=-n;while(n--)ret*=10.0;return ((long long int)ret)%10;}}
};

typedef double Double;
typedef Double T;

int sgn(Double x)
{
    if(fabs(x) < eps) return 0;
    if(x > 0) return 1;
    return -1;
}
Double qow(Double a, int p)
{
    Double ret = 1.;
    while(p)
    {
        if(1 & p) ret *= a;
        a *= a;
        p >>= 1;
    }
    return ret;
}

struct point
{
    T x,y;
    point(void):x(T()),y(T()){}
    point(T xx, T yy):x(xx),y(yy){}
    inline point operator-(void) const {return point(-x,-y);}
    inline point operator+(const point& b) const {return point(x+b.x,y+b.y);}
    inline point operator-(const point& b) const {return point(x-b.x,y-b.y);}
    inline point operator*(const T& scale) const {return point(x*scale,y*scale);}
    inline point operator/(const T& scale) const {return point(x/scale,y/scale);}
    inline T operator*(const point& b) const {return ((x)*(b.x))+((y)*(b.y));} /* inner product */
    inline T operator^(const point& b) const {return ((x)*(b.y))-((b.x)*(y));} /* outter product */
    inline point& operator+=(const point& b) {point tmp=(*this)+b;(*this)=tmp;return (*this);}
    inline point& operator-=(const point& b) {point tmp=(*this)-b;(*this)=tmp;return (*this);}
    inline bool operator==(const point& b) const {return (x==b.x)&&(y==b.y);}
    inline bool operator!=(const point& b) const {return !((*this)==b);}
};
#define vec point

struct line
{
    point a, b;
    line(void) {}
    line(point x, point y):a(x),b(y) {}
};

/* include end points */
bool PointOnSegment(point p, line l)
{
    return (0 == sgn((p-l.a)^(l.b-l.a))) && (sgn((p-l.a)*(p-l.b)) <= 0);
}

bool parallel(line a, line b)
{
    return (0 == sgn((a.a-a.b)^(b.a-b.b)));
}

bool line_make_point(line a, line b, point &res)
{
    if (parallel(a,b)) return false;
    T s1( (a.a-b.a) ^ (b.b-b.a) );
    T s2( (a.b-b.a) ^ (b.b-b.a) );
    res = (a.b*s1 - a.a*s2) / (s1-s2);
    return true;
}

const T pi = acos(-1.0);

int N;
point TRIANGLE[3];
T S;

T Gamma(T rho, T theta, T &len)
{
    line seg;
    if(0 == sgn(theta)) seg = line(point(rho,0), point(rho,1));
    else if (0 == sgn(theta - (pi/2.))) seg = line(point(0,rho), point(1,rho));
    else seg = line(point(rho / cos(theta), 0.), point(0., rho / sin(theta)));
    for(int i = 0;i < 3;i++)
    {
        point P = TRIANGLE[i];
        if(PointOnSegment(P, seg)) continue;
        point Q = TRIANGLE[(i+1)%3], R = TRIANGLE[(i+2)%3];
        line PQ(P, Q), PR(P, R);
        point xQ, xR;
        bool xPQ = line_make_point(PQ, seg, xQ);
        bool xPR = line_make_point(PR, seg, xR);
        if(xPQ && xPR && PointOnSegment(xQ, PQ) && PointOnSegment(xR, PR))
        {
            T part = fabs((xQ - P) ^ (xR - P)) / 2.;
            len = sqrt( (xQ - xR) * (xQ - xR) );
            return part / S;
        }
    }
    return 1.;
}

T gamma(T rho, T theta, T &len)
{
    T G = Gamma(rho, theta, len);
    return (qow(G, (N-2)) + qow((T(1.)-G), (N-2)));
}

namespace innerint
{
    T F(T rho, T theta)
    {
        T l = 0.;
        T g = gamma(rho, theta, l);
        return (g * qow(l,3));
    }
    T simpson(T theta, T a, T b)//三点Simpson法，这里要求F是一个全局函数
    {
        T c = a + (b - a) / 2.;
        return (F(a, theta) + T(4) * F(c, theta) + F(b, theta))*(b - a) / T(6);
    }
    T asr(T theta, T a, T b, T _eps, T A)//自适应Simpson公式（递归过程）。已知整个区间[a,b]上的三点Simpson值A
    {
        T c = a + (b - a) / T(2);
        T L = simpson(theta, a, c), R = simpson(theta, c, b);
        if (fabs(L + R - A) <= T(15.) * _eps) return L + R + ((L + R - A) / T(15.0));
        return asr(theta, a, c, _eps / T(2), L) + asr(theta, c, b, _eps / T(2), R);
    }
    T asr(T theta, T a, T b, T _eps)//自适应Simpson公式（主过程）
    {
        return asr(theta, a, b, _eps, simpson(theta, a, b));
    }
}

namespace outterint
{
    /* int from p_min to p_max dp */
    T F(T theta, T _eps = 1e-4)
    {
        T p_min = inf, p_max = -inf;
        point unit(cos(theta), sin(theta));
        for(int i = 0;i < 3;i++)
        {
            p_min = min(p_min, unit*TRIANGLE[i]);
            p_max = max(p_max, unit*TRIANGLE[i]);
        }
        return innerint::asr(theta, p_min, p_max, _eps);
    }
    T simpson(T a, T b)//三点Simpson法，这里要求F是一个全局函数
    {
        T c = a + (b - a) / T(2);
        return (F(a) + T(4) * F(c) + F(b))*(b - a) / T(6);
    }
    T asr(T a, T b, T _eps, T A)//自适应Simpson公式（递归过程）。已知整个区间[a,b]上的三点Simpson值A
    {
        T c = a + (b - a) / T(2);
        T L = simpson(a, c), R = simpson(c, b);
        if (fabs(L + R - A) <= T(15.) * _eps) return L + R + ((L + R - A) / T(15.0));
        return asr(a, c, _eps / T(2), L) + asr(c, b, _eps / T(2), R);
    }
    T asr(T a, T b, T _eps)//自适应Simpson公式（主过程）
    {
        return asr(a, b, _eps, simpson(a, b));
    }
}

int main(void)
{
    int i = 0;
    for(i = 0;i < 3;i++)
    {
        int xi, yi;
        scanf("%d%d", &xi, &yi);
        TRIANGLE[i] = point((double_t)xi, (double_t)yi);
    }
    S = fabs((TRIANGLE[1]-TRIANGLE[0]) ^ (TRIANGLE[2]-TRIANGLE[0])) / T(2.);
    scanf("%d", &N);
    if(3 == N) puts("3.00000000");
    else
    {
        T dN = N;
        T CN2 = dN * 0.5 * (dN - 1.);
        T ans = outterint::asr(T(0.), pi, 1e-5);
        ans *= CN2;
        ans /= 3.;
        ans /= S;
        ans /= S;
        printf("%.8lf\n", ans);
    }
    return 0;
}
