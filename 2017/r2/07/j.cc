/* UESTC 2017 Summer Training #23 Div.2. Problem J, by Abreto<m@abreto.net> */
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

#define INPUTFILE   "J.in"
#define eps (1e-9)
template < typename T = double >
struct dbl
{
    T x;
    dbl(void):x(0.0){}
    template <typename U>
    dbl(U a):x((T)a){}
    inline char sgn(void){return ((x>=-eps)&&(x<=eps))?(0):((x>eps)?(1):(-1));}
    inline T tabs(void){return ((x>=-eps)&&(x<=eps))?(0.0):((x>eps)?(x):(-x));}
    inline dbl abs(void){return dbl(tabs());}
    template <typename U>
    inline dbl &operator=(const U b) {x=(T)b;return (*this);}
    inline dbl operator+(const dbl &b) const {return dbl(x+b.x);}
    inline dbl operator-(const dbl &b) const {return dbl(x-b.x);}
    inline dbl operator*(const dbl &b) const {return dbl(x*b.x);}
    inline dbl operator/(const dbl &b) const {return dbl(x/b.x);}
    inline dbl operator+=(const dbl &b) {return dbl(x+=b.x);}
    inline dbl operator-=(const dbl &b) {return dbl(x-=b.x);}
    inline dbl operator*=(const dbl &b) {return dbl(x*=b.x);}
    inline dbl operator/=(const dbl &b) {return dbl(x/=b.x);}
    inline bool operator==(const dbl &b) const {return (0 == ((*this)-b).sgn());}
    inline bool operator<(const dbl &b) const {return (-1 == ((*this)-b).sgn());}
    inline bool operator<=(const dbl &b) const {return (((*this)==b) || ((*this)<b));}
    inline bool operator>(const dbl &b) const {return (b < (*this));}
    inline bool operator>=(const dbl &b) const {return (((*this)==b) || ((*this)>b));}
    template <typename U>
    inline operator U() const {return (U)x;}
};

#define MAXD    64
typedef dbl< long double > Double;
typedef long long int ll;

Double C[MAXD][MAXD];
void init(void)
{
    int i = 0, j = 0;
    //Double::set_eps();
    C[0][0] = 1.0;
    for(i = 1;i < MAXD;++i)
    {
        C[i][0] = C[i][i] = 1.0;
        for(j = 1;j < i;j++)
            C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
}

Double quickpow(int a, int b)
{
    int ret = 1, base = a;
    while(b)
    {
        if(b&1) ret *= base;
        base *= base;
        b >>= 1;
    }
    return Double(ret);
}

int a, m, b, n;
Double da, db, dm, dn;

/* here A = [A,b]. */
int N;
int row, col;
Double A[MAXD][MAXD];
Double x[MAXD];
int l[MAXD];
#define HASH(i,j)   ((i)*n+(j)+1) /* a^(i/m)*b^(j/n) */

void gauss(void)
{
    int i = 0, j = 0, k = 0;
    int ret = 0, r = 0;
    for(i = 0;i < N;++i)
    {
        l[i] = 0;
        x[i] = 0.0;
    }
    for(i = 0;i < N;++i)
    {
        for(j = r;j < N;++j)
            if(0 != A[j][i].sgn())
            {
                for(k = i;k <= N;++k)
                    swap(A[j][k], A[r][k]);
                break;
            }
        if(0 == A[r][i].sgn())
        {
            ++ret;
            continue;
        }
        for(j = 0;j < N;++j)
            if(j != r && 0 != A[j][i].sgn())
            {
                Double tmp = A[j][i] / A[r][i];
                for(k = i;k <= N;++k)
                    A[j][k] -= tmp * A[r][k];
            }
        l[i] = 1; ++r;
    }
    for(i = 0;i < N;++i)
        if(l[i])
            for(j = 0;j < N;++j)
                if(0 != A[j][i].sgn())
                    x[i] = A[j][N] / A[j][i];
}

void proccess(void)
{
    int i = 0, j = 0;
    int d = 0;
    da = a; db = b;
    dm = m; dn = n;
    N = m*n+1;
    row = N;
    col = N+1;
    memset(A, 0, sizeof(A));
    for(d = 0;d < row;++d)
        for(i = 0;i <= d;++i)
        {
            int di = d - i;
            Double tmp = C[d][i] * pow((long double)da, di/m) * pow((long double)db, i/n);
            A[HASH(di%m,i%n)][d] += tmp;
        }
    A[0][N-1] = A[0][N] = 1.0;
    gauss();
    for(i = N-1;i >= 0;--i)
    {
        printf("%d ", (int)round(x[i].x));
    }
}

int main(void)
{
    freopen(INPUTFILE, "r", stdin);
    init();
    while(EOF != scanf("%d%d%d%d", &a, &m, &b, &n) && a && m && b && n)
    {
        proccess();
        printf("\n");
    }
    return 0;
}
