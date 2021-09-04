package crack;

import java.io.File;
import java.io.FileReader;

public class CharacterFrequencies 
{
	public static void main(String[] args) throws Exception 
	{
		FileReader fr_bigrams = new java.io.FileReader ( args[0] );
		int size = (int) (new File(args[0]) ).length();
		for (int i=2;i<Math.sqrt(size) +1 ;i++)
			if ( size % i == 0)
				System.out.println ( i );
		
        int percent[] = new int [Character.MAX_VALUE];
        for (int c = fr_bigrams.read();c>0;c=fr_bigrams.read() )
        {
        	percent[c]++;
        }
	    for (int i = 0; i < percent.length; i++) {
			percent[i] =(int) Math.round( percent[i] * 100.0 /size );
		}
	    
	    for (char i = 0; i < percent.length; i++) {
		   if (percent[i] > 2 ) {
			   String s = i + "";
			   if (i=='\n')
				   s = new String ("new line");
			   
			   if (i=='\r')
				   s = new String ("cr");

			   if (i=='\t')
				   s = new String ("tab");
			   
			   if (i==' ')
				   s = new String ("space");
			   
			   System.out.println( s + "=" + percent[i]+"%" );
		   }   
		}

	} 
	
}
