package crack;
/*
 * Course 22923 - Computer System Security
 * Assignement 14 
 * Author Stekolchik Alexander
 * id 303967020
 * 
 * Important
 * Use jdk1.5 in order to compile this code
 */
import java.io.File;
import java.io.FileReader;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import cipher.VigenereCipher;

/**
 * @author alexanderst
 * 
 * This class is an object for cracking the Viginere cypher.
 * The class implements the Kasiski/Kerckhoff algorithm.
 * Kasiski's technique for finding the length of the keyword was based on 
 * measuring the distance between repeated bigrams in the ciphertext.
 * Factoring the distances between repeated bigrams is a way of identifying 
 * possible keyword lengths, 
 * with those factors that occur most frequently being the best candidates 
 * for the length of the keyword. 
 *  
 */ 

public class VigenereCipherCracker 
{
	private static final char DEFAULT_MOST_OCCURED_CHAR = ' ';
	public static void main (String argc[]) throws Exception
	{
		if (argc.length == 0 || argc[0].trim().equals("") )
			throw new RuntimeException ( "Usage java crack.VigenereCipherCracker "
					+ "$file name for analyze" );
		
		FileReader fr_bigrams = new java.io.FileReader ( argc[0] );
		int size = (int) (new File(argc[0]) ).length();
		size = ( int ) Math.round( Math.sqrt( size ) )  + 1;
		long factors[] = new long[ size ];
		long sortedFactors[] = new long[ size ];
        HashMap<String, List<Long>> bigrams = new HashMap<String, List<Long>>();
        char bigram[] = new char[2];
        /* look fo bigrams and all theirs appearance in the text
         * and the bigram place within the text/
         * The distance between bigrams is the difference between bigram 
         * posistions
         */
        int c = fr_bigrams.read( bigram );
        if ( c == bigram.length ) 
        {
        	for (long pos=2;c>-1;pos++ ) 
        	{

        		StringBuffer bf = new StringBuffer ();
        		bf.append(bigram);
        		String strBigram = bf.toString();
        		List <Long >bigram_ocurrences = bigrams.get( strBigram );  
        		if ( bigram_ocurrences == null ) {
        			FileReader fr_search = new java.io.FileReader ( argc[0] );
        			bigram_ocurrences = searchOccurences ( strBigram, fr_search , pos );
        			bigrams.put( bf.toString(), bigram_ocurrences );
        		}	
        		// next bigram in the secret text.
        		c=fr_bigrams.read();
                bigram[0] = bigram[1];
                bigram[1] = (char)c;
        	}
        }
		// analyse the factors of the distances between bigrams
        // use only bigrams having not less then two occurences
        Set<String> set = bigrams.keySet();
		Iterator<String> it = set.iterator();
		for (String key = it.next();it.hasNext();key = it.next() )
		{
			List <Long>l = bigrams.get(key);
			if ( l.size() >= 2 ) 
			{	
				long countDuplicatesDigrams = 0;
				// Find all the factors for the distance between first two 
				// occurence
				// omit other occurences as the first ones give 
				// enough  information
				// fill the two array
				// two array are necessary for find the three posible options
				// most common factors for each bigram.
				// e.g fo bigram ab we have distance beween occurences 10 
				// and for bc distance is 12 then after running the code bellow
				// factor[2]=2 //divides 1o and 12
				// factor[3]=1 //divides 12
				// factor[4]=1 //divides 12
				// factor[5]=1 //divides 10
                // factor[6]=1 //divides 12 

				long distance = l.get( 1 ) - l.get(0);
				for ( int i = 2 ; i <= Math.sqrt( distance ); i++ )
				{
					countDuplicatesDigrams ++;
					if ( distance % i == 0) 
					{	
						// If i is a factor for the distance between 
						// ocurences of the certain bigram then increment 
						// its counter in the factors and sort factors array. 
						//count the number of the specific factor
						// for the different bigram
						factors [i] ++;
						sortedFactors[i]++;
					}	
				}
			}

		}
        // Get the factors common to the most distances betwen digrams  
		Arrays.sort( sortedFactors );
		// The three factors that divide the most distances between 
		// bigram occurences inthe descending order
		// the value 1 is the number of distances the the most common factor 
		// divides 
		long value1 = sortedFactors[ factors.length - 1 ];
		long value2 = sortedFactors[ factors.length - 2 ];
		long value3 = sortedFactors[ factors.length - 3 ];
		
		// find the key length using the number of distances 
		// that the specific factor divide 
		int key1 = 0;
        int key2 = 0;
        int key3 = 0;
        for (int i = 0; i < factors.length; i++) 
        {
		  if ( factors[i] == value1 )
		    key1 = i;
		  if ( factors[i] == value2 )
			    key2 = i;
		  if ( factors[i] == value3 )
			    key3 = i;
          if (key1 * key2 * key3 > 0 )
        	  break;
		}
        
        // Use the most possible key length to find the key value 
        ResolveKeys resolveKeys = new ResolveKeys (
        		new java.io.FileInputStream ( argc[0]) , key1 );
        
        resolveKeys.execute();
        String keyValue1 = resolveKeys.getKey();
        
        resolveKeys = new ResolveKeys (
        		new java.io.FileInputStream ( argc[0]) , key2 );
        resolveKeys.execute();
        String keyValue2 = resolveKeys.getKey();
        

        resolveKeys = new ResolveKeys (
        		new java.io.FileInputStream ( argc[0]) , key3 );
        resolveKeys.execute();
        String keyValue3 = resolveKeys.getKey();

        System.out.println( "Possible key length and value");        
        System.out.println( "1)" + key1 + " " + keyValue1 );
        System.out.println( "2)" + key2 + " " + keyValue2 );
        System.out.println( "3)" + key3 + " " + keyValue3 );
		
	}
/**
 * Look for all the occurences the given bigram from the offset position
 * Returns the list of all found bigrams posistion itn the text.
 * @param bigram two letter combination
 * @param fr_search the input stream for search
 * @param offset the place to search from
 * @return the all the found bigram posisitons
 * @throws Exception
 */
	private static List<Long> searchOccurences(String bigram, 
			FileReader fr_search, long offset ) throws Exception 
	{
        char[] currentBigram = new char[2];
        List<Long> occurences = new ArrayList<Long> (20);
        fr_search.skip( offset - 2 );
        int c = fr_search.read ( currentBigram );
        for (long pos = 2; c>-1;c=fr_search.read (),currentBigram[1] = (char)c, 
                                                    pos++) 
        {
           StringBuffer bf = new StringBuffer ();
           bf.append( currentBigram );
           if ( bigram.equals(bf.toString()))
           {
        	   Long lngPos = new Long ( offset + pos - 4 );
        	   occurences.add ( lngPos );
           }
           currentBigram[0] = currentBigram[1];
        }
        return occurences;
	}

/**
 * This class is object for retrieve the key value from the  encripted text 
 * and known key length value
 * @author alexanderst
 *
 */
public static class ResolveKeys 
{
    private InputStream data;
    private int keyLength = 0;
    private String key;
    private int[][] cryptogram;
    /**
     * The object consructor, recieves as parameters input stream and the key length
     * @param data
     * @param keyLength
     */
	public ResolveKeys(InputStream data, int keyLength) {
		super();
		this.data = data;
		this.keyLength = keyLength;
		cryptogram = new int [ keyLength ][Character.MAX_VALUE];   
	}
	/**
	 * The key read method
	 * @return
	 */
	public String getKey() {
		return key;
	}
	
