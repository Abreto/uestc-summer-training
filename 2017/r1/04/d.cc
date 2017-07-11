/* UESTC 2017 Summer Training #4 Div.2. Problem D, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cmath>
#include <set>
#include <map>

using namespace std;

#define MAXN    600000


int main(void)
{
    int i = 0, ai = 0;
    int N, K;
    set< int > a;
    map<int,int> idx;

    scanf("%d%d", &N, &K);
    for(i = 0;i < K;++i)
    {
        scanf("%d", &ai);
        a.insert(ai);
        idx[ai] = i+1;
    }
    for(auto it:a)
    {
        for(i = it+it;i <= N;i += it)
            if(a.count(i))
                return !printf("%d %d\n", idx[it], idx[i]);
    }
    printf("0 0\n");
    return 0;
}
