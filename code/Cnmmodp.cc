LL C(const LL &n, const LL &m, const int &pr) {
	LL ans = 1;
	for (int i = 1; i <= m; i++) {
		LL a = (n - m + i) % pr;
		LL b = i % pr;
		ans = (ans * (a * Inv(b, pr) % pr) % pr) % pr;
	}
	return ans;
}
/*
 * Author: Simon
 * 功能: 求组合数
 * 复杂度: O(p+log(p))
 */
int bit[maxn]; //阶乘数组，对p取模，则只需初始化1~p的阶乘即可。
int C(const int n,const int m,const int p){
    if (n < m) return 0;
	return bit[n] * fpow(bit[m], p - 2, p) % p * fpow(bit[n - m], p - 2, p) % p; 
}