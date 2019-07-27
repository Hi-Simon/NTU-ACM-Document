std::ostream& operator<<(std::ostream& os, __int128 T) {
	if (T<0) os<<"-";if (T>=10 ) os<<T/10;if (T<=-10) os<<(-(T/10));
	return os<<( (int) (T%10) >0 ? (int) (T%10) : -(int) (T%10) ) ;
}

void scan(__int128 &x) {
	x = 0;
	int f = 1;
	char ch;
	if((ch = getchar()) == '-') f = -f;
	else x = x*10 + ch-'0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = x*10 + ch-'0';
	x *= f;
}

void print(__int128 x) {
	if(x < 0) {
		x = -x;
		putchar('-');
	}
	if(x > 9) print(x/10);
	putchar(x%10 + '0');
}
// by Simon
struct Istream {
	template <class T>
	Istream &operator >>(T &x) {
		static char ch;static bool neg;
		for(ch=neg=0;ch<'0' || '9'<ch;neg|=ch=='-',ch=getchar());
		for(x=0;'0'<=ch && ch<='9';(x*=10)+=ch-'0',ch=getchar());
		x=neg?-x:x;
		return *this;
	}
}fin;

struct Ostream {
	template <class T>
	Ostream &operator <<(T x) {
		x<0 && (putchar('-'),x=-x);
		static char stack[233];static int top;
		for(top=0;x;stack[++top]=x%10+'0',x/=10);
		for(top==0 && (stack[top=1]='0');top;putchar(stack[top--]));
		return *this;
	}

	Ostream &operator <<(char ch) {
		putchar(ch);
		return *this;
	}
}fout;