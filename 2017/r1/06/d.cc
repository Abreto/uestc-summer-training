/* UESTC 2017 Summer Training #6 Div.2. Problem D, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cfloat>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

#define EPS (1e-12)
bool fe(double a, double b){return ((a-b>=-EPS)&&(a-b<=EPS));}
bool fl(double a, double b){return (a-b<-EPS);}
bool fle(double a, double b){return (a-b<=EPS);}

typedef long long int ll;
struct point
{
    double x, y;
    point():x(0),y(0){}
    point(double xx, double yy):x(xx),y(yy){}
    friend point operator-(point a, point b){return point(a.x-b.x, a.y-b.y);}
    double mag2(void){return (x*x+y*y);}
    double det(point b){return (x*b.y-y*b.x);}
    friend bool operator==(point a, point b)
    {
        return fe(a.x,b.x)&&fe(a.y,b.y);
    }
    friend bool operator<(point a, point b)
    {
        if(!fe(a.y, b.y)) return fl(a.y, b.y);
        return fl(b.x, a.x);
    }
};
typedef vector<point> vp;

#define INPUTFILE   "dome.in"
#define OUTPUTFILE  "dome.out"

set<point> src;
vp convex;

double ansh, ansr;
double ansv=DBL_MAX;

void make_convex(void)
{
    int top = 0;
    for(auto cdd:src)
    {
        if(0 == top)
        {
            convex.push_back(cdd); ++top;
            continue;
        }
        if(fe(cdd.y, convex[top-1].y)) continue;
        while(top > 0 && fle(convex[top-1].x,cdd.x))
        {
            convex.pop_back(); --top;
        }
        while(top > 1 && fl((convex[top-1]-convex[top-2]).det(cdd-convex[top-1]),0.0))
        {
            convex.pop_back(); --top;
        }
        convex.push_back(cdd); ++top;
    }
}

void update(double nh, double nr)
{
    double nv = nr*nr*nh;
    if(fl(nv,ansv))
    {
        ansv = nv; ansh = nh; ansr = nr;
    }
}

void testseg(point a, point b)
{
    double k = (a.y-b.y)/(a.x-b.x);
    double nh = a.y - k * a.x;
    double nr = -nh/k;
    update(nh, nr);
}

void handle(void)
{
    make_convex();
    if(1 == convex.size())
    {
        double r0 = convex[0].x, h0 = convex[0].y;
        ansh = 3.0 * h0;
        ansr = 1.5 * r0;
    } else {
        int nconvex = convex.size();
        /* upmost */
        {
            point upmost = convex[nconvex-1], prev = convex[nconvex-2];
            if(upmost.x > EPS)
            {
                point lm = point(0.0, 3.0*upmost.y);
                point um = lm-upmost, pu = upmost-prev;
                double t = pu.det(um);
                if(fl(0,t))
                {
                    double newh = 3.0*upmost.y, newr = 1.5*upmost.x;
                    update(newh, newr);
                } else testseg(upmost, prev);
            }
        }
        /* bottom */
        {
            point bot = convex[0], next = convex[1];
            point lm = point(0.0, 3.0*bot.y);
            point bm = lm-bot, bn = next-bot;
            double t = bm.det(bn);
            if(fl(0,t))
            {
                double newh = 3.0*bot.y, newr = 1.5*bot.x;
                update(newh, newr);
            } else testseg(bot, next);
        }
        /* middle */
        for(int i = 1;i < convex.size()-1;++i)
        {
            point prev = convex[i-1], mid = convex[i], next = convex[i+1];
            point lm(0.0, 3.0*mid.y);
            point pm = mid-prev, ml = lm-mid, mn = next-mid;
            double t1 = pm.det(ml), t2 = ml.det(mn);
            if(fle(0,t1)&&fle(0,t2))
            {
                double newh = lm.y, newr = 1.5*mid.x;
                update(newh, newr);
            } else {
                testseg(prev, mid);
                testseg(mid, next);
            }
        }
    }
}

int main(void)
{
    int n = 0;
    double xi = 0.0, yi = 0.0, zi = 0.0;
    double ri = 0.0;
    freopen(INPUTFILE, "r", stdin);
    freopen(OUTPUTFILE, "w+", stdout);

    scanf("%d", &n);
    while(n--)
    {
        scanf("%lf%lf%lf", &xi, &yi, &zi);
        ri = sqrt(xi*xi+yi*yi);
        src.insert(point(ri, zi));
    }
    handle();
    printf("%.3lf %.3lf\n", ansh, ansr);
    return 0;
}
