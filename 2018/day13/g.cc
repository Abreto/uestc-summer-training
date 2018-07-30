/**
 * 2018 Multi-University Training Contest 3.
 * Problem 100x,
 * by Abreto<m@abreto.net>.
 **/
#include <cassert>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
#define pb push_back
typedef pair<int,int> pii;
#define mp make_pair
#define fi first
#define se second

typedef long long int ll;

map<pii,int> sml_id;

struct point
{
    ll x, y;
    int id;
    point(void){}
    point(ll xx, ll yy, int ii):x(xx),y(yy),id(ii){}
    ll mag(void) const { return (x*x + y*y); }
    point operator-(const point &o) const
    {
        return point(x - o.x, y - o.y, -1);
    }
    ll operator^(const point &o) const
    {
        return (x * o.y - o.x * y);
    }
    bool operator<(const point &o) const
    {
        ll det = (*this) ^ o;
        if(0 == det) return (mag() > o.mag());
        else return (det < 0);
    }
};

struct ac_machine
{
    static const int maxn = 200020;
    int u;
    int n;
    int x[maxn];
    int xn;
    int case0;
    point pt[maxn];
    int top;
    point convex[maxn];
    ac_machine(void)
    {
        clear();
        init();
    }
    void clear(void)
    {
        sml_id.clear();
        case0 = 1;
    }
    void init(void)
    {
        ;
    }
    void scan(FILE *stream)
    {
        int i;
        scanf("%d", &n);
        for(i = 0;i < n;i++)
        {
            int xi, yi;
            scanf("%d%d", &xi, &yi);
            x[i+1] = xi;
            if(yi) case0 = 0;
            if(sml_id.find(mp(xi,yi)) == sml_id.end()) sml_id[mp(xi,yi)] = i+1;
            else sml_id[mp(xi,yi)] = min(sml_id[mp(xi,yi)], i+1);
            if(i == n-1) xn = xi;
        }

        u = 0;
        for(auto pnt : sml_id)
        {
            pt[u++] = point(pnt.fi.fi, pnt.fi.se, pnt.se);
            // printf("%d:%lld,%lld\n", pt[u-1].id, pt[u-1].x, pt[u-1].y);
        }
    }
    int ac(void)
    {
        if(case0)
        {
            /* y_i === 0 */
            int maxx = -1;
            vector<int> vi;
            for(int i = 0;i < u;i++)
                vi.pb(pt[i].id);
            sort(vi.begin(), vi.end());
            for(int i = 0;i < u;i++)
            {
                if( x[vi[i]] <= maxx ) continue;
                printf("%d%s", vi[i], (i==u-1)?"\n":" ");
                maxx = x[vi[i]];
            }
        } else {
            int i, j;
            sort(pt+1, pt+u);
            /* for(i = 0;i < u;i++)
                printf("%d: %lld %lld\n", pt[i].id, pt[i].x, pt[i].y); */
            convex[0] = pt[0];
            convex[1] = pt[1];
            top = 1;
            for(i = 2;i < u;i++)
            {
                // printf("considering %d:%lld,%lld\n", pt[i].id, pt[i].x, pt[i].y);
                while(top && (((convex[top]-convex[top-1])^(pt[i]-convex[top])) > 0)) top--;
                convex[++top] = pt[i];
                if(pt[i].x == xn) break;
            }
            // for(int a = 0;a <= top;a++) printf("%d:%lld %lld\n", convex[a].id, convex[a].x, convex[a].y);
            assert(convex[top].x == xn);
            printf("1");
            vector<int> eqslope;
            for(i = 1;(i < u);i++)
                if(0 == ( pt[i] ^ convex[1] ))
                    eqslope.pb(pt[i].id);
            int shoat = convex[1].id;
            sort(eqslope.begin(), eqslope.end());
            int maxx = 0;
            for(auto id:eqslope)
            {
                if(x[id] <= maxx) continue;
                printf(" %d", id);
                maxx = x[id];
                if(id == shoat) break;
            }
            for(i = 1;i < top;i++)
            {
                /* pt[i] has been outputed */
                eqslope.clear();
                eqslope.pb(convex[i+1].id);
                for(j = i+2;(j <= top) && (0 == ((convex[j]-convex[i]) ^ (convex[i+1]-convex[i])));j++)
                {
                    eqslope.pb(convex[j].id);
                }
                j--; eqslope.pop_back();
                if(eqslope.size())
                {
                    maxx = 0;
                    sort(eqslope.begin(), eqslope.end());
                    for(auto spot : eqslope)
                    {
                        if(spot > convex[j].id) break;
                        if(x[spot] <= maxx) continue;
                        printf(" %d", spot);
                        maxx = x[spot];
                    }
                }
                printf(" %d", convex[j].id);
                i = j - 1;
            }
            puts("");
        }
        return 0;
    }
};

int main(void)
{
    ac_machine *app = new ac_machine();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        app->clear();
        app->scan(stdin);
        app->ac();
    }
    return 0;
}
