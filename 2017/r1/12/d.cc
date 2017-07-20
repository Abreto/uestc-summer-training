/* UESTC 2017 Summer Training #12 Div.2. Problem D, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

#define eps (1e-8)
#define pi  acos(-1.0)
#define dst pi*2.0

int N;
double dis[128];
double ans;

double f(double a)
{
    int i = 0;
    double ret = 0.0;
    for(i = 0;i < N;++i)
    {
        double cosa = (dis[i]*dis[i]+dis[i+1]*dis[i+1]-a*a)/(2.0*dis[i]*dis[i+1]);
        ret += acos(cosa);
    }
    return ret;
}

double solve(double l0, double r0)
{
    double l = l0, r = r0;
    while(r-l>eps)
    {
        double mid = (l+r)/2.0;
        double t = f(mid);
        if(t > dst+eps) r = mid;
        else if (t < dst-eps) l = mid;
        else return mid;
    }
    return l;
}

int ok(void)
{
    int i = 0;
    double mina = 0.0, maxa = 1e9;
    for(i = 0;i < N;++i)
    {
        mina = max(mina, fabs(dis[i]-dis[i+1]));
        maxa = min(maxa, dis[i]+dis[i+1]);
    }
    if( (mina > maxa+eps) || (f(mina+eps)>dst+eps) || (f(maxa-eps)<dst-eps) )
        return 0;
    else
    {
        ans = solve(mina, maxa);
        return 1;
    }
}

void proccess(int caseid)
{
    int i = 0;
    scanf("%d", &N);
    for(i = 0;i < N;++i)
        scanf("%lf", dis+i);
    dis[N] = dis[0];
    printf("Case %d: ", caseid);
    if(ok()) printf("%.3lf\n", ans);
    else puts("impossible");
}

int main(void)
{
    int T = 0, ncase = 0;
    scanf("%d", &T);
    while(T--) proccess(++ncase);
    return 0;
}
