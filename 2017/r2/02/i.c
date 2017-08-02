/* UESTC 2017 Summer Training Round2 #02 Div.2. Problem I, by . */
#include <stdio.h>

typedef unsigned int uint;

#define MAXN    (10000000)
#define inf     ((1u<<31)-1u)
#define BASE    10099u

uint n, q, x0, x1, a, b, c;

uint aa[MAXN];

uint next()
{
    uint t = x0 * a + x1 * b + c;
    x0 = x1;
    x1 = t;
    return x0 >> 2;
}

uint* findmin(uint* l, uint* r)
{
    uint* x = l, *ret = l;
    while(++x < r)
        if(*x < *ret)
            ret = x;
    return ret;
}

int main(void)
{
    int i = 0;
    uint* pm = aa;
    uint sum = 0, base = BASE;
    scanf("%u%u%u%u%u%u%u", &n, &q, &x0, &x1, &a, &b, &c);
    for(i = 0;i < n;++i) aa[i] = inf;
    while(q--)
    {
        uint idx = next()%n, x = next();
        aa[idx] = x;
        if(x < *pm) {
            pm = aa+idx;
        } else if(aa+idx == pm) {
                pm = findmin(aa,aa+n);
        }
        sum += (*pm)*base;
        base *= BASE;
    }
    printf("%u\n", sum);
    return 0;
}
