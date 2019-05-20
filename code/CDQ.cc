//Author:marsed
/*
*将区间分成左右两部分 递归处理
一层递归计算当前左区间的修改操作对右区间的查询操作的影响
当flag为1代表修改操作 为0代表查询操作
*/
#include <algorithm>
#define mid (l + r)/2

const int maxn = "Edit";

struct Node {
	int id, x1,x2;
	int operator<(const Node &b) {   //按照参数的优先级排序
		return ;
	}
};

Node nod[maxn], tmp[maxn];

void cdq(int l, int r) {
	if (l == r) return;
	cdq(l, mid); cdq(mid + 1, r);
	int p = l, q = mid + 1, cnt = 0;
	while (p <= mid&&q <= r) {
		if (nod[p] < nod[q]) {
			if (nod[p].flag) ;    //左区间里的修改操作会对右区间的查询操作有影响 计算影响
			tmp[cnt++] = nod[p++];
		} else {
			if (!nod[q].flag) ;//计算右区间的查询操作的值
			tmp[cnt++] = nod[q++];
		}
	}
	while (p <= mid) tmp[cnt++] = nod[p++];
	while (q <= r) {
		if (!nod[q].flag) ;
		tmp[cnt++] = nod[q++];
	}
	for (int i = l; i <= r; i++)
		nod[i] = tmp[i - l];
}

int main()
{
	cdq(1, q);
	return 0;
}