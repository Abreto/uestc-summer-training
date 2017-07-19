/* UESTC 2017 Summer Training #10 Div.2. Problem A, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <math.h>

#define TLE puts("TLE")
#define AC  puts("AC")

int limit[8] = {0,12,29,177,1000,31622,39620077,1000000000};

int f(int n, int t)
{
    int ret = 0;
    int base = 2;
    double tmp = 0.0;
    switch(t)
    {
    case 1:
        ret = 1;
        while(n) ret *= n--;
        break;
    case 2:
        ret = 1;
        while(n)
        {
            if(n&1) ret *= base;
            base *= base;
            n >>= 1;
        }
        break;
    case 3:
        ret = n*n*n*n;
        break;
    case 4:
        ret = n*n*n;
        break;
    case 5:
        ret = n*n;
        break;
    case 6:
        tmp = log2(n);
        ret = ceil(tmp*(double)n);
        break;
    case 7:
        ret = n;
        break;
    }
    return ret;
}

int main(void)
{
    int m = 0, n = 0, t = 0;
    scanf("%d%d%d", &m, &n, &t);
    if(n > limit[t]) TLE;
    else if(f(n,t) > m) TLE;
    else AC;
    return 0;
}
