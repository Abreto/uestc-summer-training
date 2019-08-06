#include <bits/stdc++.h>

using namespace std;

namespace abreto {

typedef long long int ll;
const int maxn = 1 << 8;
const int alphabet_sz = 26;

const ll seed = 233, p = 1000000007;

int n, m;
char mat[maxn][maxn];

/* rsum[i][0][k] = (mat[i][0] == k)
 * rsum[i][j][k] = rsum[i][j - 1][k] + (mat[i][j] == k) */
int rsum[maxn][maxn][26];

int oncol[maxn];    /* from 0 to n - 1 */
int temp[maxn];
int pr[maxn];
ll proceed(void)
{
    temp[0] = -2;
    for (int i = 0; i < n; i++)
    {
        temp[(i << 1) + 1] = -1;
        temp[(i << 1) + 2] = oncol[i];
    }
    temp[(n << 1) + 1] = -1;
    temp[(n << 1) + 2] = -3;
    int tl = (n << 1) + 2;
    int last = 0, lmid = 0;
    ll ret = 0;
    // for (int i = 0; i <= tl; i++)
    //     fprintf(stderr, " %d", temp[i]);
    // fprintf(stderr, "\n");
    for (int i = 1; i < tl; i++)
    {
        if (i > last)
        {
            pr[i] = 1;
        } else {
            pr[i] = pr[(lmid << 1) - i];
        }
        while(temp[i - pr[i]] == temp[i + pr[i]]) pr[i]++;
        if (temp[i] <= -10) pr[i] = 1;
        if (i + pr[i] - 1 > last)
        {
            last = i + pr[i] - 1;
            lmid = i;
        }
        ret += ((pr[i]) >> 1);
    }
    // for (int i = 0; i <= tl; i++)
    //     fprintf(stderr, " %d,%d", pr[i], (((pr[i]) >> 1)));
    // fprintf(stderr, ";%d\n", ret);
    return ret;
}
ll calc(int l, int r)
{
    for (int i = 0; i < n; i++)
    {
        ll hash = 0ll;
        int nOdd = 0;
        for (int k = 0; k < alphabet_sz; k++)
        {
            int cnt = rsum[i][r + 1][k] - rsum[i][l][k];
            nOdd += (cnt & 1);
            hash = (hash * seed + cnt) % p;
        }
        if (nOdd > 1) hash = -10 - i;
        oncol[i] = hash;
    }
    // fprintf(stderr, "for %d to %d:\n", l, r);
    // for (int i = 0; i < n; i++)
    //     fprintf(stderr, " %d", oncol[i]);
    // fprintf(stderr, "\n");
    return proceed();
}

void main(void)
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> mat[i];
        for (int j = 0; j < m; j++)
            mat[i][j] -= 'a';
        for (int k = 0; k < alphabet_sz; k++)
        {
            rsum[i][1][k] = (mat[i][0] == k);
            for (int j = 1; j < m; j++)
                rsum[i][j + 1][k] = rsum[i][j][k] + (mat[i][j] == k);
        }
    }
    ll ans = 0ll;
    for (int l = 0; l < m; l++)
        for (int r = l; r < m; r++)
            ans += calc(l, r);
    cout << ans << '\n';
}

}

int main(void)
{
    cin.sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(8);
    abreto::main();
    return 0;
}