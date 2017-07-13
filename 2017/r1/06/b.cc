/* UESTC 2017 Summer Training #6 Div.2. Problem B, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

struct INT
{
    vector<char> d;
    void read(void)
    {
        char line[128] = {0};
        scanf("%s", line);
        int len = strlen(line);
        d.clear();
        for(int i = len;i > 0;--i)
            d.push_back(line[i-1]-'0');
    }
    void show(void){for(int i=0;i<d.size();++i)printf("%d",d[i]);printf("\n");}
    void push_back(int x){d.push_back(x);}
    INT operator+(INT b)
    {
        int i = 0; int cf = 0;
        INT ans; int la = d.size(), lb = b.d.size();
        if( lb < la ) return (b+(*this));
        for(i = 0;i < min(la,lb);++i)
        {
            int t = d[i]+b.d[i]+cf;
            ans.push_back(t%10);
            cf = t/10;
        }
        for(i = la;i < lb;++i)
        {
            int t = b.d[i] + cf;
            ans.push_back(t%10);
            cf = t/10;
        }
        if(cf) ans.push_back(1);
        return ans;
    }
    bool operator==(const INT b) const
    {
        int la = d.size(), lb = b.d.size();
        if(la != lb) return 0;
        else
        {
            for(int i = 0;i < la;++i)
                if(d[i] != b.d[i])
                    return 0;
            return 1;
        }
    }
};

int main(void)
{
    int i = 0, j = 0, k = 0;
    INT X[3];

    for(i = 0;i < 3;++i)
        X[i].read();
    for(i = 0;i < 3;++i)
        for(j = 0;j < 3;++j)
            for(k = 0;k < 3;++k)
                if(X[i]+X[j]==X[k])
                    return !printf("YES\n");
    printf("NO\n");
    return 0;
}
