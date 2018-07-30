/**
 * 2018 Multi-University Training Contest 3.
 * Problem 100x,
 * by Abreto<m@abreto.net>.
 **/
#include <cstdio>
#include <algorithm>

using namespace std;

const char pattern[8][8] = {
    "..+-+",
    "././|",
    "+-+.+",
    "|.|/.",
    "+-+..",
};

struct ac_machine
{
    static const int maxn = 128;
    int a, b, c;
    int w, h;
    char gird[maxn][maxn];
    ac_machine(void)
    {
        init();
    }
    void clear(void)
    {
        for(int i = 0;i < maxn;i++)
            for(int j = 0;j < maxn;j++)
                gird[i][j] = '.';
    }
    void init(void)
    {
        clear();
    }
    void puts(int i, int j, const char *s)
    {
        while(*s)
            gird[i][j++] = *(s++);
    }
    /* draw what left bottom at (i,j)(0-based) */
    void draw(int i, int j)
    {
        puts(i-4, j+2, "+-+");
        puts(i-3, j+1, "/./|");
        puts(i-2, j, "+-+.+");
        puts(i-1, j, "|.|/");
        puts(i, j, "+-+");
        /* for(int x = 0;x < 5;x++)
        {
            for(int y = 0;y < 5;y++)
            {
                if(pattern[x][y] != '.')
                    gird[i-4+x][j+y] = pattern[x][y];
            }
        } */
    }
    void scan(FILE *stream)
    {
        fscanf(stream, "%d%d%d", &a, &b, &c);
        w = 2*a + 2*b + 1;
        h = 2*b + 2*c + 1;
    }
    int ac(void)
    {
        for(int row = 0;row < b;row++)
        {
            /* wall from far to closer */
            for(int col = 0;col < a;col++)
            {
                /* colum from left to right */
                for(int hei = 0;hei < c;hei++)
                {
                    /* block from below to high */
                    // printf("%d,%d\n", h-1 - 2*(b-row-1) - 2*hei, 2*(b-row-1) + 2*col);
                    draw(h-1 - 2*(b-row-1) - 2*hei, 2*(b-row-1) + 2*col);
                }
            }
        }
        for(int i = 0;i < h;i++)
        {
            for(int j = 0;j < w;j++)
                putchar(gird[i][j]);
            ::puts(" ");
        }
        return 0;
    }
};

int main(void)
{
    int T;
    ac_machine *app = new ac_machine();
    scanf("%d", &T);
    /* int a = ~0;
    for(int i = 2;i < max(T,80000000);i++)
        a %= i;
    fprintf(stderr, "%d", a); */
    while(T--)
    {
        app->init();
        app->scan(stdin);
        app->ac();
    }
    return 0;
}
