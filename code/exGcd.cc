//如果GCD(a,b) = d, 则存在x, y, 使d =  ax +  by
// extended_euclid(a, b) = ax + by
int extended_euclid(int a, int b, int &x, int &y) {
	int d;
	if(b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	d = extended_euclid(b, a % b, y, x);
	y -= a / b * x;
	return d;
}