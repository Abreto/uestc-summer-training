#include <cstdio>
#include <set>

using namespace std;

int N, Q, P;
set<int> balls;

int main(void)
{
    int i = 0;
    int dec = 0;
    scanf("%d%d%d", &N, &Q, &P);
    for(i = 0;i < N;i++)
    {
        int pi;
        scanf("%d", &pi);
        balls.insert(pi);
    }
    while(Q--)
    {
        int command;
        scanf("%d", &command);
        if(1 == command)
        {
            int x;
            scanf("%d", &x);
            balls.insert(x + dec);
        } else {
            int leftmost = *(balls.begin());
            balls.erase(leftmost);
            dec++;
            balls.insert(P - 1 + dec);
        }
    }
    for(auto p : balls)
        printf("%d ", p - dec);
    puts("");
    return 0;
}
