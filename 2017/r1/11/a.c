/* UESTC 2017 Summer Training #11 Div.2. Problem A, by Abreto<m@abreto.net>. */
#include <stdio.h>

#define INPUTFILE   "bulls.in"
#define OUTPUTFILE  "bulls.out"

int main(void)
{
    int i = 0, j = 0;
    char sec[8] = {0}, gus[8] = {0};
    int nbulls = 0, ncows = 0;
    char bulled[8] = {0};
    freopen(INPUTFILE, "r", stdin);
    freopen(OUTPUTFILE, "w+", stdout);
    scanf("%s", sec);
    scanf("%s", gus);
    for(i = 0;i < 4;++i)
        if(sec[i] == gus[i])
        {
            nbulls++;
            bulled[i] = 1;
        }
    for(i = 0;i < 4;++i)
        if(!bulled[i])
            for(j = 0;j < 4;++j)
                if(0 == bulled[j] && gus[i]==sec[j])
                    ncows++;
    printf("%d %d\n", nbulls, ncows);
    return 0;
}
