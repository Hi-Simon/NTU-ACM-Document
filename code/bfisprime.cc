bool is_prime(int  u) {
	if(u ==  0 || u ==  1) return false;
	if(u ==  2)      return true;
	if(u%2 == 0)      return false;
	for(int i=3; i <=  sqrt(u) ; i+=2)
		if(u%i==0)      return false;
	return true;
}