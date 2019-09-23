int tree[maxn][26];
int sum[maxn];
int tot;
void Insert(char *str) {
	int len = strlen(str);
	int root = 0;
	for (int i = 0; i < len; i++) {
		int id = str[i] - 'a';
		if (!tree[root][id]) tree[root][id] = ++tot;
		root = tree[root][id];
		sum[root]++;
	}
}

int Find(char *str) {
	int len = strlen(str);
	int root = 0;
	for (int i = 0; i < len; i++) {
		int id = str[i] - 'a';
		if (!tree[root][id]) return 0;
		root = tree[root][id];
	}
	return sum[root];
}