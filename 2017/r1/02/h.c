/* UESTC 2017 Summer Training #2 Div.2. Problem H, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <math.h>

#define PI  acos(-1.0)
#define EPS (1e-12)

double alpha = 2.0*PI/3.0;

double f(double b)
{
    double over = sin(alpha) + sin(b) - sin(alpha+b);
    double bot = sin(alpha/2.0) + sin(b/2.0) + sin((alpha+b)/2.0);
    return over / bot;
}

void calc(int r, int R)
{
    if( R < 2*r )
        printf("NO Solution!\n");
    else
    {
        double ratio = 2.0*(double)r / (double)R;
        double beta = 0.0, gamma = 0.0;
        double l = 0.0, r = 2.0*PI/3.0;
        while( r-l > EPS)
        {
            double mid = (l+r) / 2.0;
            double fm = f(mid);
            if( fm > ratio )
                r = mid;
            else
                l = mid;
        }
        beta = l; gamma = 2*PI - alpha - beta;

        printf("%.18lf %.18lf %.18lf\n", 2.0*R*sin(alpha/2), 2.0*R*sin(beta/2), 2.0*R*sin(gamma/2));
    }
}

int main(void)
{
    int r = 0, R = 0;

    while(EOF != scanf("%d%d", &r, &R))
        calc(r, R);

    return 0;
}
