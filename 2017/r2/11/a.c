/* UESTC 2017 Summer Training #28 Div.2. Problem A, by Abreto<m@abreto.net>. */
#include <stdio.h>

int choice[3] = {0};
int check(int i)
{
    int j = 0;
    for(j = 0;j < 3;++j)
        if(j != i && choice[j] == choice[i])
            return 0;
    return 1;
}

int main(void)
{
    int i = 0;
    scanf("%d %d %d", choice, choice+1, choice+2);
    for(i = 0;i < 3;++i)
        if(check(i))
        {
            printf("%c\n", 'A'+i);
            return 0;
        }
    puts("*");
    return 0;
}
