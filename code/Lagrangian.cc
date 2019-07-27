/*
Author: Simon
复杂度：O(n)
功能：已知多项式前n+1项，求第k项。
*/
int bit[maxn]/*预处理前n项阶乘*/;
int Lagrangian(int y[]/*值域*/,int n/*变量*/,int k/*待求y_k*/,int mod){
    if(k<=n) return y[k];
    int ubit[maxn]={k};/*预处理前n项反k阶乘即：(k-0)*(k-1)*...*(k-k)*/;
    for(int i=1;i<=n;i++) ubit[i]=ubit[i-1]*(k-i)%mod;
    int ans=0;
    for(int i=1;i<=n;i++){ /*拉格朗日插值多项式,y[0]=0*/
        int s1=y[i]*ubit[i-1]%mod*ubit[n]%mod*fpow(ubit[i],mod-2,mod)%mod; /*分子*/
        int s2=bit[i]*bit[n-i]%mod; /*分母*/
        (ans+=((n-i)&1?-1:1)*s1%mod*fpow(s2,mod-2,mod)%mod)%=mod;
    }
    return (ans+mod)%mod;
}
/*
Author: Simon
复杂度：O(n^2)
功能：已知多项式任意n项，求第k项
*/
int Lagrangian(int y[]/*值域*/,int x[]/*变量*/,int k/*待求y_k*/,int mod){
    int ans=0;
    for(int i=1;i<=n;i++){
        int s1=y[i]%mod,s2=1;
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            (s1*=((k-x[j])%mod+mod)%mod)%=mod;
            (s2*=((x[i]-x[j])%mod+mod)%mod)%=mod;
        }
        (ans+=s1*fpow(s2,mod-2,mod)%mod)%=mod;
    } 
    return ans;
}