/*
 * Course 22923 - Computer System Security
 * Assignement 14 
 * Author Stekolchik Alexander
 * id 303967020
 * 
 * Important
 * Use jdk1.5 in order to compile this code
 */
/**
 * Permutation cipher
 * From Wikipedia, the free encyclopedia
 * Jump to: navigation, search
 * In classical cryptography, a permutation cipher 
 * is a transposition cipher in which the key is a permutation.
 * To apply a cipher, a random permutation of size e is generated 
 * (the larger the value of e the more secure the cipher). 
 * The plaintext is then broken into segments of size e and the letters within 
 * that segment are permuted according to this key.
 * In theory, any transposition cipher can be viewed as a permutation cipher 
 * where e is equal to the length of the plaintext; 
 * this is too cumbersome a generalisation to use in actual practice, however.
 * 
 * The current implementation does not use the random number e for creating 
 * permutation but  constant 4x6=24 as the algorithm uses rectangle 4x6 for 
 * encript / decript the text. The encritping algorithm is
 * 1) Divide the input into the 24 character length segments
 * 2) Put each segment into matrice 4x6 from left to right
 * 3) Change order of the column according the key word
 * 4) Unroll the matrice into segment
 * 5) Write the segment to output 
 * 
 */
package cipher;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.Writer;
import java.util.Arrays;

public class SimplePermutationCipher 
{
	// The number of elements in the block
	private final static int SEG_LEN = 24;
	// number of rows in the block 
	private final static int HEIGHT = 4;
	//  number of columns
	private final static int WIDTH = 6;

	private String key;
	private String inputFileName;
	private String outputFileName;
	private boolean printOnConsole;
	private boolean decript;
	private int[] shuffleOrder;

	/**
	 * Execution from command line
	 * @param args
	 */
	public static void main (String args[] )
	{
		String key = null;
		String inputFileName = null;
		String outputFileName = null;
		boolean printHelp = false;
		boolean printOnConsole = true;
		boolean decript = false;

		final String help = " Using \n" 
		+ "$_JAVA_HOME/bin/java ViegareCipher -k key_value "
		+ "-f the input file name "
		+ "-o the output file name\n"
		+ "-d "
		+ "if -o parameter omited then use the standard output for result print \n"
		+ "if -d parameter indicated the action is to decript the input file \n" +
		"otherwise teh action is to encript the input file"
		+ " Or \n"
		+ "$_JAVA_HOME/bin/java cipher.SimplePermutationCipher -help"
		+ " for print this message.";

		// validate input
		for (int i = 0; i < args.length; i++) 
		{
//			read the key
			if (args[i].equals("-k") && i + 1 < args.length )
			{	 
				key = args[++i];
				continue;
			}	 
//			read the input file name
			if (args[i].equals("-f") && i + 1 < args.length )
			{	 
				inputFileName = args[++i];
				continue;
			}	 
//			read the desired action
			if (args[i].equals("-d")  )
			{	 
				decript = true;
				continue;
			}	 

//			read the output file name if it is not indicated then the output will redirected to 
//			console
			if (args[i].equals("-o") && i + 1 < args.length )
			{ 
				outputFileName = args[++i];
				printOnConsole = false;
				continue;
			}	 
//			Show the help message
			if (args[i].equals("-help") )
			{ 
				printHelp = true;
				continue;
			}	 

		}

		if ( key == null || key.trim().equals("") 
				|| inputFileName == null || printHelp )
		{
			System.out.println( help );
			System.exit (0);
		}

		// initilaize cipher engine
		SimplePermutationCipher engine = new SimplePermutationCipher ( key,
				inputFileName,
				outputFileName,
				printOnConsole,
				decript);
		
		try {
			engine.execute();
		} catch (Exception e) {
			e.printStackTrace();
		}

	}


