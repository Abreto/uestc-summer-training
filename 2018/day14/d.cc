#include <cstdio>
#include <algorithm>

using namespace std;

struct ac_machine
{
    int S[3];
    int choose;
    /* map cordnate = (3+virtual-choose) % 3. */
    inline int cord(int j)
    {
        return (3 + j - choose) % 3;
    }
    void draw(void)
    {
        int i, j;
        int cords[3] = {0};
        int occupied[128][128] = {0};
        cords[cord(2)] = 0;
        int a = S[choose], b = S[(choose+1)%3], c = S[(choose+2)%3];
        int minbc = min(b,c);
        for(i = 0;i < minbc;i++)
        {
            j = minbc - 1 - i;
            cords[cord(0)] = i;
            cords[cord(1)] = j;
            occupied[i][j] = 1;
            printf("%d %d %d\n", cords[0], cords[1], cords[2]);
            a--;
        }
        for(i = minbc;i < b;i++)
        {
            cords[cord(0)] = i;
            cords[cord(1)] = 0;
            occupied[i][0] = 1;
            printf("%d %d %d\n", cords[0], cords[1], cords[2]);
            a--;
        }
        for(i = minbc;i < c;i++)
        {
            cords[cord(0)] = 0;
            cords[cord(1)] = i;
            occupied[0][i] = 1;
            printf("%d %d %d\n", cords[0], cords[1], cords[2]);
            a--;
        }
        for(i = 0;(i < b) && (a > 0);i++)
        {
            for(j = 0;(j < c) && (a > 0);j++)
            {
                if(0 == occupied[i][j])
                {
                    cords[cord(0)] = i;
                    cords[cord(1)] = j;
                    occupied[i][j] = 1;
                    printf("%d %d %d\n", cords[0], cords[1], cords[2]);
                    a--;
                }
            }
        }
    }
    void scan(void)
    {
        scanf("%d%d%d", S, S+1, S+2);
    }
    int ac(void)
    {
        int i;
        for(i = 0;i < 3;i++)
            if(S[i] > (S[(i+1)%3]*S[(i+2)%3]))
            {
                puts("-1");
                return 0;
            }
        for(i = 0;i < 3;i++)
            if(S[i] >= S[(i+1)%3] && S[i] >= S[(i+2)%3])
            {
                printf("%d\n", S[i]);
                choose = i;
                draw();
                return 0;
            }
        puts("-1");
        return 0;
    }
};

int main(void)
{
    ac_machine *app = new ac_machine();
    app->scan();
    return app->ac();
}
