import java.math.BigInteger;

public class Main {
	static BigInteger n,mod;
	public static BigInteger Sqrt(BigInteger c) {
		if(c.compareTo(BigInteger.ONE)<=0)
			return c;
		BigInteger temp=null,x;
		x=c.shiftRight((c.bitLength()+1)/2);
		while(true) {
			temp=x;
			x=x.add(c.divide(x)).shiftRight(1);
			if(temp.equals(x)||x.add(BigInteger.ONE).equals(temp)) break;
		}
		return x;
	}
	public static boolean judge(BigInteger c) {
		BigInteger x=Sqrt(c);
		if(x.multiply(x).equals(c)) {
			return true;
		} else {
			return false;
		}
	}
}