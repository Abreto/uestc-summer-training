#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

typedef long long int ll;

void set1(ll &dest, int i, int j)
{
    dest |= (1ll << ((i-1) * 8 + j - 1));
}

int n;
int m1, m2;
map<ll,char> exist;
int phi[10];
char mat[10][10];
ll g2;

void check(void)
{
    int i, j;
    ll g1 = 0;
    for(i = 1;i <= n;i++) for(j = 1;j <= n;j++)
    {
        if(mat[phi[i]][phi[j]])
        {
            set1(g1, i, j);
            set1(g1, j, i);
        }
    }
    if((g1 & g2) == g1)
        exist[g1] = 1;
}

int main(void)
{
    int i, j, a, b;
    while( EOF != scanf("%d%d%d", &n, &m1, &m2) )
    {
        for(i = 1;i <= n;i++) for(j = 1;j <= n;j++) mat[i][j] = 0;
        g2 = 0;
        for(i = 0;i < m1;i++)
        {
            scanf("%d%d", &a, &b);
            mat[a][b] = mat[b][a] = 1;
        }
        for(i = 0;i < m2;i++)
        {
            scanf("%d%d", &a, &b);
            set1(g2, a, b);
            set1(g2, b, a);
        }
        exist.clear();
        for(i = 1;i <= n;i++) phi[i] = i;
        do
        {
            check();
        }while(next_permutation(phi+1, phi+n+1));
        printf("%lu\n", exist.size());
    }
    return 0;
}