	/**
	 * The class public constructor
	 * @param key - key for encript/decript
	 * @param inputFileName the input
	 * @param outputFileName the result of decripting/encripting action 
	 * will directed to this file name 
	 * @param printOnConsole the program will output the file to console
	 * @param decript action if is true the decripting action envolved 
	 * elso the input will be encripted with the key
	 */
	public SimplePermutationCipher (  String key,
			String inputFileName,
			String outputFileName,
			boolean printOnConsole,
			boolean decript
	)
	{
		this.key = key;
		this.inputFileName = inputFileName;
		this.outputFileName = outputFileName;
		this.printOnConsole = printOnConsole;
		this.decript = decript;
		/*
		 *  create the order for column scrambling. The sequence replaces the
		 *  duplicates. e.g if key is java then the scrambling order is
		 *  4,2,5,3,0,1 (j = 4,a=2,v=2,a=3(second occurence get the next 
		 *  sequence number,0,1 padding the missing charracters- key length is
		 *  six. 
		 */
		this.shuffleOrder = new int[ WIDTH ];
		String effectiveKey =  ( key.length() > ( WIDTH ) )
		? this.key.substring(0,WIDTH)
		: this.key;
		char[] sortedKey = effectiveKey.toCharArray();
        Arrays.sort ( sortedKey );
        
        int[] values = new int[shuffleOrder.length];
        // Set the shuffleorder according to the ascii order of the letters in the 
        // key. e.g if key = java then shuffleOrder[0]=3 as j is the j value is 
        // the third.  
        for (int i = 0; i < sortedKey.length; i++) 
        {
          char c = effectiveKey.charAt (i);
          int idx = Arrays.binarySearch(sortedKey , c ); 
          this.shuffleOrder[i] = idx;
		  values[i]=idx;
		}
        
        // remove duplicates and replace it by sequental numbers
        Arrays.sort ( values );
        for ( int i = 0; i < values.length; i++ ) 
        {
			int val = values[i];
			// if duplicate exists
			if ( i > 0 && val == values [i-1 ] )
			{
				int pos = -1;
				// find it first occurences in the shuffleOrder
				// array
				for ( int j=0; j<shuffleOrder.length;j++ )
				{
					if ( this.shuffleOrder[j] == val )
						if ( pos < 0 )
						{	
							pos = j;
							break;
						}	
				}
                // increment by 1 the value all the elements bigger or equal val 
				// then one except its first occurences 
				for ( int j=0; j < this.shuffleOrder.length;j++ )
				{
					if ( j != pos && this.shuffleOrder[j] >= val )
						this.shuffleOrder[j]++;
				}
                
				// update the sorted value list with the new values
				for (int j = i ; j < values.length; j++) {
                	values[j]++;
				}
			}
		}
	}

	protected void execute() throws Exception
	{
		Reader reader;
//		Check the input file existance and open it
		try 
		{
			InputStream is = null;
			is = new FileInputStream ( this.inputFileName );
			reader = new InputStreamReader ( is);
		}
		catch ( FileNotFoundException e )
		{
			throw new RuntimeException ( "The input file " + 
					this.inputFileName + "\ndoes not exist." );
		}
//		Open output for write		
		
		Writer writer = null;
		try 
		{
			OutputStream os =
				this.printOnConsole ?
						System.out
						:
							new FileOutputStream ( outputFileName );
			writer = new OutputStreamWriter ( os );
		}
		catch ( FileNotFoundException e )
		{
			throw new RuntimeException ( "The problem open output file " + 
					this.outputFileName );
		}
		char[] segment = null;
        // process the input 
		segment = readSegment ( reader );
        while ( segment != null )
        {
        	if ( decript )
        		segment = decriptData ( segment );
        	else
        		segment = encriptData ( segment );
        	writeSegment( writer , segment );
        	segment = readSegment ( reader );
        }
        writer.close();
        reader.close();
	}

