const int maxn = 10005;   //点的最大个数

int head[maxn], cnt=0;//head用来表示以i为起点的第一条边存储的位置，cnt读入边的计数器

struct Edge {
	int next; //同一起点的上一条边的储存位置
	int to; //第i条边的终点
	int w; //第i条边权重
};

Edge edge[maxn];

void addedge(int u,int v,int w) {
	edge[cnt].w = w;
	edge[cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt++;
}

void traverse() {
	for(int i=0; i<=n; i++) {
		for(int j=head[i]; j！=-1; j=edge[j].next) {
			std::cout << i << " " << head[i].to << " " << head[i].w << '\n';
		}
	}
}
