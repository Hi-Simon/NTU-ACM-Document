/*
 * Author: Simon
 * 复杂度: O(n^{3/4}/logn)
 * 功能: 解决一类积形函数前缀和问题
 * 适用条件: 在质数处表达式为多项式，在质数的高次幂处可以快速求值
 */
#include<bits/stdc++.h>
using namespace std;
typedef int Int;
#define int long long
#define INF 0x3f3f3f3f
#define maxn 1000005
const int mod=1e9+7;
int prime[maxn],cnt=0,w[maxn],g[maxn],h[maxn],m=0;
int id1[maxn],id2[maxn],Sqr,sp[maxn];
bool vis[maxn]={1,1};
void Euler(int n){
    for(int i=2;i<=n;i++){
        if(!vis[i]) prime[++cnt]=i,sp[cnt]=sp[cnt-1]+i;
        for(int j=1;j<=cnt&&i*prime[j]<=n;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0) break;
        }
    }
}
int getG(int p){
    return p;
}
int getH(int p){
    return 1;
}
int getSigmaG(int p){ /*素数和 */
    return sp[p];
}
int getSigmaH(int p){
    return p;
}
int getF(int p,int e){ 
    return (p^e);
}
int fpow(int a,int b,int mod){
    int ans=1;a%=mod;
    while(b){
        if(b&1) (ans*=a)%=mod;
        (a*=a)%=mod;
        b>>=1;
    }
    return ans;
}
int S(int x,int y,int n){
    if (x<=1||prime[y]>x) return 0;
    int k=(x<=Sqr)?id1[x]:id2[n/x];
    int res=((1LL*g[k]-h[k])-(getSigmaG(y-1)-getSigmaH(y-1)))%mod;/*g(n,|P|)-sigma(f(P_i)) */
    res=(res+mod)%mod;
    if (y==1) res+=2; //特判。
    for (int i=y;i<=cnt&&1LL*prime[i]*prime[i]<=x;++i){
        int p1=prime[i],p2=1LL*prime[i]*prime[i];
        for (int e=1;p2<=x;++e,p1=p2,p2*=prime[i])
            (res+=(1LL*S(x/p1,i+1,n)*getF(prime[i],e)%mod+getF(prime[i],(e+1)))%mod)%=mod;
    }
    return res;
}
Int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;cin>>n;
    Sqr=sqrt(n);Euler(Sqr);
    for(int i=1,j;i<=n;i=j+1){ /*f(i)=g(i)-h(i) */
        j=n/(n/i);
        w[++m]=n/i; /*预处理离散化xk=n/i */
        h[m]=(w[m]-1)%mod; /*h(m,0)即h函数的前缀和减去h(1) */
        g[m]=((w[m]+1)%mod*w[m]%mod*fpow(2,mod-2,mod)%mod-1+mod)%mod; /*g(m,0)即g函数的前缀和减去g(1)*/
        w[m]<=Sqr?id1[w[m]]=m:id2[n/w[m]]=m;
    }
    for(int j=1;j<=cnt;j++){
        for(int i=1;i<=m&&prime[j]*prime[j]<=w[i];i++){
            int k=w[i]/prime[j]<=Sqr?id1[w[i]/prime[j]]:id2[n/(w[i]/prime[j])];
            (g[i]-=getG(prime[j])%mod*(g[k]-getSigmaG(j-1))%mod+mod)%=mod;/*根据转移方程即g(i,j)-=f(P_j)·g(n/P_j,j-1)-sigma(f(P_i)) */
            (h[i]-=getH(prime[j])%mod*(h[k]-getSigmaH(j-1))%mod+mod)%=mod; /*h函数转移同上 */
        }
    }
    cout<<((S(n,1,n)+1)%mod+mod)%mod<<endl;
    cin.get(),cin.get();
    return 0;
}