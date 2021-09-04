
public class BigModulus 
{
 public static void main (String[] args )
 {
//	long C = 11220;
//	long N = 17741;

	long C = 254;
	long N = 319;

	int k = 1;
	long m = C;
	for ( int i = 1;i<20 && m > 0 ;i++ )
	{
		System.out.println ( k + ";" + m );
		k = k * 2;
        m =  ( m * m ) % N;
        //11220 * 16946 * 8584 * 6683 * 8392 * 11635 * 4550 * 16494 
	}
    System.out.println ( 11220 * 16946 % 17741 );
    System.out.println ( 8584 * 6683 % 17741 );
    System.out.println ( 8392 * 11635 % 17741 );
    System.out.println ( 4550 * 16494 % 17741 );
    System.out.println ( "=============" );
    System.out.println ( 3823 * 10219 % 17741 ); 
    System.out.println ( 12197 * 3270 % 17741 );
    System.out.println ( "=============" );
    System.out.println ( 1555 * 2422 % 17741 );
    System.out.println ( ( ( 254 * 78 ) % 319 * ( 210 * 78) % 319 * (23 * 78 ) % 319 ) % 319 );

 }
}
