import java.io.File;
import java.io.FileInputStream;
import java.text.NumberFormat;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Set;


public class CharCount {

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
	    try {
			
			File f = new File (args[0] );
			long total = f.length();
			FileInputStream fis = new FileInputStream ( f );
			int[] chars = new int[26];
			for (int i = 0; i < chars.length; chars[i++]=0 ); 
			HashMap<String, Integer> digraphs = new HashMap<String, Integer>();
			HashMap<String, Integer> trigraphs = new HashMap<String, Integer>();
			LinkedHashMap<Integer, Character> decrypt = new  LinkedHashMap <Integer, Character>(); 
			char[] digraph = new char[2];
			char[] trigraph = new char[3];
			for ( int c = fis.read(), counter=0;c>-1;c= fis.read(),counter++ )
			{
                if (c == '\n' || c == '\t' || c == '\r' || c == ' ' )
                	continue;
                decrypt.put(counter, (char) ( 'A' + (15 * (c - 'A') + 23) % 26 ) );
                chars[c - 'A']++; 
                digraph[0] = digraph[1];
				digraph[1] = (char)c;
				
				trigraph[0] = trigraph[1];
				trigraph[1] = trigraph[2];
				trigraph[2] = (char)c;
				
				if (counter > 0 )
				{
					String key = "" + digraph[ 0 ] + digraph[1];      
					Integer val = (Integer) digraphs.get(  key );
					if (val == null )
						val = 1;
					else
						val = val + 1;
					digraphs.put(  key , val );
				}
				
				if (counter > 1 )
				{
					String key = "" + trigraph[ 0 ] + trigraph[1] + trigraph[2];      
					Integer val = (Integer) trigraphs.get(  key );
					if (val == null )
						val = 1;
					else
						val = val + 1;
					trigraphs.put(  key , val );
				}
				
				
			}
		for (int c = 'A'; c<='Z'; c++ )
		{
			Integer val = chars[c - 'A'];
			if ( val == null ) 
				val = 0;
			double x =  100.0 * val/total;
			x = Math.round( x * 100 ) / 100.0 ;
			NumberFormat nf = NumberFormat.getInstance();
			System.out.println ((char)c + "\t" +   val + '\t' + nf.format ( x ) );
			System.out.println( (char) (c - 'A' + 'a') + "oal");
		}

	    Set<Map.Entry<String, Integer>> setDigraphs = digraphs.entrySet();
	    Iterator<Map.Entry<String, Integer>>  it = setDigraphs.iterator();
	    while (it.hasNext() )
	    {
	    	Map.Entry<String, Integer> entry = it.next(); 
	    	System.out.println( entry.getKey() + "\t" + entry.getValue() );
	    }
	    
	    Set<Map.Entry<String, Integer>> setTrigraphs = trigraphs.entrySet();
	    Iterator<Map.Entry<String, Integer>>  it1 = setTrigraphs.iterator();
	    while (it1.hasNext() )
	    {
	    	Map.Entry<String, Integer> entry = it1.next(); 
	    	System.out.println( entry.getKey() + "\t" + entry.getValue() );
	    }

	    Iterator<Character> itd = decrypt.values().iterator();
	    while ( itd.hasNext())
	    	System.out.print(itd.next());
	    
	    } catch ( Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
