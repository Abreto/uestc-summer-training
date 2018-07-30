#include <cstdio>
#include <string>

using namespace std;

#define MAXN    100000

char path[MAXN+10];
string workspace;

int main(void)
{
    int i = 0;
    scanf("%s", path);
    workspace = string(path);
    for(i = 0;i < workspace.size();i++)
    {
        if(i > 0) if(workspace[i] == workspace[i-1]) {
            workspace.erase(i-1, 1);
            workspace.erase(i-1, 1);
            i -= 2;
        }
        if(i > 3) if (workspace[i-1] == workspace[i-3])
            if(workspace[i] == workspace[i-4] && workspace[i] == workspace[i-2]) {
                workspace.erase(i, 1);
                workspace.erase(i-4, 1);
                i -= 5;
            }
    }
    puts( workspace.size() ? "open" : "closed" );
    return 0;
}
