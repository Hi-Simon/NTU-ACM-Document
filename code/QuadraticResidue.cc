//求解X^2==n(mod p) 
ll P;
 
inline ll Pow(ll a,ll b){
	ll ret=1;
	for (;b;b>>=1,a=a*a%P)
		if (b&1)
			ret=ret*a%P;
	return ret;
}
 
inline ll legendre(ll a){
	return Pow(a,(P-1)>>1);
}
 
struct abcd{
	ll a,b,w; //a+b*sqrt(w)
	abcd(ll a=0,ll b=0,ll w=0):a(a),b(b),w(w) { }
	friend abcd operator *(abcd A,abcd B){
		return abcd((A.a*B.a%P+A.b*B.b%P*A.w%P)%P,(A.a*B.b%P+A.b*B.a%P)%P,A.w);
	}
};
 
inline abcd Pow(abcd a,int b){
	abcd ret=abcd(1,0,a.w);
	for (;b;b>>=1,a=a*a)
		if (b&1)
			ret=ret*a;
	return ret;
}
 
inline ll Solve(ll n,ll p){
	P=p;
	if (P==2) return 1;
	if (legendre(n)==P-1) return -1;
	ll a,w;
	while (1){
		a=rand()%P;
		w=((a*a-n)%P+P)%P;
		if (legendre(w)==P-1) break;
	}
	return Pow(abcd(a,1,w),(P+1)>>1).a;
}