	/**
	 * Read the input file into the one dimension buffers  
	 * retrurn the null at the and of the input stream
	 * @param data input stream for reading data
	 * @return char [SEG_LEN] , null at the end of data.
	 * @throws Exception
	 */
	private char[] readSegment ( Reader data ) throws Exception
	{
		char segment[] = new char [SEG_LEN];
		/*
		 * padding the array with asterisk. if the segment length does not
		 * devide input length then pad missing char within asterisks 
		 */
		for (int i=0;i<segment.length;i++)
		{
			segment[i]= new Character ( ( char ) 0x2a ); // '*'
		}
        int c = data.read( segment ); 

        if ( c < 0 )
        	segment = null;
		return segment;
	}

	/**
     * Writing the buffer of data to the output target
     * @param target
     * @param data
     * @throws Exception 
     */
	private void writeSegment ( Writer os, char[] data ) throws Exception
	{
		os.write( data );
	}

	/**
	 * Encript the character baffer using the Permutation cipher algorithm
	 * @param data the buffer for encription
	 * @return encripted data
	 */
	private char[] encriptData ( char[] data )
	{
		char block[][] = new char [HEIGHT][WIDTH];
		// Write the data from one dimension array
		// to the two dimension matrix column by column
		// The order is from top down from left to right
		for (int i = 0; i < data.length; i++) 
        {
		   int k = i / HEIGHT;
		   int l = i % HEIGHT;
		   block[ l ][ k ] = data [ i ];
		}
        // mess the column order 
        block = shuffleColumns ( block );
		char retval [] = new char [ HEIGHT * WIDTH ];
		/*
		 * Write the matrix back to one dimentsion buffer line by line
		 */
		for (int i = 0; i < block.length; i++) 
		{
			for (int j = 0; j < block[i].length; j++) {
				retval[ i * WIDTH + j ] = block[i][j];
			}
		}
		return retval;
	}

	/**
	 * Decript the character buffer using the Permutation cipher algorithm
	 * @param data the buffer for decription
	 * @return decripted data
	 */
	
	private char[] decriptData ( char[] data )
	{
		char block[][] = new char [HEIGHT][WIDTH];
		// Fill the matrix within the characters from data
		// buffer line by line.
		for (int i = 0; i < HEIGHT; i++) 
		{
			for (int j = 0; j < WIDTH; j++) 
			{
				block[i][j] = data[ i * WIDTH + j  ];
			}	
		}
		
		// Restore the order of the columns
		block = unShuffleColumns ( block );
		// Write the data back to one dimension array
		// column by column
		char retval [] = new char [ HEIGHT * WIDTH ];
        for (int i = 0; i < retval.length; i++) 
        {
		   int k = i / HEIGHT;
		   int l = i % HEIGHT;
		   retval [ i ] = block[ l ][ k ];
		}
		return retval;
	}
    
	/**
	 * shuffle the columns of data matrix corresponding to the 
	 * shuffleOrder array.
	 * @param data the matrice for changig column order
	 * @return the matrice with shuffled columns
	 */
	private char[][] shuffleColumns ( char data[][])
    {
     
    	char retval [][] = new char[HEIGHT][WIDTH];
    	for (int i = 0; i < this.shuffleOrder.length; i++) 
    	{
    		int val = this.shuffleOrder[i];
    		for (int j=0;j<HEIGHT;j++ )
    			retval [ j ][ i ] = data[ j ][ val ];
		}
    	return retval;	
    }

	 /**
	  * Restore the original column order 
	  * @param data matrice with scrambled columns
	  * @return matrice with original column order
	  */
    private char[][] unShuffleColumns ( char data[][])
    {
     
    	char retval [][] = new char[HEIGHT][WIDTH];
    	for (int i = 0; i < this.shuffleOrder.length; i++) 
    	{
    		int val = this.shuffleOrder[i];
    		for (int j=0;j<HEIGHT;j++ )
    			retval [ j ][ val ] = data[ j ][ i ];
		}
    	return retval;	
    }

}
