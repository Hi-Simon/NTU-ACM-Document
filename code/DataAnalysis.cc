/*
 * Author: Simon
 * 功能: 基础大数运算，结构体排序，减法
 */
class Bignum{
public:
	static const maxn=9999;
	static const int maxsize=10000;
	static const int dlen=4;
	int a[maxsize],len;
	Bignum(){len=1;memset(a,0,sizeof(a));};
	Bignum(const int);
	Bignum(const Bignum&);
	Bignum &operator =(const Bignum&);

	Bignum operator -(const Bignum &)const;
	bool operator>(const Bignum&T)const;
	bool operator>(const int &t)const;
	friend istream&operator >>(istream &in,Bignum &b){
		char ch[maxsize*4];
		int i=-1;
		in>>ch;
		int l=strlen(ch);
		int count=0,sum=0;
		for(int i=l-1;i>=0;){
			sum=0;
			int t=1;
			for(int j=0;j<4&&i>=0;j++,i--,t*=10){
				sum+=(ch[i]-'0')*t;
			}
			b.a[count]=sum;
			count++;
		}
		b.len=count++;
		return in;
	}
	friend ostream& operator <<(ostream& out,Bignum &b){
		int i;
		out<<b.a[b.len-1];
		for(int i=b.len-2;i>=0;i--){
			out.width(dlen);
			out.fill('0');
			out<<b.a[i];
		}
		return out;
	}
};
Bignum::Bignum(const int b){
	int c,d=b;
	len=0;memset(a,0,sizeof(a));
	while(d>maxn){
		c=d-(d/(maxn+1))*(maxn+1);
		d=d/(maxn+1);
		a[len++]=c;
	}
	a[len++]=d;
}
Bignum::Bignum(const Bignum&T):len(T.len){
	int i;memset(a,0,sizeof(a));
	for(int i=0;i<len;i++) a[i]=T.a[i];
}
Bignum &Bignum::operator=(const Bignum&n){
	int i;
	len=n.len;
	memset(a,0,sizeof(a));
	for(int i=0;i<len;i++) a[i]=n.a[i];
	return *this;
}
Bignum Bignum::operator-(const Bignum&T)const{
	int i,j,big; bool flag;
	Bignum t1,t2;
	if(*this>T){
		t1=*this;t2=T;
		flag=0;
	} else{
		t1=T;t2=*this;
		flag=1;
	}
	big=t1.len;
	for(int i=0;i<big;i++){
		if(t1.a[i]<t2.a[i]){
			j=i+1;
			while(t1.a[j]==0) j++;
			t1.a[j--]--;
			while(j>i) t1.a[j--]+=maxn;
			t1.a[i]+=maxn+1-t2.a[i];
		}
		else t1.a[i]-=t2.a[i];
	}
	t1.len=big;
	while(t1.a[t1.len-1]==0&&t1.len>1){
		t1.len--;big--;
	}
	if(flag) t1.a[big-1]=0-t1.a[big-1];
	return t1;
}
bool Bignum::operator>(const Bignum&T)const{
	int ln;
	if(len>T.len) return 1;
	else if(len==T.len){
		ln=len-1;
		while(a[ln]==T.a[ln]&&ln>=0) ln--;
		return ln>=0&&a[ln]>T.a[ln];
	}else return 0;
}
bool Bignum::operator >(const int &t)const{
	Bignum b(t);
	return *this>b;
}
struct node{
	string name;
	Bignum val;
	bool operator <(const node&a){
		return val>a.val;
	}
}a[1005];
vector<string>ans;
signed main(){
	int n;Bignum m;cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].name>>a[i].val;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(!(a[i].val>m)){ /*只重载了>运算符*/
			ans.push_back(a[i].name);
			m=m-a[i].val;
		}
	}
	if(m>0) cout<<"0"<<endl;
	else{
		cout<<ans.size()<<endl;
		for(auto v:ans) cout<<v<<endl;
	}
	return 0;
}
