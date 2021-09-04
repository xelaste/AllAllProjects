
public class Strings {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
 		// TODO Auto-generated method stub
		String xx = "aa.bb.Icc";
		int pos = xx.lastIndexOf('.');
		System.out.println (xx.substring(pos + 1));
		String yy = xx.substring(pos + 1);
		if ( yy.startsWith("I"))
			System.out.println ( yy.substring(1) );
		
		
	}

}
