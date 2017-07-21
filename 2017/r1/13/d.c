/* UESTC 2017 Summer Training #13 Div.2. Problem D, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <math.h>

#define pi  (acos(-1.0))

int main(void)
{
    int T = 0, ncase = 0;
    scanf("%d", &T);
    while(T--)
    {
        double R = 0.0, dn = 0.0;
        double s = 0.0;
        int n = 0;
        scanf("%lf %d", &R, &n); dn = n;
        s = sin(pi/dn);
        printf("Case %d: %.10lf\n", ++ncase, R*s/(1.0+s));
    }
    return 0;
}
