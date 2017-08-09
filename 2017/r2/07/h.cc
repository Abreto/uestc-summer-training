/* UESTC 2017 Summer Training #23 Div.2. Problem H, by Abreto<m@abreto.net> */
#include <cstdio>
#include <cstring>
#include <unordered_map>

using namespace std;

#define INPUTFILE   "H.in"

const char array_name[] = "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM";
int array_length[128];
unordered_map<int,int> vars[128];

void reload(void)
{
    int i = 0;
    for(i = 0;i < 52;++i)
    {
        array_length[array_name[i]] = -1;
        vars[array_name[i]].clear();
    }
}

/* return 0 if this is declaration or the position of '=' */
int type(char *code)
{
    int i = 0, l = strlen(code);
    for(i = 0;i < l;++i)
        if('=' == code[i])
            return i;
    return 0;
}

#define is_array_name(c)    ((((c)>='a')&&((c)<='z'))||(((c)>='A')&&((c)<='Z')))
#define is_digit(c)         (((c)>='0')&&((c)<='9'))
/* return -1 if an error occured. */
int calc(char *code, int n)
{
    int i = 0;
    if(is_array_name(code[0]))
    {
        char var_name = code[0];
        int indices = calc(code+2, n-3);
        if(indices < 0 || indices >= array_length[var_name]) return -1;
        if(0 == vars[var_name].count(indices)) return -1;
        return vars[var_name][indices];
    } else if(is_digit(code[0])) {
        int num = 0;
        for(i = 0;i < n;++i)
            num = num*10 + (code[i]-'0');
        return num;
    }
}

/* return 1 if bug appear. */
int handle(char *code)
{
    int t = type(code), l = strlen(code);
    if(0 == t) /* declaration */
    {
        int up = calc(code+2, l-3);
        if(up < 0) return 1;
        array_length[code[0]] = up;
    } else {
        int indices = calc(code+2, t-3);
        int value = calc(code+t+1, l-t-1);
        if(indices < 0 || value < 0) return 1;
        if(indices >= array_length[code[0]]) return 1;
        vars[code[0]][indices] = value;
    }
    return 0;
}

void proccess(void)
{
    int failed = 0;
    int nline = 0;
    char line[128] = {0};
    reload();
    while(fgets(line, 128, stdin))
    {
        line[strlen(line)-1] = 0;
        if('.' == line[0])
        {
            if(0 == nline) break;
            printf("%d\n", failed);
            failed = nline = 0;
            reload();
        } else {
            if(failed) continue;
            else
            {
                int t = handle(line);
                ++nline;
                if(t) failed = nline;
            }
        }
    }
}

int main(void)
{
#ifndef ABDEBUG
    freopen(INPUTFILE, "r", stdin);
#endif
    proccess();
    return 0;
}
