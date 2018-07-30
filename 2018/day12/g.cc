#include <cstdio>
#include <cmath>

using namespace std;
#define MAXN    (100010)

typedef __float128 dbl;

#define eps (1e-7)

dbl fabs(dbl x)
{
    if(x < 0) return -x;
    return x;
}

int mysgn(dbl x)
{
    return (fabs(x) <= eps);
}

int n;
dbl px[MAXN], py[MAXN];
dbl py0, pyn;
dbl k[MAXN];
dbl lambda[MAXN];
dbl lsum;

int main(void)
{
    int i;
    scanf("%d", &n);
    for(i = 0;i <= n;i++)
    {
        int xi, yi;
        scanf("%d%d", &xi, &yi);
        px[i] = xi;
        py[i] = yi;
    }
    for(i = 0;i < n;i++)
    {
        k[i] = (py[i+1] - py[i]) / (px[i+1] - px[i]);
        if(i)
        {
            lambda[i] = (k[i] - k[i-1]) * 0.5;
            lsum += lambda[i];
            py0 += lambda[i] * fabs(px[i] - px[0]);
            pyn += lambda[i] * fabs(px[i] - px[n]);
        }
    }

    puts( ((1 == mysgn(k[0]+lsum)) && (1 == mysgn(k[n-1]-lsum)) && (1 == mysgn(py0-py[0])) && (1 == mysgn(pyn-py[n])))
        ? "Yes" : "No" );
    return 0;
}
