/* UESTC 2017 Summer Training Round2 #03 Div.2. Problem , by Abreto<m@abreto.net>. */
#include <cstdio>
#include <string>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

#define MAXM    128

char gird[MAXM][MAXM];
int M, N;
string ans[2];

bool compar(string a, string b)
{
    return (a>b);
}

int npi;
int len;
string pieces[MAXM];
void handle(int id)
{
    int i = 0, j = 0, k = 0;
    sort(pieces, pieces+npi, compar);
    for(i = 0;i < npi;i++)
    {
        for(j = 0;j < len;++j)
            if( '0' != pieces[i][j] )
            {
                string temp = pieces[i].substr(j);
                for(k = 0;k < npi;++k)
                    if(k != i)
                        temp += pieces[k];
                temp += pieces[i].substr(0,j);
                if(temp > ans[id]) ans[id] = temp;
            }
    }
}

int main(void)
{
    int i = 0, j = 0;
    scanf("%d %d", &N, &M);
    for(i = 0;i < N;++i)
        scanf("%s", gird[i]);
    for(i = 0;i < N;++i)
        pieces[i] = gird[i];
    len = M; npi = N;
    handle(0);
    len = N; npi = M;
    for(i = 0;i < M;++i)
    {
        pieces[i] = "";
        for(j = 0;j < N;++j)
            pieces[i] += gird[j][i];
    }
    handle(1);
    printf("%s\n", max(ans[0],ans[1]).c_str());
    return 0;
}
