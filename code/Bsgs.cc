//Author: Simon 
#include <algorithm>
#include <cmath>
#include <cstring>
using ll = long long;
const int maxn = 1000005;
const ll mod = 611977;

struct HashMap {
	ll head[mod+5], key[maxn], value[maxn], nxt[maxn], tol;
	inline void clear() {
		tol=0;
		memset(head,-1,sizeof(head));
	}
	HashMap() {
		clear();
	}
	inline void insert(ll k,ll v) {
		ll idx = k % mod;
		for(ll i = head[idx]; ~i; i = nxt[i]) {
			if(key[i] == k) {
				value[i] = std::min(value[i], v);
				return ;
			}
		}
		key[tol] = k; 
		value[tol] = v; 
		nxt[tol] = head[idx]; 
		head[idx] = tol++;
	}
	inline ll operator [](const ll &k) const {
		ll idx = k % mod;
		for(ll i=head[idx]; ~i; i=nxt[i]) {
			if(key[i]==k) return value[i];
		}
		return -1;
	}
}mp;

inline ll fpow(ll a, ll b, ll mod) {
	a %= mod;
	ll ans = 1;
	while (b) {
		if(b&1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}
inline ll exgcd(ll a,ll b,ll &x,ll &y) {
	if (b==0) {
		x=1, y=0;
		return a;
	}
	ll ans = exgcd(b, a%b, y, x);
	y -= a/b*x;
	return ans;
}

inline ll Bsgs(ll a,ll b,ll mod) {
	a %= mod, b %= mod; mp.clear();
	if (b==1) return 0;
	if (a == 0) return b == 0 ? 1 : -1;
	ll m = ceil(sqrt(mod)), inv, y;
	exgcd(fpow(a, m, mod), mod, inv, y);
	inv = (inv % mod + mod) % mod;
	mp.insert(1, 1);
	for(ll i=1, e=1; i<m; i++) {
		e = e * a % mod;
		if(mp[e] == -1) mp.insert(e, i+1);
	}
	for(ll i = 0; i <= m; i++) {
		if(mp[b] != -1) {
			ll ans = mp[b]-1;
			return ans + i * m;
		}
		b = b * inv % mod;
	}
	return -1;
}

inline ll gcd(ll a, ll b) {
	return b==0 ? a : gcd(b, a%b);
}
inline int exBsgs(int a, int b, int p) {//扩展BSGS, 处理a，mod不互质的情况
    if(b == 1) return 0;
    int tb = b, tmp = 1;
    for(int g = gcd(a, p),k=1; g != 1; g = gcd(a, p),k++) {
        if(tb % g) return -1; //保证g为a,b,p的最大公约数
        tb /= g; p /= g; tmp = tmp * a / g % p;
        if(tmp == tb) return k;
    }
    return Bsgs(a, b, p);
}