typedef unsigned long long ull;
const ull base = 163;
char s[maxn];
ull hash[maxn];
 
void init() {
    p[0] = 1;
    hash[0] = 0;
    int n = strlen(s + 1);
   for(int i = 1; i <=100000; i ++)p[i] =p[i-1] * base;
   for(int i = 1; i <= n; i ++)hash[i] = hash[i - 1] * base + (s[i] - 'a');
}
 
ull get(int l, int r, ull g[]) {
    return g[r] - g[l - 1] * p[r - l + 1];
}

struct HASHMAP {
	int size;
	int head[maxh], next[maxn], f[maxn];	// maxh 为hash链表最大长度
	ull state[maxn];
	void init() {
		size = 0;
		memset(head, -1, sizeof(head));
	}
	int insert(ull val, int id) {
		int h = val % maxh;
		for (int i = head[h]; i != -1; i = next[i])
			if (val == state[i]) return f[i];
		f[size] = id;
		state[size] = val;
		next[size] = head[h];
		head[h] = size;
		return f[size++];
	}
};