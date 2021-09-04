
public class InverseNumber {
	/**
	 * Find inverse for given number.
	 * implementation of Euclidus advanced algorithm 
	 * Ri+1 = Ri - f * Ri-1
	 * The inverse is the sum of the factors in the all iterations
	 * if the inverse number is negative the next value from the group created by 
	 * mod a operation
	 * one iteration the number is negative the next one is positive 
	 * according to algorithm definition
	 * @author ALEXANDERST
	 */

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		System.out.println ( "inverse 231 mod 100 = " + ( new InverseNumber()).findInverseNumber ( 100, 231 ) );
		System.out.println ( "inverse 700 mod 33 = " + ( new InverseNumber()).findInverseNumber ( 33, 700 ) );
		System.out.println ( "inverse 3300 mod 7 = " + ( new InverseNumber()).findInverseNumber ( 7, 3300 ) );
		System.out.println ( "inverse 3 mod 280 = " + ( new InverseNumber()).findInverseNumber ( 280, 3 ) );
		System.out.println ( ( 100 * 100 * 100 ) % 319 );
	}
	/*
	 * find inverse (g) mod e )
	 */
	public long findInverseNumber ( long e,long g)
	{

		long a,b;
        a = e; 
		if ( g > e)
		{
		  b = g % e;	
		}
		else 
		{
			b = g;
		}


		long x = 0; 

		long r1 = a;
		long r2 = b;
		long r = 0;

		long a1 = 1;
		long a2 = 0;
		long a3 = 0;

		long b1 = 0;
		long b2 = 1;
		long b3 = 0;

		long f=0;
		boolean positive = true;

		do {
			r = r1 % r2;
			f = r1 / r2;
			a3 = a1 + f * a2;
			b3 = b1 + f * b2;
			r1 = r2;
			r2 = r;

			a1 = a2;
			a2 = a3;

			b1 = b2;
			b2 = b3;
			positive = !positive;
		}
		while ( r > 1 );

		if ( !positive )
			x = a - b3;
		else
			x = b3;

		return x;
	} 

}

