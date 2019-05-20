/*
MST�㷨(Kruskal)��
e�����¼ÿ���ߣ��±�1~n��pre��¼���鼯���ڵ㣬lef��¼ʣ��δ����������ansΪ���·��
ע��Kruskal�㷨������ϡ��ͼ
*/

struct edge {
	int s, t, w;	//��s��t��Ȩֵw
	edge() {}
	edge(int s, int t, int w) :s(s), t(t), w(w) {}
}e[maxn];

int pre[maxn];

int find(int x) {
	int r = x, i = x, j;
	while (pre[r] != r)
		r = pre[r];
	while (i != r) {	//״̬ѹ��
		j = pre[i];
		pre[i] = r;
		i = j;
	}
	return r;
}

int cmp(edge e1, edge e2) {
	return e1.w < e2.w;
}

int kruskal(int n, int m) {	//nΪ������mΪ����
	int lef = m - 1, ans = 0;
	for (int i = 1; i <= m; i++)pre[i] = i;
	sort(e + 1, e + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		int fs = find(e[i].s), ft = find(e[i].t);
		if (fs != ft) {
			pre[fs] = ft;
			ans += e[i].w;
			lef--;
		}
		if (!lef)break;
	}
	if (lef)ans = 0;	//ͼ����ͨ
	return ans;
}