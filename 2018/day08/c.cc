#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long int ll;
const ll mod = 1000000007ll;
template <int N>
struct mat
{
    ll a[N][N];
    mat(void)
    {
        clear();
    }
    mat(ll x[][N])
    {
        for(int i = 0;i < N;i++)
            for(int j = 0;j < N;j++)
                a[i][j] = x[i][j];
    }
    void clear(void)
    {
        for(int i = 0;i < N;i++)
            for(int j = 0;j < N;j++)
                a[i][j] = 0ll;
    }
    void as1(void)
    {
        for(int i = 0;i < N;i++) a[i][i] = 1ll;
    }
    mat operator*(const mat &b) const
    {
        mat ret;
        for(int i = 0;i < N;i++)
            for(int j = 0;j < N;j++)
                for(int k = 0;k < N;k++)
                    ret.a[i][j] = (ret.a[i][j] + ((a[i][k] * b.a[k][j]) % mod)) % mod;
        return ret;
    }
};

ll ans[3];
ll base[][3] = {
    {0, 0, 0},
    {1, 0, 0},
    {0, 0, 1}
};
mat<3> bm;

void proc(void)
{
    int i, j;
    ll A, B, C, D, P, n;
    scanf("%lld%lld%lld%lld%lld%lld", &A, &B, &C, &D, &P, &n);
    if(n <= 2)
    {
        ans[1] = A; ans[2] = B;
        printf("%lld\n", ans[n]);
        return;
    }
    mat<3> res; res.a[0][0] = B; res.a[1][0] = A; res.a[2][0] = 1ll;
    base[0][0] = D; base[0][1] = C;
    for(i = 3;i <= n;i = j)
    {
        j = (P/i) ? (P / (P / i) + 1) : (n+1);
        if(j > n+1) j = n+1;
        int p = j - i;
        base[0][2] = P / i;
        bm = mat<3>(base);
        while(p)
        {
            if(1 & p) res = bm * res;
            bm = bm * bm;
            p >>= 1;
        }
    }
    printf("%lld\n", res.a[0][0]);
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while(T--) proc();
    return 0;
}
