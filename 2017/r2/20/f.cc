/* MIPT-2016 Pre-Finals Workshop, Taiwan NTU Contest. Problem F, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;

#define MOD 20160519
#define TMOD    26880696
#define TTMOD   746688

template <ll mod>
struct mat
{
    ll a[2][2];
    mat(void)
    {
        a[0][0] = a[1][1] = 0;
        a[0][1] = a[1][0] = 0;
    }
    mat(int t)
    {
        if(1 == t)
        {
            a[0][0] = 0; a[0][1] = 1;
            a[1][0] = 1; a[1][1] = 1;
        } else {
            a[0][0] = a[1][1] = 1;
            a[1][0] = a[0][1] = 0;
        }
    }
    void print(void) const
    {
        printf("|%lld %lld|\n|%lld %lld|\n", a[0][0], a[0][1], a[1][0], a[1][1]);
    }
    mat operator*(const mat& mb) const
    {
        mat ans;
        for(int i = 0;i < 2;++i)
            for(int j = 0;j < 2;++j)
                for(int k = 0;k < 2;++k)
                {
                    ll temp = (a[i][k]*mb.a[k][j]) % mod;
                    ans.a[i][j] = (ans.a[i][j] + temp) % mod;
                }
        return ans;
    }
};

template <ll mod>
mat<mod> quickpow(mat<mod> base, int p)
{
    mat<mod> ret(2);
    while(p)
    {
        if(p&1) ret = ret * base;
        mat<mod> tmp = base*base;
        base = tmp;
        p >>= 1;
    }
    return ret;
}

template <ll mod>
ll fib(int n)
{
    if(n < 2)
    {
        int f[] = {0,1};
        return f[n];
    } else {
        mat<mod> m(1);
        mat<mod> r = quickpow(m, n);
        ll ret = r.a[0][1] % mod;
        return ret;
    }
}

ll answer(int n)
{
    return fib<MOD>(fib<TMOD>(n%TTMOD));
}

int main(void)
{
    int T = 0, n = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        printf("%lld\n", answer(n));
    }
    return 0;
}
