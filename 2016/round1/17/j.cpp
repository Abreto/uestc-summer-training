/* UESTC 2016 Summer Training #17 Div.2. Problem J, by Abreto, 20160728. */
#include <cstdio>
#include <string>
#include <map>
#include <vector>

using namespace std;

typedef struct _data
{
  int count;
  int price;
}data, *p_data;

vector<string> phones;
map<string, vector<string> > buyers;
map<string, data> t;
string phonename;
int maxnusers = 0;
int minprice = 0;

int handled(string pname)
{
  int i = 0;
  for(i = 0;i < phones.size();++i)
    if( phones[i] == pname )
      return 1;
  return 0;
}

int main(void)
{
  int i = 0;
  char cname[32] = "";
  char phone[32] = "";
  int p = 0;

  for(i = 0;i < 6;++i)
  {
    string name, phon;

    scanf("%s\n", cname);
    scanf("%s\n", phone);
    scanf("%d\n", &p);

    name = cname;
    phon = phone;

    if( 0 == handled(phon) )
    {
      phones.push_back(phon);
      buyers[phon].push_back(name);
      t[phon].count = 1;
      t[phon].price = p;
    }
    else
    {
      int j = 0;
      int ifhavebough = 0;
      /* if he have bought */
      for(j = 0;j < buyers[phon].size();++j)
        if( (buyers[phon])[i] == name )
        {
          ifhavebough = 1;
          break;
        }
      if( 0 == ifhavebough )
      {
        buyers[phon].push_back(name);
        ((t[phon]).count)++;
      }
      if( p < t[phon].price )
        t[phon].price = p;
    }
  }

  phonename = phones[0];
  maxnusers = t[phonename].count;
  minprice = t[phonename].price;
  for(i = 1;i < phones.size();++i)
  {
    if( t[phones[i]].count > maxnusers)
    {
      phonename = phones[i];
      maxnusers = t[phonename].count;
      minprice = t[phonename].price;
    }
    else if( t[phones[i]].count == maxnusers && t[phones[i]].price < minprice )
    {
      phonename = phones[i];
      minprice = t[phonename].price;
    }
  }

  printf("%s\n", phonename.c_str());
  return 0;
}
