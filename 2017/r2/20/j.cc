/* MIPT-2016 Pre-Finals Workshop, Taiwan NTU Contest. Problem J, by Abreto<m@abreto.net>. */
#include/*772002*/<bits/stdc++.h>

using namespace std;
#define MAXN    200002

int n;
int a[MAXN], b[MAXN];
int posa[MAXN], posb[MAXN];
int solid[MAXN];
int c[MAXN];
int cnt;

int main(void)
{
    int i = 0;
    scanf("%d", &n);
    for(i = 0;i < n;++i)
    {
        scanf("%d", a+i);
        posa[a[i]] = i;
    }
    for(i = 0;i < n;++i)
    {
        scanf("%d", b+i);
        posb[b[i]] = i;
    }
    for(i = 2*n-2;cnt < n;i--)
    {
        int ai_lb = i-n+1;
        for(int ai = ai_lb;ai < n;++ai)
        {
            int bi = i - ai;
            int pos = (posa[ai] + posb[bi]) % n;
            if(0 == solid[pos])
            {
                solid[pos] = 1;
                c[pos] = i;
                ++cnt;
                if(cnt == n) break;
            }
        }
    }
    for(i = 0;i < n;++i)
        printf("%s%d", i?" ":"", c[i]);
    puts("");
    return 0;
}
