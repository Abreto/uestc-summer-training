/* UESTC 2017 Summer Training #11 Div.2. Problem L, by Abreto<m@abreto.net>. */
#include <cstdio>

#define INPUTFILE   "lshape.in"
#define OUTPUTFILE  "lshape.out"
using namespace std;

bool fe(int a, int b){return (a==b);}

typedef int T;
struct point
{
    T x, y;
    point():x(0),y(0){}
    point(T xx, T yy):x(xx),y(yy){}
    T mag2(void){return (x*x+y*y);}
    T X(point b){return (x*b.y-y*b.x);}
    T& operator[](int i){if(0==i)return x;else return y;}
    friend point operator+(point a, point b){return point(a.x+b.x, a.y+b.y);}
    friend point operator-(point a, point b){return point(a.x-b.x, a.y-b.y);}
    friend T operator*(point a, point b){return (a.x*b.x+a.y*b.y);}
    friend bool operator==(point a, point b){return fe(a.x,b.x)&&fe(a.y,b.y);}
};

#define MAXN    5001

int N;
point a[MAXN], b[MAXN];

#define valid(o,a,b)    (0==(((a)-(o))*((b)-(o))))

int check(int i, int j)
{
    if(a[i]==a[j]) return valid(a[i],b[i],b[j]);
    else if (a[i]==b[j]) return valid(a[i],a[j],b[i]);
    else if (b[i]==a[j]) return valid(b[i],a[i],b[j]);
    else if (b[i]==b[j]) return valid(b[j],a[i],a[j]);
    else return 0;
}

int main(void)
{
    int i = 0, j = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    int cnt = 0;
    freopen(INPUTFILE, "r", stdin);
    freopen(OUTPUTFILE, "w+", stdout);
    scanf("%d", &N);
    for(i = 0;i < N;++i)
    {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        a[i] = point(x1,y1);
        b[i] = point(x2,y2);
    }
    for(i = 0;i < N;++i)
        for(j = i+1;j < N;++j)
            if(check(i,j))
                cnt++;
    printf("%d\n", cnt);
    return 0;
}
