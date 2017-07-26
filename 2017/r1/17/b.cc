/* UESTC 2017 Summer Training #17 Div.2. Problem B, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <unordered_map>

using namespace std;
typedef unsigned long long int ul;

#define MAXN    1024
#define WORD    40
#define CHKLEN  64

inline unsigned sfr(unsigned h, unsigned x) {
        return h >> x;
}
int f(long long i, long long j) {
    long long w = i * 1000000ll + j;
        int h = 0;
        for(int k = 0; k < 5; ++k) {
             h += (int) ((w >> (8 * k)) & 255);
              h += (h << 10);
             h ^= sfr(h, 6);
        }
        h += h << 3;
        h ^= sfr(h, 11);
        h += h << 15;
        return sfr(h, 27) & 1;
}

char zerone[MAXN][MAXN];
unordered_map<ul,char> app;
char pat[128];
int pi[128];

int check(int ai, int aj)
{
    int i = 0;
    for(i = 0;i < CHKLEN;++i)
        if( f(ai,aj+i) != zerone[0][i+1] )
            return 0;
    return 1;
}

void compute(void)
{
    int i = 0, k = 0;
    int m = WORD;
    pi[1] = 0;
    for(i = 2;i <= m;i++)
    {
        while(k && pat[k+1]!=pat[i])
            k = pi[k];
        if(pat[k+1] == pat[i])
            k++;
        pi[i] = k;
    }
}
int kmp(int I)
{
    int i = 0, q = 0;
    int ret = 0;
    int n = 1000, m = WORD;
    for(i = 1;i <= n;++i)
    {
        while(q && pat[q+1]!=zerone[I][i])
            q = pi[q];
        if( pat[q+1]==zerone[I][i] )
            q++;
        if(q == m)
            return i-m+1;
    }
    return 0;
}

void proccess(int id)
{
    int ti = 0, tj = 0;
    int i = 0, j = 0, k = 0;
    int ansi = 0, ansj = 0;
    for(i = 0;i < 1000;++i)
        scanf("%s", zerone[i]+1);
    for(i = 0;i < 1000;++i)
        for(j = 1;j <= 1000;++j)
            zerone[i][j] -= '0';
    app.clear();
    for(i = 0;i < 1000;++i)
        for(j = 1;j < 1001-WORD;++j)
        {
            ul w = 0;
            for(k = 0;k < WORD;++k)
            {
                w <<= 1;
                w |= (zerone[i][j+k]);
            }
            app[w] = 1;
        }
    for(ti = 1;ti < 1000000;ti += 1000)
        for(tj = 1;tj < 1000000;tj += 1000)
        {
            ul tw = 0;
            for(k = 0;k < WORD;++k)
            {
                tw <<= 1;
                tw |= f(ti,tj+k);
            }
            if(app.count(tw))
            {
                for(k = 0;k < WORD;++k)
                    pat[k+1] = f(ti,tj+k);
                compute();
                for(i = 0;i < 1000;++i)
                    if(k = kmp(i))
                    {
                        ansi = ti-i;
                        ansj = tj - k+1;
                        break;
                    }
                if( ansi && ansj && check(ansi,ansj) )
                    goto printans;
            }
        }
printans:
    printf("Case #%d: %d %d\n", id, ansi, ansj);
}

int main(void)
{
    int T = 0, nx = 0;
    scanf("%d\n", &T);
    while(T--) proccess(++nx);
    return 0;
}
