/*
 * Author: Simon
 * 复杂度: O(log(n))
 * 功能: 快速幂
 */
int fpow(int a,int b,const int &mod){
	int ans=1;a%=mod;
	while(b){
		if(b&1) ans=(1LL*ans*a)%mod;
		a=(1LL*a*a)%mod;
		b>>=1;
	}
	return ans;
}