	/**
	 * Key length read method
	 * @return
	 */public int getKeyLength() {
		return keyLength;
	}
	
	
	/**
	 * Find the key for Vigenere cypher using the known key length
	 * Once the length of the keyword is known, 
	 * the ciphertext can be broken up into 
	 * that many simple substitution cryptograms
	 * after the message has been separated into several columns, 
	 * corresponding to the simple substitution cryptograms, 
	 * one tallies the frequencies in each column and then uses frequency 
	 * and logical analysis to construct the key. For example, 
	 * suppose the most frequent letter in the first column is 'K'. 
	 * We would hypothesize that 'K' corresponds to the English 'E'. 
	 * If we consult the Vigenere tableau at this point, 
	 * we can see that if English 'E' were enciphered into 'K' 
	 * then row G of the table must have been the alphabet 
	 * used for the first letter of the keyword. 
	 * This implies that the first letter of the keyword is 'G'.
	 * 
	 *  The current implementation uses all punctuation characters and space, then
	 *  the most frequent symbol is space, therefore it used for rsolving the key
	 *  value. 
	 * @throws Exception
	 */
	public void execute () throws Exception
	{
		VigenereCipher.TabulaRecta tabulaRecta = 
			VigenereCipher.TabulaRecta.getTabulaRectaInstance();

		// find letter distribution frequencies
		for (int i=0, c = data.read();c>-1;c=data.read(),i++ )
        {
        	cryptogram[i % keyLength ] [ c ] ++;
        }
	    StringBuffer bf = new StringBuffer ();
		for (int i =0;i<keyLength;i++ )
		{
			int max = 0;
			for (int j=0;j<cryptogram[i].length;j++ )
				if ( cryptogram[i][j] > cryptogram[i][max] )
					max = j;
		    // AS the space is the part of tabularecta ,then it is the most
			// frequent symbol in the text.
			char k = tabulaRecta.findKeyLetter( (char) max, DEFAULT_MOST_OCCURED_CHAR );
			bf.append(k);
		}
		key = bf.toString();
	}
}

}
