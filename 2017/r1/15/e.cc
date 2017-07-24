/* UESTC 2017 Summer Training #15 Div.2. Problem E, by Abreto<m@abreto.net>. */
#include <cstdio>

using namespace std;

typedef long long int ll;
ll myabs(ll x){return (x<0)?(-x):x;}
ll gcd(ll a, ll b) {return (0==b)?a:gcd(b,a%b);}

struct frac
{
    ll n,d;
    frac(){}
    frac(ll nn, ll dd):n(nn),d(dd){}
    frac operator-(void) const
    {
        return frac(-n,d);
    }
    frac operator+(const frac b) const
    {
        ll nn = n*b.d+b.n*d;
        ll nd = d*b.d;
        ll g = myabs(gcd(nn,nd));
        return frac(nn/g,nd/g);
    }
    frac operator*(const frac b) const
    {
        ll nn = n*b.n;
        ll nd = d*b.d;
        ll g = myabs(gcd(nn,nd));
        return frac(nn/g,nd/g);
    }
    void put(void)
    {
        if(1==d) printf("%lld", n);
        else printf("%lld/%lld", n, d);
    }
};

#define MAXN    512
frac ft[MAXN][MAXN];

void init(void)
{
    int i = 0, j = 0;
    frac I(1,1);
    ft[0][1] = I;
    for(i = 1;i < 401;++i)
    {
        frac sum(0,1);
        for(j = 2;j <= i+1;++j)
        {
            ft[i][j] = frac(i,j)*ft[i-1][j-1];
            sum = sum+ft[i][j];
        }
        ft[i][1] = I+(-sum);
    }
}

int main(void)
{
    int P = 0;
    int n = 0, m = 0, k = 0;
    init();
    scanf("%d", &P);
    while(P--)
    {
        scanf("%d %d %d", &n, &m, &k);
        printf("%d ", n);
        ft[m][k].put();
        puts("");
    }
    return 0;
}
