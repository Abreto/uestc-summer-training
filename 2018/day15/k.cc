#include <cstdio>
#include <cstring>

using namespace std;

class abio
{
    static const unsigned BUF_SZ = 65535;
    FILE *istream, *ostream;
    char ibuf[BUF_SZ], obuf[BUF_SZ];
    bool reached_eof;
    size_t ip, isz;
    size_t op, osz;
    inline void clear_ibuf(void) { ip = isz = 0u; }
    inline void clear_obuf(void) { op = osz = 0u; }
    inline void clear_buffer(void)
    {
        reached_eof = false;
        clear_ibuf();
        clear_obuf();
    }
    inline size_t read_buffer(void)
    {
        isz = fread(ibuf, sizeof(char), BUF_SZ, istream);
        ip = 0;
        return isz;
    }
    inline size_t write_buffer(void)
    {
        if(osz)
        {
            size_t ret = fwrite(obuf+op, sizeof(char), osz-op, ostream);
            op += ret;
            if(op == osz) clear_obuf();
            return ret;
        }
        return 0;
    }
    inline abio &reach_eof(void)
    {
        reached_eof = true;
        return (*this);
    }
public:
    abio(FILE *input = stdin, FILE *output = stdout)
    {
        this->istream = input;
        this->ostream = output;
        clear_buffer();
    }
    abio(const char *input, const char *output)
    {
        this->istream = fopen(input, "r");
        this->istream = fopen(output, "w+");
        clear_buffer();
    }
    ~abio(void)
    {
        write_buffer();
        fclose(istream);
        fclose(ostream);
    }
    operator bool() const
    {
        return (!reached_eof);
    }
    inline int getchar(void)
    {
        if(0 == isz || isz == ip) read_buffer();
        if(0 == isz || isz == ip) return EOF;
        return ibuf[ip++];
    }
    inline int putchar(int ch)
    {
        if(osz == BUF_SZ) write_buffer();
        if(osz == BUF_SZ) return EOF;
        return (obuf[osz++] = ch);
    }
    abio &read_int(int &x)
    {
        int flag = 0, ch = getchar();
        if(EOF == ch) return (this->reach_eof());
        x = 0;
        while((EOF!=ch)&&(('-'!=ch)&&((ch<'0')||(ch>'9'))))ch=getchar();
        if(EOF==ch) return (this->reach_eof());
        if('-'==ch){flag=1;ch=getchar();}
        //if(EOF==ch) return (this->reach_eof());
        for(;(((ch>='0')&&(ch<='9')));ch=getchar()){x*=10;x+=(ch-'0');}
        //if(EOF==ch)this->reach_eof();
        if(flag)x*=(-1);
        return (*this);
    }
    abio &read_ll(long long int &x)
    {
        int flag = 0, ch = getchar();
        if(EOF == ch) return (this->reach_eof());
        x = 0ll;
        while((EOF!=ch)&&(('-'!=ch)&&((ch<'0')||(ch>'9'))))ch=getchar();
        if(EOF==ch) return (this->reach_eof());
        if('-'==ch){flag=1;ch=getchar();}
        //if(EOF==ch) return (this->reach_eof());
        for(;(((ch>='0')&&(ch<='9')));ch=getchar()){x*=(10ll);x+=(ch-'0');}
        //if(EOF==ch)this->reach_eof();
        if(flag)x*=(-1);
        return (*this);
    }
    /* set interrupt as '\n' to read a whole line. */
    abio &read_s(char *s, const char interrupt = ' ')
    {
        int ch = getchar();
        while((EOF!=ch)&&(ch<'!'||ch>'~'))ch=getchar();
        if(EOF==ch) return (this->reach_eof());
        for(;(EOF!=ch)&&(interrupt!=ch)&&(ch>=' '&&ch<='~');ch=getchar())(*s++)=ch;
        (*s)=0;
        return (*this);
    }
    abio &write_int(int x, char append = 0)
    {
        int d[20],nd=0;
        if(0==x) putchar('0');
        if(x<0){putchar('-');x=-x;}
        while(x){d[nd++]=x%10;x/=10;}
        while(nd--)putchar('0'+d[nd]);
        if(append)putchar(append);
        return (*this);
    }
    abio &write_ll(long long int x, char append = 0)
    {
        int d[20],nd=0;
        if(0==x) putchar('0');
        if(x<0){putchar('-');x=-x;}
        while(x){d[nd++]=x%10;x/=10;}
        while(nd--)putchar('0'+d[nd]);
        if(append)putchar(append);
        return (*this);
    }
    abio &write_s(const char *s, char append = 0)
    {
        while(*s) putchar(*s++);
        if(append) putchar(append);
        return (*this);
    }
}io;

#define is_nonzero(x) (((x)>='1')&&((x)<='9'))
#define is_digit(x) (((x)>='0')&&((x)<='9'))

const int MAXN = (1<<9);
char s[MAXN];
typedef struct ac_machine
{
    int len;
    void scan(void)
    {
        io.read_s(s);
        // scanf("%s", s);
        len = strlen(s);
    }
    int ac(void)
    {
        int i;
        int failed = 0;
        int first_of_number = 1;
        for(i = 0;i < len;i++)
        {
            if('+' == s[i] || '*' == s[i])
            {
                if(first_of_number)
                {
                    failed = 1;
                    break;
                }
                /* new segment */
                first_of_number = 1;
            } else {
                if(first_of_number)
                {
                    if('0' == s[i])
                    {
                        if((i+1) < len && is_digit(s[i+1]))
                        {
                            failed = 1;
                            break;
                        }
                        if('?' == s[i+1]) s[i+1] = '+';
                    } else {
                        if('?' == s[i])
                        {
                            s[i] = '1';
                        }
                    }
                    first_of_number = 0;
                } else {
                    if('?' == s[i])
                        s[i] = '1';
                }
            }
        }
        if(first_of_number) failed = 1;
        io.write_s( failed ? "IMPOSSIBLE" : s, '\n');
        // puts( failed ? "IMPOSSIBLE" : s );
        return 0;
    }
}am;



int main(void)
{
    am *app = new am();
    int T;
    io.read_int(T);
    // scanf("%d", &T);
    while(T--)
    {
        app->scan();
        app->ac();
    }
    return 0;
}
