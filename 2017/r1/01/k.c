/* UESTC 2017 Summer Training #1 Div.2. Problem K, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN    1024

typedef long long int ll;

ll mag2(ll ox, ll oy)
{
    return (ox*ox + oy*oy);
}
ll det(ll x1, ll y1, ll x2, ll y2)
{
    return (x1*y2-x2*y1);
}
int sgn(ll x)
{
    return (x<0)?-1:(x>0?1:0);
}

int N, tN;
ll x[MAXN], y[MAXN];
int deleted[MAXN];

int nc;
int O[MAXN];
int convex[MAXN][MAXN];
int np[MAXN];
int isline[MAXN];

ll mag2o(int idx)
{
    ll ox = x[O[nc]], oy = y[O[nc]];
    return mag2(x[idx]-ox, y[idx]-oy);
}
ll deto(int a, int b)
{
    ll ox = x[O[nc]], oy = y[O[nc]];
    return det(x[a]-ox, y[a]-oy, x[b]-ox, y[b]-oy);
}
int compar_angle(const void *a, const void *b)
{
    int pa = *((int*)a), pb = *((int*)b);
    ll t = deto(pa, pb);
    if(0 == t) return sgn(mag2o(pb)-mag2o(pa)); 
    else return (-sgn(t));
}

int sorted[MAXN];
void graham(void)
{
    int i = 0, j = 0;
    for(i = 1;i <= N;++i)
        if( !deleted[i] )
            sorted[j++] = i;
    qsort(sorted, tN, sizeof(int), compar_angle);
    convex[nc][0] = O[nc]; convex[nc][1] = sorted[0];
    np[nc] = 1;
    for(i = 1;i < tN;++i)
        while(1)
        {
            //printf("Now top is (%lld,%lld)\n", x[convex[nc][np[nc]]], y[convex[nc][np[nc]]]);
            //printf("Considering (%lld,%lld)\n", x[sorted[i]], y[sorted[i]]);
            if(np[nc] < 1)
            {
                convex[nc][++np[nc]] = sorted[i];
                break;
            } else {
                ll t = det(x[convex[nc][np[nc]]]-x[convex[nc][np[nc]-1]], y[convex[nc][np[nc]]]-y[convex[nc][np[nc]-1]], x[sorted[i]]-x[convex[nc][np[nc]]], y[sorted[i]]-y[convex[nc][np[nc]]]);
                if( t >= 0 )
                {
                    convex[nc][++np[nc]] = sorted[i];
                    break;
                } else {
                    --np[nc];
                }
            }
        }
    for(i = 0;i < tN-1;++i)
        if( /*printf("i:%d\n", i) &&*/ deto(sorted[i], sorted[0]) )
            break;
    if(i == tN-1)
    {
        np[nc] = -1;
        for(i = tN - 1;i >= 0;i--)
            convex[nc][++np[nc]] = sorted[i];
        convex[nc][++np[nc]] = O[nc];
        isline[nc] = 1;
    } else if (i > 1) {
        for(j = np[nc];j > 0;j--)
            convex[nc][j+i-1] = convex[nc][j];
        np[nc] += i-1;
        for(j = 1;j < i;++j)
            convex[nc][j] = sorted[i-j];
    }
    /*printf("__________\n");
    for(i = 0;i <= np[nc];++i)
        printf("%lld,%lld\n", x[convex[nc][i]], y[convex[nc][i]]);
    printf("----------\n");*/
}

void readata(void)
{
    int i = 0;
    scanf("%d", &N); tN = N;
    for(i = 1;i <= N;++i)
        scanf("%lld%lld", x+i, y+i);
}

void proccess(void)
{
    int i = 0;
    nc = 0;
    while(tN)
    {
        for(i = 1;i <= N;++i)
            if( !deleted[i] )
            {
                O[nc] = i;
                break;
            }
        for(i = 1;i <= N;++i)
            if(!deleted[i])
            {
                if(x[i] < x[O[nc]])
                    O[nc] = i;
                else if (x[i] == x[O[nc]] && y[i] < y[O[nc]])
                    O[nc] = i;
            }
        graham();
        for(i = 0;i < np[nc];++i)
        {
            deleted[convex[nc][i]] = 1;
            tN--;
        }
        ++nc;
    }
}

void writeans(void)
{
    if(isline[0])
        puts("-1");
    else {
        int i = 0, j = 0;
        for(j = 0;j < np[0];++j)
            printf("%d %d\n", convex[0][j], convex[0][j+1]);
        for(i = 1;i < nc;++i)
        {
            printf("%d %d\n", O[i-1], convex[i][0]);
            for(j = 1;j < np[i];++j)
                printf("%d %d\n", convex[i][j-1], convex[i][j]);
        }
    }
}

int main(void)
{
    readata();
    proccess();
    writeans();
    return 0;
}
