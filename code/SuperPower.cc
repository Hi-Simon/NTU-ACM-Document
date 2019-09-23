/*
 * Author: Simon 
 * 功能: 求a^a^a^a^...^a mod m,总共b个
 * 复杂度: O(log(m))
 */
#include<bits/stdc++.h>
using namespace std;
typedef int Int;
#define int long long
#define INF 0x3f3f3f3f
#define maxn 1000005
int Phi(int x) {
    int ans = x;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            ans = ans / i * (i - 1);
            while (x % i == 0) x /= i;
        }
    }
    if (x != 1) ans = ans / x * (x - 1);
    return ans;
}
int fpow(int a,int b,int mod){
    a%=mod;int ans=1;
    while(b){
        if(b&1) (ans*=a)%=mod;
        (a*=a)%=mod;
        b>>=1;
    }
    return ans%mod;
}
int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}
/*判断a^b mod p 中b是否小于p */
bool check(int a,int b,int p){
    int ans=1;
    if(a>=p) return 0;
    for(int i=1;i<=b;i++){
        if(ans>=20) return 0;/*p最大1e6,所以ans>=20则肯定大于p */
        ans=fpow(a,ans,1e18);
        if(ans>=p) return 0;
    }
    return 1;
}
/*递归欧拉降幂 */
int f(int a,int b,int m){
    if(m==1) return 0;
    if(b<=1) return fpow(a,b,m);
    int p=Phi(m);
    int t=f(a,b-1,p);/*f(a,b,m)=a^{f(a,b-1,p) mod 待定} mod m */
    int g=gcd(a,m);
    if(g==1/*gcd(a,m)=1 */||check(a,b-1,p)/*f(a,b-1,INF)<p */) return fpow(a,t,m); //扩展欧拉定理
    else/*f(a,b-1,INF)>=p */ return fpow(a,t+p,m);
}
Int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;cin>>T;
    while(T--){
        int a,b,m;cin>>a>>b>>m;
        /*f(a,b,m)=a^a^a^...^a mod m,总共b个a */
        cout<<f(a,b,m)%m<<endl;
    }
    return 0;
}