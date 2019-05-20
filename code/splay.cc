// splay tree. HDU 3726：插入、删除、合并

const int MAXN = 20010;
struct Node;
Node* null;
struct Node {
	Node *ch[2], *fa;//指向儿子和父亲结点
	int size, key;
	Node() {
		ch[0] = ch[1] = fa = null;
	}
	inline void setc(Node* p, int d) {
		ch[d] = p;
		p->fa = this;
	}
	inline bool d() {
		return fa->ch[1] == this;
	}
	void push_up() {
		size = ch[0]->size + ch[1]->size + 1;
	}
	void clear() {
		size = 1;
		ch[0] = ch[1] = fa = null;
	}
	inline bool isroot() {
		return fa == null || this != fa->ch[0] && this != fa->ch[1];
	}
};

inline void rotate(Node* x) {
	Node *f = x->fa, *ff = x->fa->fa;
	int c = x->d(), cc = f->d();
	f->setc(x->ch[!c], c);
	x->setc(f, !c);
	if (ff->ch[cc] == f)ff->setc(x, cc);
	else x->fa = ff;
	f->push_up();
}

inline void splay(Node* &root, Node* x, Node* goal) {
	while (x->fa != goal) {
		if (x->fa->fa == goal)rotate(x);
		else {
			bool f = x->fa->d();
			x->d() == f ? rotate(x->fa) : rotate(x);
			rotate(x);
		}
	}
	x->push_up();
	if (goal == null)root = x;
}

//找到 r 子树里面的第 k 个
Node* get_kth(Node* r, int k) {
	Node* x = r;
	while (x->ch[0]->size + 1 != k) {
		if (k < x->ch[0]->size + 1)x = x->ch[0];
		else {
			k -= x->ch[0]->size + 1;
			x = x->ch[1];
		}
	}
	return x;
}


void erase(Node* &root, Node* x) {
	splay(root, x, null);
	Node* t = root;
	if (t->ch[1] != null) {
		root = t->ch[1];
		splay(root, get_kth(root, 1), null);
		root->setc(t->ch[0], 0);
	}
	else {
		root = root->ch[0];
	}
	root->fa = null;
	if (root != null)root->push_up();
}

void insert(Node* &root, Node* x) {
	if (root == null) {
		root = x;
		return;
	}
	Node* now = root;
	Node* pre = root->fa;
	while (now != null) {
		pre = now;
		now = now->ch[x->key >= now->key];
	}
	x->clear();
	pre->setc(x, x->key >= pre->key);
	splay(root, x, null);
}

void merge(Node* &A, Node* B) {
	if (A->size <= B->size)swap(A, B);
	queue<Node*>Q;
	Q.push(B);
	while (!Q.empty()) {
		Node* fr = Q.front();
		Q.pop();
		if (fr->ch[0] != null)Q.push(fr->ch[0]);
		if (fr->ch[1] != null)Q.push(fr->ch[1]);
		fr->clear();
		insert(A, fr);
	}
}

Node pool[MAXN], *tail;

struct Edge {
	int u, v;
}edge[60010];
int a[MAXN];
bool del[60010];
struct QUERY {
	char op[10];
	int u, v;
}query[500010];
int y[500010];

Node* node[MAXN];
Node* root[MAXN];
int F[MAXN];
int find(int x) {
	if (F[x] == -1)return x;
	return F[x] = find(F[x]);
}

void debug(Node *root) {
	if (root == null)return;
	debug(root->ch[0]);
	printf("size: %d, key = %d\n", root->size, root->key);
	debug(root->ch[1]);
}

int main()
{
	int n, m;
	int iCase = 0;
	while (scanf("%d%d", &n, &m) == 2) {
		if (n == 0 && m == 0)break;
		iCase++;
		memset(F, -1, sizeof(F));
		tail = pool;
		null = tail++;
		null->size = 0; null->ch[0] = null->ch[1] = null->fa = null;
		null->key = 0;
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &edge[i].u, &edge[i].v);
			del[i] = false;
		}
		int Q = 0;
		while (1) {
			scanf("%s", &query[Q].op);
			if (query[Q].op[0] == 'E')break;
			if (query[Q].op[0] == 'D') {
				scanf("%d", &query[Q].u);
				query[Q].u--;
				del[query[Q].u] = true;
			}
			else if (query[Q].op[0] == 'Q') {
				scanf("%d%d", &query[Q].u, &query[Q].v);
			}
			else {
				scanf("%d%d", &query[Q].u, &query[Q].v);
				y[Q] = a[query[Q].u];
				a[query[Q].u] = query[Q].v;
			}
			Q++;
		}
		for (int i = 1; i <= n; i++) {
			node[i] = tail++;
			node[i]->clear();
			node[i]->key = a[i];
			root[i] = node[i];
		}
		for (int i = 0; i < m; i++)
			if (!del[i]) {
				int u = edge[i].u;
				int v = edge[i].v;
				int t1 = find(u);
				int t2 = find(v);
				if (t1 == t2)continue;
				F[t2] = t1;
				merge(root[t1], root[t2]);
			}
		vector<int>ans;
		for (int i = Q - 1; i >= 0; i--) {
			if (query[i].op[0] == 'D') {
				int u = edge[query[i].u].u;
				int v = edge[query[i].u].v;
				int t1 = find(u);
				int t2 = find(v);
				if (t1 == t2)continue;
				F[t2] = t1;
				merge(root[t1], root[t2]);
			}
			else if (query[i].op[0] == 'Q') {
				int u = query[i].u;
				int k = query[i].v;
				u = find(u);
				if (k <= 0 || k > root[u]->size) {
					ans.push_back(0);
				}
				else {
					k = root[u]->size - k + 1;
					Node* p = get_kth(root[u], k);
					ans.push_back(p->key);
				}
			}
			else {
				int u = query[i].u;
				int t1 = find(u);
				Node* p = node[u];
				erase(root[t1], p);
				p->clear();
				p->key = y[i];
				a[u] = y[i];
				insert(root[t1], p);
			}
		}
		double ret = 0;
		int sz = ans.size();
		for (int i = 0; i < sz; i++)ret += ans[i];
		if (sz)ret /= sz;
		printf("Case␣%d:␣%.6lf\n", iCase, ret);
	}
	return 0;
}