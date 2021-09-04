import java.io.File;
import java.io.FileInputStream;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;


public class Decrypt {

    private HashMap <Character,Character> mapDcr = new HashMap<Character, Character>();  
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Decrypt d = new Decrypt();
		File f = new File (args[0] );
		d.init();
        d.deCrypt( f );   

	}
	private void init ()
	{
       		mapDcr.put('V', 'h');
       		mapDcr.put('Q', 't');
       		mapDcr.put('F', 'e');
       		mapDcr.put('H', 'a');
       		mapDcr.put('O', 'o');
       		mapDcr.put('L', 'n');
       		mapDcr.put('G', 'r');
       		mapDcr.put('I', 'u');
       		mapDcr.put('E', 'f');
       		mapDcr.put('Z', 'l');
       		mapDcr.put('C', 'b');
       		mapDcr.put('P', 'm');
       		mapDcr.put('R', 'y');
       		mapDcr.put('D', 'x');
       		mapDcr.put('W', 's');
       		mapDcr.put('B', 'i');
       		mapDcr.put('Z', 'l');
       		mapDcr.put('A', 'v');
       		mapDcr.put('I', 'u');
       		mapDcr.put('J', 'c');
       		mapDcr.put('M', 'p');
       		mapDcr.put('Y', 'g');
       		mapDcr.put('K', 'd');
       		mapDcr.put('X', 'k');
       		mapDcr.put('S', 'w');
       		
	}
	private void deCrypt( File f )
	{
		try {
			FileInputStream fis = new FileInputStream ( f );
			StringBuffer buf = new StringBuffer();
			StringBuffer buf1 = new StringBuffer();
			for ( int c = fis.read(), counter=0;c>-1;c= fis.read(),counter++ )
			{
			    buf.append((char)c); 
				Character decripted = mapDcr.get((char)c);
			     
			     if ( decripted == null )
			    	 decripted = ' ';
            	 buf1.append( decripted );
			} 
			System.out.println(buf1);   	
			System.out.println( buf );

		} catch ( Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
