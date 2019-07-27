const double pi = acos(-1.0); 
struct Complex { /*复数结构体*/
	double x, y; /*实部和虚部 x+yi*/
	Complex(double _x = 0.0, double _y = 0.0) { x = _x, y = _y; }
	Complex operator-(const Complex& b) const { return Complex(x - b.x, y - b.y); }
	Complex operator+(const Complex& b) const { return Complex(x + b.x, y + b.y); }
	Complex operator*(const Complex& b) const { return Complex(x * b.x - y * b.y, x * b.y + y * b.x); }
};
/*
 * 进行FFT和IFFT前的反转变换。
 * 位置i和 （i二进制反转后位置）互换
 * len必须取2的幂
 */
void change(Complex y[], int len) {
	for (int i = 1, j = len>>1; i < len - 1; i++) { /*i做正常的+1，j做反转类型的+1,始终保持i和j是反转的*/
		if (i < j) std::swap(y[i], y[j]); /*交换互为小标反转的元素，i<j保证交换一次*/
		int k = len >>1;
		while (j >= k) j -= k, k >>= 1;
		if (j < k) j += k;
	}
}

/*
 * 做FFT
 * len必须为2^k形式，且不小于最高次幂。
 * on==1时是DFT，on==-1时是IDFT
 * DFT是将多项式系数表达转化为点值表达
 * 复杂度O(nlog(n))
 */
void fft(Complex y[], int len, int on) {
    change(y,len);	/*预处理分治区间长度为1时的位置顺序*/
	for (int mid = 1; mid < len; mid <<= 1){ /*当前分治区间的长度的一半*/
		Complex Wn(cos(pi / mid), on * sin(pi / mid)); /*mid*2等分点，单位根*/
		for (int R = mid << 1, j = 0; j < len; j += R){ /*R是区间长度，j表示第j/R+1个区间的起始下标*/
			Complex w(1, 0);						  /*幂*/
			for (int k = 0; k < mid; k++, w = w * Wn){ /*枚举左半部分*/
				Complex u = y[j + k], v = w * y[j + mid + k]; /*蝴蝶效应*/
				y[j + k] = u + v;
				y[j + mid + k] = u - v;
			}
		}
	}
    if(on==-1) for(int i=0;i<len;i++) y[i].x/=len;
}