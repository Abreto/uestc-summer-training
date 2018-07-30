#include <cstdio>
#include <cstring>
#include <unordered_map>

using namespace std;

typedef long long int ll;

#define MAXN    (100010)
#define MOD     (1000000007)

int phi(int x)
{
    int r = x;
    for(int i = 2;i*i <= x;i++)
        if(0 == x%i)
        {
            r = r / i * (i-1);
            while(0 == x%i) x /= i;
        }
    if(x > 1) r = r / x * (x-1);
    return r;
}
int qow(int a, int x, int mod)
{
    int ret = 1; a %= mod;
    while(x)
    {
        if(1 & x) ret = (1ll * ret * a) % mod;
        a = (1ll * a * a) % mod;
        x >>= 1;
    }
    return ret;
}


unordered_map<int,int> eu;
int euler(int x)
{
    if (eu.find(x) == eu.end())
        eu[x] = phi(x);
    return eu[x];
}

char s[MAXN];
int len;

int dfs(int pos, int mod)
{
    if(0 == pos) return 0;
    if(1 == mod) return 0;
    char ch = s[pos-1];
    if('0' == ch)
    {
        return (1ll + dfs(pos-1, mod)) % mod;
    } else if ('1' == ch) {
        return (2ll + 2ll * dfs(pos-1, mod)) % mod;
    } else {
        int before = dfs(pos-1, euler(mod));
        // return (3ll * qow(2, before-1, mod) - 3 + mod) % mod; [x] before could be 0
        return (6ll * qow(2, before, mod) - 3 + mod) % mod;
    }
}

void krow(void)
{
    scanf("%s", s);
    len = strlen(s);
    printf("%d\n", dfs(len, MOD));
}

int main(void)
{
    int T;
    scanf("%d", &T);
    while(T--) krow();
    return 0;
}

