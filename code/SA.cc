//author: Menci
#include <algorithm>
#include <string>
#include <iostream>

const int maxn = 1000;

char s[maxn];
int n, ht[maxn], rk[maxn], sa[maxn];

inline void suffixArray() {
	static int set[maxn + 1], a[maxn + 1];
	std::copy(s, s + n, set + 1);
	std::sort(set + 1, set + n + 1);
	int *end = std::unique(set + 1, set + n + 1);
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(set + 1, end, s[i]) - set;

	static int fir[maxn + 1], sec[maxn + 1], tmp[maxn + 1], buc[maxn + 1];
	for (int i = 1; i <= n; i++) buc[a[i]]++;
	for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
	for (int i = 1; i <= n; i++) rk[i] = buc[a[i] - 1] + 1;

	for (int t = 1; t <= n; t *= 2) {
		for (int i = 1; i <= n; i++) fir[i] = rk[i];
		for (int i = 1; i <= n; i++) sec[i] = i + t > n ? 0 : rk[i + t];

		std::fill(buc, buc + n + 1, 0);
		for (int i = 1; i <= n; i++) buc[sec[i]]++;
		for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
		for (int i = 1; i <= n; i++) tmp[n - --buc[sec[i]]] = i;

		std::fill(buc, buc + n + 1, 0);
		for (int i = 1; i <= n; i++) buc[fir[i]]++;
		for (int i = 1; i <= n; i++) buc[i] += buc[i - 1];
		for (int j = 1, i; j <= n; j++) i = tmp[j], sa[buc[fir[i]]--] = i;

		bool unique = true;
		for (int j = 1, i, last = 0; j <= n; j++) {
			i = sa[j];
			if (!last) rk[i] = 1;
			else if (fir[i] == fir[last] && sec[i] == sec[last]) rk[i] = rk[last], unique = false;
			else rk[i] = rk[last] + 1;

			last = i;
		}

		if (unique) break;
	}

	for (int i = 1, k = 0; i <= n; i++) {
		if (rk[i] == 1) k = 0;
		else {
			if (k > 0) k--;
			int j = sa[rk[i] - 1];
			while (i + k <= n && j + k <= n && a[i + k] == a[j + k]) k++;
		}
		ht[rk[i]] = k;
	}
}

int main() {
	std::cin >> n >> s;
	suffixArray();
	for (int i = 1; i <= n; i++) {
		std::cout << sa[i] << " ";
	}
}