//NTT 模板
#include <bits/stdc++.h>
#define LL long long

using namespace std;
typedef long long ll;
const int Max=5e5+100;
const ll Mod = 998244353;   // 模数
const ll SpMul = 3;  // 原根
ll qpow(ll a, ll k) {
    ll res = 1LL;
    while (k > 0) {
        if (k & 1)res = res * a % Mod;
        a = a * a % Mod;
        k >>= 1;
    }
    return res;
}

void Change(ll y[], int len) {
    for (int i = 1, j = len / 2; i < len - 1; i++) {
        if (i < j)swap(y[i], y[j]);
        int k = len / 2;
        while (j >= k) {
            j -= k;
            k /= 2;
        }
        if (j < k)j += k;
    }
}


void NTT(ll y[], int len, int on) {
    Change(y, len);
    for (int h = 2; h <= len; h <<= 1) {
        ll wn = qpow(SpMul, (Mod - 1) / h);
        if (on == -1)wn = qpow(wn, Mod - 2);
        for (int j = 0; j < len; j += h) {
            ll w = 1LL;
            for (int k = j; k < j + h / 2; k++) {
                ll u = y[k];
                ll t = w * y[k + h / 2] % Mod;
                y[k] = (u + t) % Mod;
                y[k + h / 2] = (u - t + Mod) % Mod;
                w = w * wn % Mod;
            }
        }
    }
    if (on == -1) {
        ll t = qpow(len, Mod - 2);
        for (int i = 0; i < len; i++)
            y[i] = y[i] * t % Mod;
    }
}
LL data1[Max], data2[Max];
char str1[Max], str2[Max];
int main() {
    while(~scanf("%s%s", str1, str2)){
        int len1=strlen(str1);
        int len2=strlen(str2);
        LL len=1;
        memset(data1, 0, sizeof(data1));
        memset(data2, 0, sizeof(data2));
        while(len<len1*2||len<len2*2)len<<=1;
        for(int a=0; a<len1; a++)data1[a]=str1[len1-a-1]-'0';
        for(int a=0; a<len2; a++)data2[a]=str2[len2-a-1]-'0';
        NTT(data1, len, 1);
        NTT(data2, len, 1);
        for(int a=0; a<len; a++)data1[a]=data1[a]*data2[a]%Mod;
        NTT(data1, len, -1);
        for(int a=0; a<len; a++){
            data1[a+1]+=data1[a]/10;data1[a]%=10;
        }
        while(data1[len]==0&&len>0)len--;
        for(int a=len; a>=0; a--)printf("%lld", data1[a]);
        printf("\n");
    }
    return 0;
}
