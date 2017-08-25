/* UESTC 2017 Summer Training #34 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

#define MAXN    100001

int n;
char oper[MAXN<<1][4];
int t[MAXN<<1];
int nplus;
double nminus = 0.0;
double ans[MAXN];
double expectation = 0.0;

int main(void)
{
    int i = 0;
    scanf("%d", &n);
    for(i = 0;i < n*2;++i)
        scanf("%s %d", oper[i], t+i);
    for(i = 2*n-1;i >= 0;--i)
    {
        double dt = t[i];
        if('-' == oper[i][0])
        {
            expectation = expectation * (nminus) / (nminus + 1.0);
            expectation += dt / (nminus + 1.0);
            nminus += 1.0;
        } else {
            nminus -= 1.0;
            ans[nplus++] = expectation - dt;
        }
    }
    for(i = n-1;i >= 0;--i)
        printf("%.10lf\n", ans[i]);
    return 0;
}
