class Bignum {
public:
	static const int maxm = 9999; // MAXN 是一位中最大的数字,必须是99……的形式
	static const int maxsize = 100; // MAXSIZE 是大数的位数
	static const int dlen = 4; // DLEN 记录压几位
	int a[maxsize];    //可以控制大数的位数,存储的最大数字为maxm^maxsize
	int len;       //大数目前长度
	Bignum(){ len = 1;memset(a,0,sizeof(a)); }   //构造函数
	Bignum(const int);       //将一个int类型的变量转化为大数
	Bignum(const char*);     //将一个字符串类型的变量转化为大数
	Bignum(const Bignum &);  //拷贝构造函数
	Bignum &operator=(const Bignum &);   //重载赋值运算符，大数之间进行赋值运算

	Bignum operator+(const Bignum &) const;   //重载加法运算符，两个大数之间的相加运算
	Bignum operator-(const Bignum &) const;   //重载减法运算符，两个大数之间的相减运算
	Bignum operator*(const Bignum &) const;   //重载乘法运算符，两个大数之间的相乘运算
	Bignum operator/(const int    &) const;    //重载除法运算符，大数对一个整数进行相除运算

	Bignum operator^(const int  &) const;    //大数的n次方运算
	int    operator%(const int  &) const;    //大数对一个int类型的变量进行取模运算
	bool   operator>(const Bignum & T)const;   //大数和另一个大数的大小比较
	bool   operator>(const int & t)const;      //大数和一个int类型的变量的大小比较

	void print();       //输出大数

	friend istream&operator >>(istream&in, Bignum &b) {
		char ch[maxsize*4];
		int i = -1;
		in>>ch;
		int l=strlen(ch);
		int count=0,sum=0;
		for(i=l-1;i>=0;) {
			sum = 0;
			int t=1;
			for(int j=0;j<4&&i>=0;j++,i--,t*=10) {
				sum+=(ch[i]-'0')*t;
			}
			b.a[count]=sum;
			count++;
		}
		b.len =count++;
		return in;
	}
	friend ostream& operator<<(ostream& out,  Bignum& b) {  //重载输出运算符
		int i;
		out << b.a[b.len - 1];
		for(i = b.len - 2 ; i >= 0 ; i--) {
			out.width(dlen);
			out.fill('0');
			out << b.a[i];
		}
		return out;
	}

};

Bignum::Bignum(const int b) {    //将一个int类型的变量转化为大数
	int c,d = b;
	len = 0; memset(a,0,sizeof(a));
	while(d > maxm) {
		c = d - (d / (maxm + 1)) * (maxm + 1);
		d = d / (maxm + 1);
		a[len++] = c;
	}
	a[len++] = d;
}

Bignum::Bignum(const char*s) {    //将一个字符串类型的变量转化为大数
	int t,k,index,l,i;
	memset(a,0,sizeof(a));
	l=strlen(s); len=l/dlen;
	if(l%dlen) len++;
	index=0;
	for(i=l-1;i>=0;i-=dlen) {
		t=0; k=i-dlen+1;
		if(k<0) k=0;
		for(int j=k;j<=i;j++) t=t*10+s[j]-'0';
		a[index++]=t;
	}
}

Bignum::Bignum(const Bignum & T) : len(T.len) { //拷贝构造函数
	int i; memset(a,0,sizeof(a));
	for(i = 0 ; i < len ; i++) a[i] = T.a[i];
}

Bignum & Bignum::operator=(const Bignum & n) {  //重载赋值运算符，大数之间进行赋值运算
	len = n.len;int i;
	memset(a,0,sizeof(a));
	for(i = 0 ; i < len ; i++) a[i] = n.a[i];
	return *this;
}


