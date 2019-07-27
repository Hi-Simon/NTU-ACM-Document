/*
某些计数问题或数论问题出于加长代码、增加难度、或者是一些其他不可告人的原因 给出的模数：不是质数！
但是对其质因数分解会发现它没有平方因子，也就是该模数是由一些不重复的质数相乘得到。
那么我们可以分别对这些模数进行计算，最后用 CRT 合并答案。
 */
LL Crt(LL *div, LL *rmd, LL len) { 
	LL sum = 0;
	LL lcm = 1; 
	//lcm为除数们的最小公倍数, 若div互素, 则如下一行计算lcm 
	for (int i = 0; i < len; ++i) 
		lcm *= div[i];
	for (int i = 0; i < len; ++i) {
		LL bsn = lcm / div[i];
		LL inv = Inv(bsn, div[i]);
		// dvd[i] = inv[i] * bsn[i] * rmd[i]
		LL dvd = MulMod(MulMod(inv, bsn, lcm), rmd[i], lcm);
		sum = (sum + dvd) % lcm; 
	}
	return sum; 
}