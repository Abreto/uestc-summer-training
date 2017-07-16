/* UESTC 2017 Summer Training #8 Div.2. Problem B, by Abreto<m@abreto.net>. */
#include <stdio.h>

typedef struct
{
    char op;
    int x;
}op_t;

int n = 0;
op_t ops[16];

int mess(int x)
{
    int i = 0;
    for(i = 0;i < n;++i)
    {
        if('A' == ops[i].op)
            x += ops[i].x;
        else if('M' == ops[i].op)
            x *= ops[i].x;
        else if ('D' == ops[i].op)
        {
            if( x % ops[i].x )
                return 1;
            x /= ops[i].x;
        }
        else if ('S' == ops[i].op)
        {
            x -= ops[i].x;
            if(x < 0) return 1;
        }
    }
    return 0;
}

int main(void)
{
    int i = 0;
    char opstr[16]; int operand = 0;
    int cnt = 0;

    scanf("%d", &n);
    for(i = 0;i < n;++i)
    {
        scanf("%s %d", opstr, &operand);
        ops[i] = (op_t){opstr[0], operand};
    }

    for(i = 1;i <= 100;++i)
        if(mess(i))
            cnt++;

    printf("%d\n", cnt);
    return 0;
}
