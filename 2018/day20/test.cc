#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    string s, t;
    s.resize(100, 0);
    s[2] = 0;
    t = s;
    t[4] = 0;
    printf("%lu\n", t.size());
    return 0;
}
