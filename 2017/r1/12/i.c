/* UESTC 2017 Summer Training #12 Div.2. Problem I, by Abreto<m@abreto.net>. */
#include <stdio.h>

typedef long long int ll;
#define inf (9223372036854775807ll)

#define GET(x,i)    (((x)>>(i))&1)

ll min(ll a, ll b){return (a<b)?a:b;}
ll dis2(ll dx, ll dy, ll dz)
{
    return dx*dx+dy*dy+dz*dz;
}

ll cord[3][3]; /* 0 for x, 1 for y, 2 for z */
ll mind = inf;

void update(ll dx, ll dy, ll dz)
{
    mind = min(mind, dis2(dx,dy,dz));
}

int in2plane(int i)
{
    return (cord[0][i] >= cord[1][i])&&(cord[0][i] <= cord[2][i]);
}

int in4plane(int i, int j)
{
    return in2plane(i)&&in2plane(j);
}

int incube(void)
{
    return in4plane(0,1)&&in2plane(2);
}

int test(int i, int j, int k)
{
    if(in2plane(i))
    {
        if(in2plane(j)&&(!in2plane(k)))
        {
            update(0,0,cord[0][k]-cord[1][k]);
            update(0,0,cord[0][k]-cord[2][k]);
        }
        else if (in2plane(k)&&(!in2plane(j)))
        {
            update(0,0,cord[0][j]-cord[1][j]);
            update(0,0,cord[0][j]-cord[2][j]);
        }
        else if ((!in2plane(j))&&(!in2plane(k)))
        {
            int t = 0;
            for(t = 0;t < (1<<2);++t)
                update(0, cord[0][j]-cord[1+GET(t,0)][j], cord[0][k]-cord[1+GET(t,1)][k]);
        }
    }
}

int main(void)
{
    int i = 0, j = 0, k = 0;

    for(i = 0;i < 3;++i)
        for(j = 0;j < 3;++j)
            scanf("%lld", &(cord[i][j]));
    if(incube()) puts("0");
    else
    {
        for(i=0;i<3;++i)for(j=0;j<3;++j)for(k=0;k<3;++k)
            if((i!=j)&&(j!=k)&&(k!=i))
                test(i,j,k);
        if((!in2plane(0))&&(!in2plane(1))&(!in2plane(2)))
        {
            int s = 0;
            for(s = 0;s < (1<<3);++s)
            {
                ll t = 0, d = 0;
                for(i = 0;i < 3;++i)
                {
                    d = cord[0][i] - cord[1+GET(s,i)][i];
                    t += d*d;
                }
                if(t < mind) mind = t;
            }
        }
        printf("%lld\n", mind);
    }
    return 0;
}
