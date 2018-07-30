#include <cstdio>
#include <unordered_map>

using namespace std;

typedef long long int ll;

#define mod (1000000007)

#define MAXN    1000000
ll F[100000];

unordered_map<ll,char> app;

int main(void)
{
    ll A, B, C, D, P, n;
    scanf("%lld%lld%lld%lld%lld%lld", &A, &B, &C, &D, &P, &n);
    F[1] = A; F[2] = B;
    for(int i = 3;i < MAXN;i++)
    {
        ll p1 = (C * F[n-2]) % mod;
        ll p2 = (D * F[n-1]) % mod;
        ll p3 = (p1 + p2) % mod;
        ll p4 = (P / i) % mod;
        F[i] = (p3 + p4) % mod;
        printf("F[%d] = %lld, ", i, F[i]);
        if(app.find(F[i]) != app.end()) printf("coincide");
        printf("|%lld, %lld", P/i, P/(P/i));
        puts("");
        app[F[i]] = 1;
    }
    return 0;
}
