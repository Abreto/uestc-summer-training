/* UESTC 2017 Summer Training #10 Div.2. Problem I, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <set>

using namespace std;

#define MAXN    100001

int n;
int A[MAXN];
int lok[MAXN], rok[MAXN];

int main(void)
{
    int i = 0;
    set<int> app, bpp;
    int cnt = 0;

    scanf("%d", &n);
    for(i = 0;i < n;++i)
        scanf("%d", A+i);
    for(i = 0;i < n;++i)
    {
        if(app.lower_bound(A[i])==app.end())
            lok[i] = 1;
        app.insert(A[i]);
    }
    rok[n-1] = 1; bpp.insert(A[n-1]);
    for(i = n-2;i >= 0;--i)
    {
        if( (*(bpp.begin())) > A[i] )
            rok[i] = 1;
        bpp.insert(A[i]);
    }
    for(i = 0;i < n;++i)
        if(lok[i] && rok[i])
            ++cnt;

    printf("%d\n", cnt);
    return 0;
}
