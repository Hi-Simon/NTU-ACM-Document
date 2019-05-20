//Author:marszed
/*
*离线区间处理问题。
*从区间[l,r]得到区间[l+1,r+1] [l-1,r-1]信息的转移复杂度为O(1)。
*siz为块大小。
*cnt为位于第几个块。
*modify()函数为转移函数。
*/

#include <iostream>
#include <algorithm>
#include <cmath>

const int maxn = 2e5 + 10;

int n, siz, q;
int a[maxn];

struct Node {
	int id, l, r, val, cnt;

	int operator< (const Node& b) {
		return cnt == b.cnt ? r < b.r : cnt < b.cnt;
	}
} nod[maxn];

void modify(int i, int flag) {

}

void mo() {
	std::cin >> n >> q;
	siz = sqrt(n);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= q; i++) {
		std::cin >> nod[i].l >> nod[i].r;
		nod[i].id = i;
		nod[i].cnt = nod[i].l / siz;
	}
	std::sort(nod + 1, nod + q + 1);
	int l = 0, r = 0;
	for (int i = 1; i <= q; i++) {
		while (l < nod[i].l - 1)	modify(++l, 1);
		while (l >= nod[i].l) 		modify(l--, 1);
		while (r < nod[i].r) 		modify(++r, 1);
		while (r > nod[i].r) 		modify(r--, 1);
		ans[nod[i].id] = Ans;
	}
}

int main() {}