/* Petrozavodsk Summer Training Camp 2016. Problem J, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <algorithm>

using namespace std;

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

typedef long long int ll;
bool fe(ll a, ll b){return (a==b);}
bool fl(ll a, ll b){return (a<b);}
bool fle(ll a, ll b){return (a<=b);}

typedef ll T;
struct point
{
    T x, y;
    point():x(0),y(0){}
    point(T xx, T yy):x(xx),y(yy){}
    void scan(void){scanf(INT64 INT64, &x, &y);}
    void put(void){printf("(" INT64 "," INT64 ")",x,y);}
    T mag2(void){return (x*x+y*y);}
    T X(point b){return (x*b.y-y*b.x);}
    T& operator[](int i){if(0==i)return x;else return y;}
    friend point operator+(point a, point b){return point(a.x+b.x, a.y+b.y);}
    friend point operator-(point a, point b){return point(a.x-b.x, a.y-b.y);}
    friend T operator*(point a, point b){return (a.x*b.x+a.y*b.y);}
    friend bool operator==(point a, point b){return fe(a.x,b.x)&&fe(a.y,b.y);}
};

#define MAXN    2048

ll n, A, B;
ll A2, B2;
point points[MAXN];
point ordered[MAXN][MAXN];

point O;

void gurantee(point *p) /* make p into [0,pi) */
{
    if(p->y < 0)
    {
        point tmp = point(0,0) - *p;
        *p = tmp;
    } else if (0 == p->y && (p->x < 0)) {
        point tmp = point(0,0) - *p;
        *p = tmp;
    }
}

bool compar(const point &a, const point &b)
{
    point Oa = a-O, Ob = b-O;
    if(point(0,0) == Oa) return 1;
    if(point(0,0) == Ob) return 0;
    gurantee(&Oa); gurantee(&Ob);
    ll t = Oa.X(Ob);
    /*if(0 == t) return (Oa.mag2() < Ob.mag2());
    else */return (t > 0);
}

ll gcd(ll a, ll b)
{
    return (0 == b) ? a : gcd(b, a%b);
}

/*point *mylower(int i, const point x)
{
    int l = 0, r = n-1; /* [l,r] 
    while(l < r)
    {
        int mid = (l+r)>>1;
        if( compar(ordered[i][mid], x) )
            l = mid+1;
        else
            r = mid;
    }
    return ordered[i]+l;
}
point *myupper(int i, const point x)
{
    int l = 0, r = n-1;
    while(l < r)
    {
        int mid = (l+r)>>1;
        if( compar(x, ordered[i][mid]) )
            r = mid;
        else
            l = mid+1;
    }
    return ordered[i]+l;
}*/

ll count(int i, int j)
{
    ll ret = 0;
    point A = points[i], B = points[j];
    if(A == B) while(1);
    /*printf("testing "); A.put(); B.put();*/
    point AB = B-A;
    point AR = point(AB.y, -AB.x);
    /*putchar('|'); AR.put();*/
    /*if(0 == AR.x) AR.y = 1;
    else if (0 == AR.y) AR.x = 1;
    else
    {
        ll g = gcd(llabs(AR.x), llabs(AR.y));
        AR.x /= g; AR.y /= g;
    }*/
    O = points[i];
    point *ptr = NULL;
    point NP = O + AR;
    point *l = lower_bound(ordered[i], ordered[i]+n, NP, compar);
    point *r = upper_bound(ordered[i], ordered[i]+n, NP, compar);
    /*point *l = mylower(i, AR);
    point *r = myupper(i, AR);*/
    /*puts(""); putchar('\t');
    for(ptr = l; ptr <= r ; ++ptr) ptr->put();
    puts("");*/
    /*for(ptr = l-1;ptr > ordered[i];--ptr)
    {
        if( (*ptr - A)*AB ) break;
        ll area = (*ptr-A).X(AB);
        if(area < 0) area = -area;
        if(area >= A2 && area <= B2)
        {
            ret++;
            putchar('1');A.put(); B.put(); l->put(); puts("");
        }
    }*/
    for(;l < r;++l)
    {
        if( (*l - A)*AB ) break;
        ll area = (*l-A).X(AB);
        if(area < 0) area = -area;
        if(area >= A2 && area <= B2)
        {
            ret++;
            /*putchar('2');A.put(); B.put(); l->put(); puts("");*/
        }
    }
    return ret;
}

int main(void)
{
    int i = 0, j = 0;
    ll cnt = 0;
    scanf(INT64 INT64 INT64, &n, &A, &B);
    A2 = A * 2ll; B2 = B * 2ll;
    for(i = 0;i < n;++i)
        points[i].scan();
    for(i = 0;i < n;++i)
    {
        for(j = 0;j < n;++j)
            ordered[i][j] = points[j];
        O = points[i];
        sort(ordered[i], ordered[i]+n, compar);
        /*O.put();putchar(':');
        for(j = 0;j < n;++j)
            ordered[i][j].put();
        puts("");*/
    }
    /* ^ checked ^ */
    for(i = 0;i < n;++i)
        for(j = i+1;j < n;++j)
        {
            cnt += count(i,j);
            cnt += count(j,i);
        }
    printf(INT64 "\n", cnt/2ll);
    return 0;
}
