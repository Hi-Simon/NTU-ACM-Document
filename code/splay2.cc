// splay tree：仅伸展操作
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;

const int maxn = 100005;
struct Node;
Node* null;
struct Node {
	Node *ch[2], *fa;
	int size, rev, key;
	Node() { ch[0] = ch[1] = fa = null; rev = 0; }
	inline void push_up() {
		if (this == null)return;
		size = ch[0]->size + ch[1]->size + 1;
	}
	inline void setc(Node* p, int d) {
		ch[d] = p;
		p->fa = this;
	}
	inline bool d() {
		return fa->ch[1] == this;
	}
	void clear() {
		size = 1;
		ch[0] = ch[1] = fa = null;
		rev = 0;
	}
	void Update_Rev() {
		if (this == null)return;
		swap(ch[0], ch[1]);
		rev ^= 1;
	}
	inline void push_down() {
		if (this == null)return;
		if (rev) {
			ch[0]->Update_Rev();
			ch[1]->Update_Rev();
			rev = 0;
		}
	}
	inline bool isroot() {
		return fa == null || this != fa->ch[0] && this != fa->ch[1];
	}
};
Node pool[maxn], *tail;
Node *node[maxn], *root;

inline void rotate(Node* x) {
	Node *f = x->fa, *ff = x->fa->fa;
	f->push_down();
	x->push_down();
	int c = x->d(), cc = f->d();
	f->setc(x->ch[!c], c);
	x->setc(f, !c);
	if (ff->ch[cc] == f)ff->setc(x, cc);
	else x->fa = ff;
	f->push_up();
}

inline void splay(Node* &root, Node* x, Node* goal) {
	while (x->fa != goal) {
		if (x->fa->fa == goal) rotate(x);
		else {
			x->fa->fa->push_down();
			x->fa->push_down();
			x->push_down();
			bool f = x->fa->d();
			x->d() == f ? rotate(x->fa) : rotate(x);
			rotate(x);
		}
	}
	x->push_up();
	if (goal == null)root = x;
}

Node* get_kth(Node* r, int k) {
	Node* x = r;
	x->push_down();
	while (x->ch[0]->size + 1 != k) {
		if (k < x->ch[0]->size + 1)x = x->ch[0];
		else {
			k -= x->ch[0]->size + 1;
			x = x->ch[1];
		}
		x->push_down();
	}
	return x;
}

Node* get_next(Node* p) {
	p->push_down();
	p = p->ch[1];
	p->push_down();
	while (p->ch[0] != null) {
		p = p->ch[0];
		p->push_down();
	}
	return p;
}

void build(Node* &x, int l, int r, Node* fa) {
	if (l > r)return;
	int mid = (l + r) >> 1;
	x = tail++;
	x->clear();
	x->fa = fa;
	node[mid] = x;
	build(x->ch[0], l, mid - 1, x);
	build(x->ch[1], mid + 1, r, x);
	x->push_up();
}

void init(int n) {
	tail = pool;
	null = tail++;
	null->fa = null->ch[0] = null->ch[1] = null;
	null->size = 0; null->rev = 0;
	Node *p = tail++;
	p->clear();
	root = p;
	p = tail++;
	p->clear();
	root->setc(p, 1);
	build(root->ch[1]->ch[0], 1, n, root->ch[1]);
	root->ch[1]->push_up();
	root->push_up();
}

int a[maxn], b[maxn];
bool cmp(int i, int j) { return a[i] < a[j] || (a[i] == a[j] && i < j); }

int main() {
	int n;
	while (scanf("%d", &n), n) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			b[i] = i;
		}
		init(n);
		sort(b + 1, b + n + 1, cmp);
		for (int i = 1; i <= n; i++) {
			splay(root, node[b[i]], null);
			int sz = root->ch[0]->size;
			printf("%d", root->ch[0]->size);
			if (i == n) printf("\n");
			else printf(" ");
			splay(root, get_kth(root, i), null);
			splay(root, get_kth(root, sz + 2), root);
			root->ch[1]->ch[0]->Update_Rev();
		}
	}
	return 0;
}