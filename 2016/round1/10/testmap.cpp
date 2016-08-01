#include <cstdio>
#include <map>

using namespace std;

int main(void)
{
  map<char *, int> t;
  char tst[] = "test";

  t[tst] = 1;
  printf("%d\n", t[tst]);
  t.clear();
  printf("%d\n", t[tst]);

  return 0;
}
