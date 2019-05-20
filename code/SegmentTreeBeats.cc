//使用方法
//Build(1, 1, n) 建树
//读入ql,  qr,  qt 调用函数 XXX(1, 1, n) 
using ll = long long;

const int N = "Edit";
const int M = N<<2;

int mx[M], sx[M], cx[M], mn[M], sn[M], cn[M]; 
ll sum[M]; 
int ta[M];

inline void update(int x){
	int l = x<<1, r = x<<1|1;
	sum[x] = sum[l] + sum[r];
	if (mx[l] == mx[r]) {
		mx[x] = mx[l], cx[x] = cx[l] + cx[r], sx[x] = std::max(sx[l], sx[r]);
	} else { // r>l
		if (mx[l] > mx[r]) std::swap(l,r);
		mx[x] = mx[r]; 
		cx[x] = cx[r];
		sx[x] = std::max(sx[r], mx[l]);
	}
	if (mn[l] == mn[r]) {
		mn[x] = mn[l], cn[x] = cn[l] + cn[r], sn[x] = std::min(sn[l], sn[r]);
	} else { // r<l
		if (mn[l] < mn[r]) std::swap(l,r);
		mn[x] = mn[r]; 
		cn[x] = cn[r];
		sn[x] = std::min(sn[r], mn[l]);
	}
}

//建树
inline void Build(int x, int l, int r){
	if (l == r) {
		int a;
		std::cin >> a;
		sum[x] = mx[x] = mn[x] = a; cx[x] = cn[x] = 1; 
		sx[x] = -(1<<30); sn[x]=1<<30;  ta[x]=0;
		return;
	}
	int mid=(l+r)>>1; 
	Build(x<<1,l,mid); 
	Build(x<<1|1,mid+1,r);
	update(x);
}

inline void _add(int x, int l, int r, int t) {
	sum[x] += (ll)(r-l+1)*t;
	mn[x]+=t; sn[x]+=t; mx[x]+=t; sx[x]+=t;
	ta[x]+=t;
}

inline void _min(int x,int l,int r,int t){
	sum[x] -= (ll)cx[x]*(mx[x]-t);
	mx[x]=t; mn[x]=std::min(mn[x],t);
	if (mn[x] == mx[x]) {
		sum[x] = (ll)(r-l+1)*t; cx[x] = cn[x] = r-l+1; sx[x] = -(1<<30); sn[x] = 1<<30;
	} else {
		sn[x]=std::min(sn[x],t);
	}
}

inline void _max(int x,int l,int r,int t){
	sum[x] += (ll)cn[x]*(t-mn[x]);
	mn[x] = t; mx[x] = std::max(mx[x], t);
	if (mn[x] == mx[x]) {
		sum[x]=(ll)(r-l+1)*t; cx[x] = cn[x] = r-l+1; sx[x] = -(1<<30); sn[x] = 1<<30;
	} else {
		sx[x] = std::max(sx[x], t);
	}
}

inline void push(int x, int l, int r){
	int mid = (l+r)>>1;
	if (ta[x]) {
		_add(x<<1, l, mid, ta[x]);
		_add(x<<1|1, mid+1, r, ta[x]);
		ta[x] = 0;
	}
	if (mx[x<<1]>mx[x] && sx[x<<1]<mx[x]) _min(x<<1, l, mid, mx[x]);
	if (mx[x<<1|1]>mx[x] && sx[x<<1|1]<mx[x]) _min(x<<1|1, mid+1, r, mx[x]);
	if (mn[x<<1]<mn[x] && sn[x<<1]>mn[x]) _max(x<<1, l, mid, mn[x]);
	if (mn[x<<1|1]<mn[x] && sn[x<<1|1]>mn[x]) _max(x<<1|1, mid+1, r, mn[x]);
}

int ql, qr, qt;
int n;

//把一个区间[L,R] 里小于x 的数变成x
inline void Mmax(int x, int l, int r){
	if (mn[x] >= qt) return;
	if (ql<=l && r<=qr && qt<sn[x]){
		_max(x, l, r, qt); return;
	}
	push(x, l, r); int mid = (l+r)>>1;
	if (ql<=mid) Mmax(x<<1, l, mid);
	if (qr>mid) Mmax(x<<1|1, mid+1, r);
	update(x);
}

//把一个区间[L,R] 里大于x 的数变成x 
inline void Mmin(int x,int l,int r) {
	if (mx[x]<=qt) return;
	if (ql<=l && r<=qr && qt>sx[x]) {
		_min(x,l,r,qt); return;
	}
	push(x,l,r); int mid=(l+r)>>1;
	if (ql<=mid) Mmin(x<<1, l, mid);
	if (qr>mid) Mmin(x<<1|1, mid+1, r);
	update(x);
}

//区间加值
inline void Add(int x, int l, int r) {
	if (ql<=l && r<=qr) {
		_add(x, l, r, qt); return;
	}
	push(x, l, r); int mid=(l+r)>>1;
	if (ql<=mid) Add(x<<1, l, mid);
	if (qr>mid) Add(x<<1|1, mid+1, r);
	update(x);
}

//区间最大值
inline int Max(int x, int l, int r) {
	if (ql<=l && r<=qr) return mx[x];
	push(x, l, r);
	int ret=-(1<<30); int mid=(l+r)>>1;
	if (ql<=mid) ret=std::max(ret, Max(x<<1, l, mid));
	if (qr>mid) ret=std::max(ret, Max(x<<1|1, mid+1, r));
	return ret;
}

//区间最小值
inline int Min(int x, int l, int r) {
	if (ql<=l && r<=qr)  return mn[x];
	push(x, l, r) ;
	int ret=1<<30; int mid=(l+r) >>1;
	if (ql<=mid) ret=std::min(ret, Min(x<<1, l, mid) );
	if (qr>mid)  ret=std::min(ret, Min(x<<1|1, mid+1, r) );
	return ret;
}

//区间求和
inline ll Sum(int x, int l, int r) {
	if (ql<=l && r<=qr)  return sum[x];
	push(x, l, r) ;
	ll ret=0; int mid=(l+r) >>1;
	if (ql<=mid) ret+=Sum(x<<1, l, mid) ;
	if (qr>mid)  ret+=Sum(x<<1|1, mid+1, r) ;
	return ret;
}
