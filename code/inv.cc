LL Inv(LL a, LL n){
	return PowMod(a, EulerPhi(n) - 1, n); 
	//return PowMod(a,n−2,n); //n为素数
}

int Inv(int a, int n) {
	int d, x, y;
	d = extended_euclid(a, n, x, y);
	if(d == 1)  return (x%n + n) % n;
	else     return -1; // no solution
}