/**
 * XVIII Open Cup named after E.V. Pankratiev.
 * Problem F,
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

using namespace std;

class mod_equ_resolver
{
    typedef long long int ll;
    ll a, m;
public:
    mod_equ_resolver(void)
    {
        a = 0ll;
        m = 1ll;
    }
    ll exgcd(ll m, ll n, ll &x, ll &y)
    {
        if(0 == n)
        {
            x = 1;
            y = 0;
            return m;
        }
        ll g = exgcd(n, m%n, x, y);
        ll t = x;
        x = y;
        y = t - m / n * y;
        return g;
    }
    void gurantee(void)
    {
        if(a < 0)
        {
            ll k = (-a) / m;
            a += (k+1ll) * m;
            a = (a + m) % m;
        } else {
            a %= m;
        }
        // printf("x = %lld (mod %lld)\n",a, m);
    }
    int onemore(ll a2, ll m2)
    {
        ll x, y;
        ll g = exgcd(m, m2, x, y);
        assert(x*m+y*m2==g);
        a2 = (a2 + m2) % m2;
        if (abs(a2-a) % g) return -1;
        ll newm = m / g * m2;
        ll newa = a + (a2-a) / g * x * m;
        a = newa;
        m = newm;
        gurantee();
        return 0;
    }
    ll resolve(void)
    {
        return a;
    }
};

class acmachine
{
    static const int maxn = 1000010;
    int n;
    char s[maxn], t[maxn];
    int jmp[maxn];
    char vis[maxn];
    int nc, chain[maxn];
    char origin[maxn], pattern[maxn];
    int f[maxn];
    mod_equ_resolver *resolver;

    void clear(void)
    {
        memset(vis, 0, sizeof(vis));
    }
    void prepare(void)
    {
        int i;
        for(i = 1;i <= n;i++)
            jmp[i] = (i & 1) ? ((i+1)/2) : ((n+i)/2);
    }
    int proccess(void)
    {
        int i, j, k;
        int nmatch = 0, matched[8];
        for(i = 0;i < nc;i++)
        {
            origin[i] = t[chain[i]];
            pattern[i] = s[chain[i]];
        }
        origin[i] = pattern[i] = 0;
        // printf("%s,%s\n", origin, pattern);
        f[0] = j = -1;
        for(i = 1;i < nc;i++)
        {
            while((j >= 0) && pattern[j+1] != pattern[i]) j = f[j];
            if(pattern[j+1] == pattern[i]) j++;
            f[i] = j;
        }
        j = -1; k = 0;
        for(i = 0;(i < (nc<<2)) && (nmatch < 2);i++)
        {
            while((j >= 0) && pattern[j+1] != origin[k]) j = f[j];
            if(pattern[j+1] == origin[k])
            {
                j++;
                if(j+1 == nc)
                {
                    matched[nmatch++] = i - nc + 1;
                    j = f[j];
                }
            }
            if((++k) >= nc) k = 0;
        }
        if(0 == nmatch) return -1;
        assert(nmatch == 2);
        /* proccess with k_0 = matched[0], d = matched[1]-matched[0] */
        // printf("%d,%d\n", matched[0], matched[1]-matched[0]);
        if ( resolver->onemore(matched[0], matched[1]-matched[0]) )
            return -1;
        return 0;
    }
public:
    acmachine(void)
    {
        resolver = new mod_equ_resolver();
        clear();
    }
    void scan(void)
    {
        scanf("%s", s+1);
        scanf("%s", t+1);
        n = strlen(s+1);
        assert(n == strlen(t+1));
    }
    int run(void)
    {
        prepare();
        for(int i = 1;i <= n;i++)
            if(!vis[i])
            {
                nc = 0;
                for(int j = i;!vis[j];j = jmp[j])
                {
                    chain[nc++] = j;
                    vis[j] = 1;
                }
                if(proccess())
                {
                    puts("-1");
                    return 0;
                }
            }
        printf("%lld\n", resolver->resolve());
        return 0;
    }
};

int main(void)
{
    acmachine *app = new acmachine();
    app->scan();
    return app->run();
}
