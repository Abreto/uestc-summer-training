/* UESTC 2017 Summer Training #8 Div.2. Problem A, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <math.h>

#define MAXN    100001
#define MAXV    1000001

int n, W;
double dw;

double fh(double pi, int vi)
{
    return pi * log(1+((double)vi)/(dw));
}

int main(void)
{
    int i = 0;
    char deter[8];
    int safe = 0;
    double cur = 1.0;
    double pi = 0.0; int vi = 0;
    double eh = 0.0, teh = 0.0;
    double D = 0.0;
    double maxeh = 0.0;
    scanf("%d %d", &n, &W); dw = (double)W;
    for(i = 0;i < n;++i)
    {
        scanf("%s %lf %d", deter, &pi, &vi);
        eh += fh(cur*(1-pi), safe); /* failed. */
        teh = eh + fh(cur*pi, vi); /* win and stop. */
        if(teh > maxeh) maxeh = teh;
        cur *= pi; /* win and go on. */
        if('s' == deter[0]) safe = vi;
    }
    D = dw * (exp(maxeh) - 1.0);
    printf("$%.2lf\n", D);
    return 0;
}
