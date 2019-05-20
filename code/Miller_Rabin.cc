using ll = long long;

ll prime[5] = {2, 3, 5, 233, 331};

ll pow_mod(ll a, ll n, ll mod) {
	ll ret = 1;
	while (n) {
		if (n&1) ret = ret * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return ret;
}

int isPrime(ll n) {
	if (n < 2 || (n != 2 && !(n&1))) return 0;
	ll s = n - 1;
	while (!(s&1)) s >>= 1;
	for (int i = 0; i < 5; ++i) {
		if (n == prime[i]) return 1;
		ll t = s, m = pow_mod(prime[i], s, n);
		while (t != n-1 && m != 1 && m != n-1) {
			m = m * m % n;
			t <<= 1;
		}
		if (m != n-1 && !(t&1)) return 0;
	}
	return 1;
}