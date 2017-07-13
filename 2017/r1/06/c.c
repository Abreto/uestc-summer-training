/* UESTC 2017 Summer Training #6 Div.2. Problem C, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <string.h>

#define INPUTFILE   "alignment.in"
#define OUTPUTFILE  "alignment.out"

#define MAXLEN  128
#define MAXLINE 256
#define MAXNLINE 1024

int max(int a,int b){return (a>b)?a:b;}
void putspaces(int n){while(n--)putchar(32);}

char words[MAXNLINE][MAXLINE][MAXLEN];
int nlines, nwords[MAXNLINE], wlen[MAXNLINE][MAXLINE];
int width[MAXLINE];

char* scanword(char *src, char *dest)
{
    int copied = 0;
    while(' ' == *src) src++;
    while(0 != *src && ' ' != *src)
    {
        *dest++ = *src++;
        copied = 1;
    }
    *dest = 0;
    if(0 == copied) return NULL;
    return src;
}

int main(void)
{
    int i = 0, j = 0;
    char line[MAXLINE] = {0};
    char word[MAXLEN] = {0};

    freopen(INPUTFILE, "r", stdin);
    freopen(OUTPUTFILE, "w+", stdout);

    while(gets(line))
    {
        char *last = line;
        int *nword = &(nwords[nlines]);
        do
        {
            last = scanword(last, words[nlines][(*nword)]);
            if(NULL == last) break;
            wlen[nlines][*nword] = strlen(words[nlines][*nword]);
            width[*nword] = max(width[*nword], wlen[nlines][*nword]+1);
            (*nword)++;
        }while(*last);
        nlines++;
    }

    for(i = 0;i < nlines;++i)
    {
        for(j = 0;j < nwords[i]-1;++j)
        {
            printf("%s", words[i][j]);
            putspaces(width[j]-wlen[i][j]);
        }
        puts(words[i][nwords[i]-1]);
    }
    return 0;
}
