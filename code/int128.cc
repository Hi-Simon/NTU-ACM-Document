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