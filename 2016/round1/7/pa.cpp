/* UESTC 2016 Summer Training #7 Div.2. Problem A, by Abreto, 201607181307. */
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <string>

#define MAXN  128

using namespace std;

int n = 0;
map<string, vector<string> > addresses;
vector<string>  hashtable;
int n_groups = 0;
char line[MAXN] = {0};

char tolower(char ch)
{
  if(ch >= 'A' && ch <= 'Z')
    return ('a' + ch - 'A');
  else
    return ch;
}

void handle_address(void)
{
  int i = 0;
  int len = strlen(line);
  string origin;
  string login[3]; /* 0 for part before plus, 1 for part after plus(include '+'), 2 for domain */
  int state = 0;

  for(i = 0;i < len;++i)
  {
    origin.append(1, tolower(line[i]));

    if( state < 2 && '.' == line[i] )
      continue;
    else if( 0 == state && '+' == line[i] )
        state = 1;
    else if( '@' == line[i] )
    {
      state = 2;
      continue;
    }
    login[state].append(1, tolower(line[i]));
  }

  if( "bmail.com" == login[2] )
    origin = login[0] + "@" + login[2];

  if( addresses[origin].empty() )
    n_groups++;
  addresses[origin].push_back(string(line));
}

int main(void)
{
  int i = 0;

  scanf("%d\n", &n);
  for(i = 0;i < n;++i)
  {
    scanf("%s\n", line);
    handle_address();
  }

  printf("%d\n", n_groups);
  for(map<string, vector<string> >::iterator it=addresses.begin(); it != addresses.end();++it)
  {
    int i = 0;
    int k = it->second.size();
    printf("%d", k);
    for(i = 0;i < k;++i)
      printf(" %s", (it->second)[i].c_str());
    printf("\n");
  }
  return 0;
}
