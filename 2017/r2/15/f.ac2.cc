/* UESTC 2017 Summer Training #32 Div.2. Problem F, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>
using namespace std;

#define MAXN 300
#define MAXA (MAXN*MAXN+1)

int ndistinct;
unordered_map<int,int> a2id;

int n;
set<int> app[MAXN<<1];
int delset[MAXN<<1];
set< pair<int,int> > q;
unordered_map<int,int> cnt;
unordered_map<int,int> del;
int selected[MAXN<<1];

int main(void)
{
    int i = 0, j = 0;
    int ai = 0;
    scanf("%d", &n);
    for(i = 0;i < n;++i)
        for(j = 0;j < n;++j)
        {
            scanf("%d", &ai);
            app[n-1+j-i].insert(ai);
        }
    for(i = 0;i < 2*n-1;i++)
        q.insert(make_pair(app[i].size(),i));
    for(i = 0;i < 2*n-1;++i)
        for(auto a:app[i])
        {
            int tmp = cnt[a];
            cnt[a] = tmp + 1;
            del[a] = 0;
        }
    while(!q.empty())
    {
        auto cur = q.begin();
        int setid = cur->second;
        int mina = -1;
        q.erase(cur);
        for(auto a:app[setid])
        {
            if((0 == del[a]) && ( -1 == mina || cnt[a] < cnt[mina] ))
                mina = a;
            cnt[a]--;
        }
        if(-1 == mina)
        {
            puts("NO");
            exit(EXIT_SUCCESS);
        } else {
            delset[setid] = 1;
            del[mina] = 1;
            for(i = 0;i < 2*n-1;++i)
                if(!delset[i])
                {
                    if(app[i].count(mina))
                    {
                        q.erase(make_pair(app[i].size(),i));
                        app[i].erase(mina);
                        q.insert(make_pair(app[i].size(),i));
                    }
                }
            selected[setid] = mina;
        }
    }
    puts("YES");
    for(i = 0;i < 2*n-1;i++)
        printf(" %d", selected[i]);
    puts("");
    return 0;
}
