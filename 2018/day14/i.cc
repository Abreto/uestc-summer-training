#include <cassert>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;
typedef vector<int> vi;
#define pb push_back
typedef set<int> si;
#define in insert

struct ac_machine
{
    static const int MAXN = 10100;
    static int n;
    static int ne, no;
    static int e[MAXN>>1], o[MAXN>>1];
    static int nog;
    static si og[MAXN<<1];
    static int ngs;
    static int gs[MAXN>>1];
    static int sum[MAXN>>1];
    int count;

    /** return if e[i] < o[j] */
    int ask(int i, int j)
    {
        char res[8];
        // if(n == 20 && count++ > 100) while(1) printf("1");
        printf("? %d %d\n", i, j);
        fflush(stdout);
        scanf("%s", res);
        // assert(res[0] == '<' || res[0] == '>');
        return ('<' == res[0]);
    }
    void scan(void)
    {
        count = 0;
        scanf("%d", &n);
        ne = n / 2;
        no = (n + 1) / 2;
    }
    int ac(void)
    {
        int i, j;
        if(n <= 2)
        {
            if(1 == n) puts("! 1");
            else puts("! 2 1");
            fflush(stdout);
            return 0;
        }
        /* get e[1] first { */
        og[1].clear(); og[2].clear();
        for(i = 1;i <= no;i++)
            if(ask(1, i))
            {
                og[2].in(i);
            } else {
                og[1].in(i);
            }
        sum[0] = 0;
        sum[1] = og[1].size();
        e[1] = 2 * sum[1];
        nog = ngs = 1;
        gs[1] = 1;
        if(og[2].size())
        {
            sum[2] = sum[1] + og[2].size();
            gs[2] = 2;
            nog++;
            ngs++;
        }
        // if(20 == n && (e[1] == 16)) while(1) printf("1");
        /* } */
        i=1;
        //printf("e[%d]:%d\n", i, e[i]);
            for(j = 1;j <= ngs;j++)
            {
                //printf("%d(%d):", j, sum[j]);
                for(auto x:og[gs[j]]); //printf(" %d", x);
                //puts("");
            }
        for(i = 2;i <= ne;i++)
        {
            int l = 1, r = ngs;
            
            while((l+1) < r)
            {
                int mid = (l+r)>>1;
                if(ask(i, *(og[gs[mid]].begin())))
                {
                    /* e[i] < some of og[mid] */
                    r = mid;
                } else {
                    /* e[i] > some of og[mid] */
                    l = mid;
                }
            }
            int base = sum[l-1];
            si left, mid, right;
            for(j = l;j <= r;j++)
                for(auto odd : og[gs[j]])
                    if( ask(i, odd) )
                        right.in(odd);
                    else
                        left.in(odd);
            e[i] = (base + left.size())<<1;
            for(j = ngs;j >= r;j--)
                gs[j+1] = gs[j];
            if(left.size() < og[gs[l]].size())
            {
                for(auto mid_candidate:og[gs[l]])
                    if(left.find(mid_candidate) == left.end())
                        mid.in(mid_candidate);
                og[++nog] = left;
                gs[l] = nog;
                og[++nog] = mid;
                gs[r] = nog;
                ngs++;
            } else {
                for(auto mid_candidate:og[gs[r]])
                    if(right.find(mid_candidate) == right.end())
                        mid.in(mid_candidate);
                og[++nog] = mid;
                gs[r] = nog;
                if(right.size())
                {
                    og[++nog] = right;
                    gs[r+1] = nog;
                    ngs++;
                }
            }
            for(j = l;j <= ngs;j++)
                sum[j] = sum[j-1] + og[gs[j]].size();
            //printf("e[%d]:%d\n", i, e[i]);
            for(j = 1;j <= ngs;j++)
            {
                //printf("%d(%d):", j, sum[j]);
                for(auto x:og[gs[j]]);// printf(" %d", x);
                //puts("");
            }
        }
        printf("!");
        for(i = 1;i <= ne;i++) printf(" %d", e[i]);
        // assert(no == nog);
        for(i = 1;i <= ngs;i++) o[*(og[gs[i]].begin())] = 2*i-1;
        for(i = 1;i <= no;i++) printf(" %d", o[i]);
        puts("");
        // printf("no: %d\n", no);
        fflush(stdout);
        return 0;
    }
};

#define am ac_machine

int ac_machine::n = 0;
int am::ne = 0, am::no = 0;
int ac_machine::e[MAXN>>1] = {0}, ac_machine::o[MAXN>>1] = {0};
int am::nog = 0;
si ac_machine::og[MAXN<<1];
int am::ngs = 0;
int am::gs[MAXN>>1] = {0};
int am::sum[MAXN>>1] = {0};

int main(void)
{
    ac_machine *app = new ac_machine();
    app->scan();
    return app->ac();
}
