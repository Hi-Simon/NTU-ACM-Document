LL Inv(LL a, LL n){
	return PowMod(a, EulerPhi(n) - 1, n); 
	//return PowMod(a,n−2,n); //n为素数
}

int Inv(int a, int n) {
	int d, x, y;
	d = extended_euclid(a, n, x, y);
	if(d == 1)  return (x%n + n) % n;
	else     return -1; // no solution
}
// by Simon
int inv[maxn];
int Inv(int n,int p){ //线性求1~n的逆元
	inv[1] = 1;
	for (int i = 2; i <= n; ++i) inv[i] = (long long)(p - p / i) * inv[p % i] % p;
}
//by Simon
int a[maxn]/*n个数 */,s[maxn]/*前缀积 */,inv[maxn]/*第i个数的逆元 */; 
int Inv(int n,int p){ //线性求任意n个数的逆元
	s[0] = 1;
	for (int i = 1; i <= n; ++i) s[i] = s[i - 1] * a[i] % p; //前缀积
	sv[n] = fpow(s[n], p - 2);		// 当然这里也可以用 exgcd 来求逆元,视个人喜好而定.
	for (int i = n; i >= 1; --i) sv[i - 1] = sv[i] * a[i] % p; //前缀积的逆元
	for (int i = 1; i <= n; ++i) inv[i] = sv[i] * s[i - 1] % p;
}