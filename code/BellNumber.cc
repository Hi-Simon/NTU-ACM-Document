/*
 * Author: Simon
 * 功能: 模p意义下用记忆化搜索快速求第n个贝尔数
 * 描述: 贝尔数为集合的划分数
 */
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
#define int long long
#define maxn 1000005
#define INF 0x3f3f3f3f
int n,p;
int a[maxn],fac[maxn],inv[maxn];
int dfs(int n){
	if(a[n]) return a[n];
	if(n-p>=0&&n+1-p>=0){ /*a[n]=(a[n-p]+a[n+1-p])%p */
		return a[n]=(dfs(n-p)+dfs(n+1-p))%p;
	}
	int tmp=1,sum=0;
	for(int k=0;k<n;k++){ /*如果n小于p，则暴力求a[n]*/
		tmp=fac[n-1]%p*inv[k]%p*inv[n-1-k]%p;
		sum=(sum+tmp*dfs(k)%p)%p;
	}
	return a[n]=sum;
}
int fpow(int a,int b,int mod){
	int ans=1;a%=mod;
	while(b){
		if(b&1) ans=1LL*ans*a%mod;
		a=1LL*a*a%mod;
		b>>=1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;cin>>T;
	while(T--){
		cin>>n>>p;
		memset(fac,0,sizeof(fac));
		memset(inv,0,sizeof(inv));
		memset(a,0,sizeof(a));
		a[0]=1;a[1]=1; /*初始化前2个贝尔数 */
		int t=min(n,p-1); /*模p意义下，预处理t个阶乘即可 */
		fac[0]=1;for(int i=1;i<=t;i++) fac[i]=fac[i-1]*i%p;
		inv[t]=fpow(fac[t],p-2,p);
		for(int i=t;i>=1;i--){
			inv[i-1]=inv[i]*i%p;
		}
		cout<<dfs(n)<<endl;	
	}
	return 0;
}
