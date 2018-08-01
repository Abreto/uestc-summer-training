#include <cstdio>
#include <iostream>
#include <string.h>
#include <string> 
#include <map>
#include <queue>
#include <deque>
#include <vector>
#include <set>
#include <algorithm>
#include <math.h>
#include <cmath>
#include <stack>
#include <iomanip>
#include <assert.h>
#define pb push_back 
#define mem0(a) memset(a,0,sizeof(a))
#define meminf(a) memset(a,0x3f,sizeof(a))
using namespace std;
typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int,int> pp;
const int maxn=100005,inf=0x3f3f3f3f;
const ll llinf=0x3f3f3f3f3f3f3f3f;
const ld pi=acos(-1.0L);
char s[maxn];

int main() {
    int cas;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%s",s+1);
        int len=strlen(s+1);
        for (int i=1;i<=len;i++) {
            if (s[i]=='?') {
                if (s[i-1]=='0'&&(s[i+1]>='0'&&s[i+1]<='9')) s[i]='+'; else
                if (s[i+1]=='0'&&(s[i-1]>='0'&&s[i-1]<='9')) s[i]='+'; else
                s[i]='1';
            }
        }
        if (s[1]=='+'||s[1]=='*'||s[len]=='+'||s[len]=='*') {
            printf("IMPOSSIBLE\n");continue;
        }
        int flag=1,last=-1;
        s[0]='+';
        for (int i=1;i<len;i++) {
            if (s[i]=='+'||s[i]=='*') last=-1; else if (s[i]!='0') last=i;
            if (s[i+1]>='0'&&s[i+1]<='9'&&s[i]=='0'&&last==-1) {
                flag=0;break;
            }
            if ((s[i]=='+'||s[i]=='*')&&(s[i+1]=='+'||s[i+1]=='*')) {
                flag=0;break;
            }
        }
        if (flag==0) {
            printf("IMPOSSIBLE\n");
        } else {
            printf("%s\n",s+1);
        }
    }
    return 0;
}