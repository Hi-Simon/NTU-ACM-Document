/*
 * Author: Simon
 * 复杂度：O(n)
 * 功能：已知多项式前n+1项，求第k项。
 * n次多项式的前缀和是n+1次多项式。
 */
int inv[maxn]/*阶乘逆元*/,bit[maxn]/*阶乘*/;
int ubit[maxn],subit[maxn];
void init(){
    bit[0] = 1;
    for (int i = 1; i < maxn; i++) bit[i] = 1LL * bit[i - 1] * i % mod;
    inv[maxn - 1] = fpow(bit[maxn - 1], mod - 2, mod);
    for (int i = maxn - 1; i >= 1; i--) inv[i - 1] = 1LL * inv[i] * i % mod;
}
int Lagrangian(int y[]/*值域*/,int n/*变量*/,int k/*待求y(k)*/ ){
	if(k<=n) return y[k];
	ubit[0]=subit[n]=1;
	for(int i=1;i<=n;i++){
		ubit[i]=1LL*ubit[i-1]*((k-i+1))%mod;/* ubit[i]=prod_{j\in [0,i-1]}(n-j) */
        subit[n-i]=1LL*subit[n-i+1]*((k-n+i-1))%mod; /*subit[i]=prod_{j\in[i+1,n]}(n-j) */
	}
	int ans=0;
	for(int i=0;i<=n;i++){
        int s1=1LL*y[i]%mod*ubit[i]%mod*subit[i]%mod;/*分子*/
        int s2=1LL*inv[i]%mod*inv[n-i]%mod; /*分母 */
        ans=(1LL*ans+1LL*((n-i)&1?-1:1)*s1%mod*s2%mod)%mod;
	}
	return (ans+mod)%mod;
}
/*
 * Author: Simon
 * 复杂度：O(n^2)
 * 功能：已知多项式任意n项，求第k项
 */
int Lagrangian(int y[]/*值域*/,int x[]/*变量*/,int k/*待求y_k*/,int mod){
    int ans=0;
    for(int i=1;i<=n;i++){
        int s1=y[i]%mod,s2=1;
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            (s1*=((k-x[j])%mod))%=mod;
            (s2*=((x[i]-x[j])%mod))%=mod;
        }
        (ans+=s1*fpow(s2,mod-2,mod)%mod)%=mod;
    } 
    return (ans+mod)%mod;
}