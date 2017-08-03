/* UESTC 2017 Summer Training Round2 #03 Div.2. Problem H, by . */
#include <cstdio>

using namespace std;

#define INPUT   "pocnitoare.in"
#define OUTPUT  "pocnitoare.out"

#define MAXB    32
#define MAXQ    10000003

#define BLOCKID(q)  (((q)-1)/MAXB)
#define BLOCKL(id)  ((id)*MAXB+1)

typedef long long int ll;
ll N, A, B;
ll X1;
ll Q, Q1;
int xtable[MAXQ/MAXB+1];

inline ll nextX(ll i, ll X)
{
    ll temp = (i * (ll)X) % N;
    return (temp+A)%N;
}
inline ll nextQ(ll i, ll X)
{
    ll temp = (i*(ll)X) % MAXQ;
    return (temp+B)%MAXQ+1;
}

int main(void)
{
    int i = 0, j = 0;
    ll Xi = 0, Qi = 0;
    freopen(INPUT, "r", stdin);
    freopen(OUTPUT, "w+", stdout);
    scanf("%I64d %I64d %I64d %I64d %I64d %I64d", &N, &A, &B, &X1, &Q, &Q1);
    int lastid = -1;
    Xi = X1;
    for(i = 1;i <= MAXQ;i++)
    {
        if(0 == (i-1)%MAXB)
            xtable[BLOCKID(i)] = Xi;
        Xi = nextX(i, Xi);
    }
    Qi = Q1;
    for(i = 1;i <= Q;++i)
    {
        ll base = xtable[BLOCKID(Qi)];
        ll bl = BLOCKL(BLOCKID(Qi));
        while(bl < Qi)
        {
            base = nextX(bl++, base);
        }
        printf("%lld\n", base);
        Qi = nextQ(i, base);
    }
    return 0;
}
