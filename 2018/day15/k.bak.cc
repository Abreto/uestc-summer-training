#include <cstdio>
#include <cstring>

using namespace std;

#define is_nonzero(x) (((x)>='1')&&((x)<='9'))
#define is_digit(x) (((x)>='0')&&((x)<='9'))

typedef struct ac_machine
{
    static const int MAXN = (1<<8);
    int len;
    char s[MAXN];
    int guarantee(int l, int r)
    {
        // printf("(%d,%d)\n", l, r);
        if(r < l) return -1;
        if('?' == s[l])
        {
            s[l] = '1';
        } else if ('0' == s[l]) {
            if(r == l) return 0;
            if(s[l+1] != '?') return -1;
            s[l+1] = '+';
            return guarantee(l+2, r);
        }
        for(int i = l+1;i <= r;i++)
            if('?' == s[i])
                s[i] = '1';
        return 0;
    }
    void scan(void)
    {
        scanf("%s", s);
        len = strlen(s);
    }
    int ac(void)
    {
        int i;
        int last_sign = -1;
        int failed = 0;
        for(i = 0;i < len;i++)
        {
            if('+' == s[i] || '*' == s[i])
            {
                if( guarantee(last_sign+1, i-1) )
                {
                    failed = 1;
                    break;
                }
                last_sign = i;
            }
        }
        if( guarantee(last_sign+1, len-1) )
        {
            failed = 1;
        }
        puts( failed ? "IMPOSSIBLE" : s );
        return 0;
    }
}am;



int main(void)
{
    am *app = new am();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        app->scan();
        app->ac();
    }
    return 0;
}