Bignum Bignum::operator+(const Bignum & T) const {  //两个大数之间的相加运算
	Bignum t(*this);
	int i,big;      //位数
	big = T.len > len ? T.len : len;
	for(i = 0 ; i < big ; i++) {
		t.a[i] +=T.a[i];
		if(t.a[i] > maxm) {
			t.a[i + 1]++;
			t.a[i] -=maxm+1;
		}
	}
	if(t.a[big] != 0) t.len = big + 1;
	else t.len = big;
	return t;
}
Bignum Bignum::operator-(const Bignum & T) const {   //两个大数之间的相减运算
	int i,j,big; bool flag;
	Bignum t1,t2;
	if(*this>T) {
		t1=*this; t2=T;
		flag=0;
	} else {
		t1=T; t2=*this;
		flag=1;
	}
	big=t1.len;
	for(i = 0 ; i < big ; i++) {
		if(t1.a[i] < t2.a[i]) {
			j = i + 1;
			while(t1.a[j] == 0) j++;
			t1.a[j--]--;
			while(j > i) t1.a[j--] += maxm;
			t1.a[i] += maxm + 1 - t2.a[i];
		}
		else t1.a[i] -= t2.a[i];
	}
	t1.len = big;
	while(t1.a[t1.len - 1] == 0 && t1.len > 1) {
		t1.len--; big--;
	}
	if(flag) t1.a[big-1]=0-t1.a[big-1];
	return t1;
}

Bignum Bignum::operator*(const Bignum & T) const {  //两个大数之间的相乘运算
	Bignum ret;
	int i,j,up;
	int temp,temp1;
	for(i = 0 ; i < len ; i++) {
		up = 0;
		for(j = 0 ; j < T.len ; j++) {
			temp = a[i] * T.a[j] + ret.a[i + j] + up;
			if(temp > maxm) {
				temp1 = temp - temp / (maxm + 1) * (maxm + 1);
				up = temp / (maxm + 1);
				ret.a[i + j] = temp1;
			} else {
				up = 0;
				ret.a[i + j] = temp;
			}
		}
		if(up != 0) ret.a[i + j] = up;
	}
	ret.len = i + j;
	while(ret.a[ret.len - 1] == 0 && ret.len > 1) ret.len--;
	return ret;
}
Bignum Bignum::operator/(const int & b) const {  //大数对一个整数进行相除运算
	Bignum ret;
	int i,down = 0;
	for(i = len - 1 ; i >= 0 ; i--) {
		ret.a[i] = (a[i] + down * (maxm + 1)) / b;
		down = a[i] + down * (maxm + 1) - ret.a[i] * b;
	}
	ret.len = len;
	while(ret.a[ret.len - 1] == 0 && ret.len > 1) ret.len--;
	return ret;
}
int Bignum::operator %(const int & b) const {   //大数对一个int类型的变量进行取模运算
	int i,d=0;
	for (i = len-1; i>=0; i--) d = ((d * (maxm+1))% b + a[i])% b;
	return d;
}
Bignum Bignum::operator^(const int & n) const {   //大数的n次方运算
	Bignum t,ret(1);
	int i;
	if(n<0) exit(-1);
	if(n==0) return 1;
	if(n==1) return *this;
	int m=n;
	while(m>1) {
		t=*this;
		for( i=1;i<<1<=m;i<<=1) t=t*t;
		m-=i; ret=ret*t;
		if(m==1) ret=ret*(*this);
	}
	return ret;
}

bool Bignum::operator>(const Bignum & T) const {  //大数和另一个大数的大小比较
	int ln;
	if(len > T.len) return 1;
	else if(len == T.len) {
		ln = len - 1;
		while(a[ln] == T.a[ln] && ln >= 0) ln--;
		return ln >= 0 && a[ln] > T.a[ln];
	} else return 0;
}

bool Bignum::operator >(const int & t) const {  //大数和一个int类型的变量的大小比较
	Bignum b(t);
	return *this>b;
}

void Bignum::print() {    //输出大数
	int i;
	cout << a[len - 1];
	for(i = len - 2 ; i >= 0 ; i--) {
		cout.width(dlen);
		cout.fill('0');
		cout << a[i];
	}
	cout << endl;
}
