//dp[i] = sigma(a[j] * dp[i-j]) (j < i);
const int maxn = "Edit";
int dp[maxn], a[maxn];
Complex x[maxn<<2], y[maxn<<2];
void solve(int L, int R){
	if(L == R) return ;
	int mid = (L + R) >> 1;
	solve(L, mid);
	int len = 1, len1 = R - L + 1;
	while(len <= len1) len <<= 1;
	for(int i = 0; i < len1; ++i) x[i] = Complex(a[i], 0);
	for(int i = len1; i <= len; ++i) x[i] = Complex(0, 0);
	for(int i = L; i <= mid; ++i)
		y[i-L] = Complex(dp[i], 0);
	for(int i = mid - L + 1; i <= len; ++i) y[i] = Complex(0, 0);
	fft(x, len, 1);
	fft(y, len, 1);
	for(int i = 0; i < len; ++i) x[i] = x[i] * y[i];
	fft(x, len, -1);
	for(int i = mid + 1; i <= R; ++i){
		dp[i] += x[i-L].x + 0.5;
	}
	solve(mid + 1, R);
}