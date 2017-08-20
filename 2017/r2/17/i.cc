/* Osipovsky Cup 2014 (partially SYSU-Aug-2014 contest). Problem I, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;
#define MAXN    100001

int m, n;
int n_locations;
unordered_map<string,int> name2id;
string names[16];
int app[16][MAXN];

int main(void)
{
    int i = 0, j = 0;
    scanf("%d%d", &m, &n);
    while(m--)
    {
        int a, b; char l[16];
        scanf("%d %d %s", &a, &b, l);
        if(!name2id.count(string(l)))
        {
            names[n_locations] = string(l);
            name2id[string(l)] = n_locations++;
        }
        app[name2id[string(l)]][b]++;
    }
    for(i = 0;i < n_locations;++i)
    {
        int *maxa = &(app[i][1]);
        for(j = 2;j <= n;j++)
            if(app[i][j] > *maxa)
                maxa = &(app[i][j]);
        printf("%s %ld\n", names[i].c_str(), maxa - app[i]);
    }
    return 0;
}
