/* UESTC 2017 Summer Training #7 Div.2. Problem H, by Abreto<m@abreto.net>. */
#include <stdio.h>
#include <string.h>

int current;
char buffer[65536];

char stacks[65536];
int top;

void addchar(char ch)
{
    stacks[top++] = ch;
    if(';' == ch)
    {
        stacks[top] = 0;
        printf("%d: ", current);
        puts(stacks);
        top = 0;
    }
}

void proccess(void)
{
    char *p = NULL;
    current = 1; top = 0;
    while(fgets(buffer, 65535, stdin))
    {
        if(0 == strcmp(buffer, "END OF CASE\n")) break;
        p = buffer;
        while(*p && *p != '\n') addchar(*p++);
        ++current;
    }
}

int main(void)
{
    int N = 0;
    scanf("%d", &N);

             /**!!**/    
    /**!!**/ getchar(); /**!!**/
             /**!!**/

    while(N--) proccess();
    return 0;
}
