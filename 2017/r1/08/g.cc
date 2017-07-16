/* UESTC 2017 Summer Training #8 Div.2. Problem G, by Abreto<m@abreto.net>. */
#include <cstdio>
#include <set>
#include <string>
#include <utility>

using namespace std;

int main(void)
{
    int n = 0;
    char fn[16] = {0}, ln[16] = {0};
    set< pair<string,string> > names;
    scanf("%d", &n);
    while(n--)
    {
        scanf("%s %s", fn, ln);
        names.insert(make_pair(string(ln),string(fn)));
    }
    for(auto name:names)
        printf("%s %s\n", name.second.c_str(), name.first.c_str());
    return 0;
}
