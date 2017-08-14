/* Petrozavodsk Summer-2015. Xudyh Contest. Problem A, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
#define MAXN    128
typedef long long int ll;

const char parrel_dir[] = "LR";
const char vertical_dir[] = "UD";

int go(int lines, int width, char R, char L, char D)
{
    int i = 0, j = 0;
    int ret = 0;
    if(width < 1) return 0;
    for(i = 0;i < lines;++i)
    {
        if(i) {putchar(D);ret++;}
        for(j = 1;j < width;++j)
        {
            ret++;
            if(i&1) putchar(L);
            else putchar(R);
        }
    }
    return ret;
}

int n, m;
ll gird[MAXN][MAXN];
ll maxsum;

void clear(void)
{
    maxsum = 0;
}

void handle_odd(void)
{
    printf("%lld\n", maxsum);
    if(m&1)
    {
        go(m, n, 'D', 'U', 'R');
    } else {    /* 1 == n&1 */
        go(n, m, 'R', 'L', 'D');
    }
}

void handle_even(void)
{
    int i = 0, j = 0;
    ll mincell = 1000000007;
    int mini = 0, minj = 0;
    int steps = 0;
    for(i = 1;i <= n;++i)
        for(j = 1;j <= m;++j)
            if( (i&1)^(j&1) ) /*if( ((1==(i&1))&&(0==(j&1))) || ((0==(i&1))&&(1==(j&1))) )*/
            {
                if(gird[i][j] < mincell)
                {
                    mincell = gird[i][j];
                    mini = i; minj = j;
                }
            }
    printf("%lld\n", maxsum - mincell);
    i = mini; j = minj;
    /*printf("Drop (%d,%d)\n", i, j);*/
    if(1 == j)
    {
        /*puts("1");*/
        steps = go(i-2, 2, 'R', 'L', 'D');
        if(i>2) {putchar('D');}
        putchar('R');putchar('D'); if(i<n) putchar('D');
        steps = go(n-i, 2, 'L', 'R', 'D');
        if(2<m) putchar('R');
        go(m-2, n, 'U', 'D', 'R');
    } else if (m == j) {
        /*puts("2");*/
        steps = go(m-2, n, 'D', 'U', 'R');
        if(m>2) putchar('R');
        steps = go(i-1, 2, 'R', 'L', 'D');
        if(i>1) {putchar('D');}
        putchar('D');putchar('R'); if(i+1<n) putchar('D');
        go(n-i-1, 2, 'L', 'R', 'D');
    } else if (1 == i) {
        /*puts("3");*/
        steps = go(j-2, n, 'D', 'U', 'R');
        if(j>2) {putchar('R');}
        putchar('D');putchar('R'); if(i+1<n) putchar('D');
        steps = go(n-2, 2, 'L', 'R', 'D');
        if(j<m) putchar('R');
        go(m-j, n, 'U', 'D', 'R');
    } else if (n == i) {/**/
        /*puts("4");*/
        steps = go(j-1, n, 'D', 'U', 'R');
        if(j>1) putchar('R');
        steps = go(i-2, 2, 'R', 'L', 'D');
        if(n>2) {putchar('D');}
        putchar('R');putchar('D'); if(j+1<m)putchar('R');
        go(m-j-1, n, 'U', 'D', 'R');
    } else if(j&1) {
        /*puts("5");*/
        steps = go(j-2, n, 'D', 'U', 'R');
        if(j>2) putchar('R');
        steps = go(n-i-1, 2, 'R', 'L', 'U');
        if(i+1<n) {putchar('U');}
        putchar('L');putchar('U'); if(i>1) putchar('U');
        steps = go(i-1, 2, 'R', 'L', 'U');
        if(j<m) putchar('R');
        go(m-j, n, 'D', 'U', 'R');
    } else {
        /*puts("6");*/
        //steps = go(n, j-1, 'R', 'L', 'D');  // <-------
          steps = go(j-1, n, 'D', 'U', 'R');    // <-------
        if(j>1) putchar('R');
        steps = go(n-i, 2, 'R', 'L', 'U');
        if(i<n) {putchar('U');}
        putchar('U');putchar('L'); if(i>2)putchar('U');
        steps = go(i-2, 2, 'R', 'L', 'U');
        if(j+1<m) putchar('R');
        go(m-j-1, n, 'D', 'U', 'R');
    }
}

void proc(void)
{
    int i = 0, j = 0;
    for(i = 1;i <= n;++i)
        for(j = 1;j <= m;++j)
        {
            scanf("%lld", &(gird[i][j]));
            maxsum += gird[i][j];
        }
    if((n&1) || (m&1)) handle_odd();
    else handle_even();
}

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d %d", &n, &m);
        clear();
        proc();
        puts("");
    }
    return 0;
}
