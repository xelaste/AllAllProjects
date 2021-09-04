package cipher;

/*
 * Course 22923 - Computer System Security
 * Assignement 14 
 * Author Stekolchik Alexander
 * id 303967020
 * 
 * Important
 * Use jdk1.5 in order to compile this code
 */

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.util.HashMap;

/**
 * 
 * The Vigenere Cipher -- A Polyalphabetic Cipher 
 * One of the main problems with simple substitution ciphers is that they are so 
 * vulnerable to frequency analysis. Given a sufficiently large ciphertext, 
 * it can easily be broken by mapping the frequency of its letters to the know 
 * frequencies of, say, English text. Therefore, to make ciphers more secure, 
 * cryptographers have long been interested in developing enciphering techniques 
 * that are immune to frequency analysis. 
 * One of the most common approaches is to suppress the normal frequency data 
 * by using more than one alphabet to encrypt the message. 
 * A polyalphabetic substitution cipher involves the use of two or more 
 * cipher alphabets. Instead of there being a one-to-one relationship 
 * between each letter and its substitute, there is a one-to-many relationship 
 * between each letter and its substitutes.
 * The Vigenere Tableau
The Vigenere Cipher , proposed by Blaise de Vigenere 
from the court of Henry III of France in the sixteenth century, 
is a polyalphabetic substitution based on the following tableau:

        	    A B C D E F G H I J K L M N O P Q R S T U V W X Y Z

    	A   A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
    	B   B C D E F G H I J K L M N O P Q R S T U V W X Y Z A 
    	C   C D E F G H I J K L M N O P Q R S T U V W X Y Z A B
    	D   D E F G H I J K L M N O P Q R S T U V W X Y Z A B C 
    	E   E F G H I J K L M N O P Q R S T U V W X Y Z A B C D 
    	F   F G H I J K L M N O P Q R S T U V W X Y Z A B C D E 
    	G   G H I J K L M N O P Q R S T U V W X Y Z A B C D E F 
    	H   H I J K L M N O P Q R S T U V W X Y Z A B C D E F G 
    	I   I J K L M N O P Q R S T U V W X Y Z A B C D E F G H 
    	J   J K L M N O P Q R S T U V W X Y Z A B C D E F G H I 
    	K   K L M N O P Q R S T U V W X Y Z A B C D E F G H I J 
    	L   L M N O P Q R S T U V W X Y Z A B C D E F G H I J K 
    	M   M N O P Q R S T U V W X Y Z A B C D E F G H I J K L 
    	N   N O P Q R S T U V W X Y Z A B C D E F G H I J K L M 
    	O   O P Q R S T U V W X Y Z A B C D E F G H I J K L M N 
    	P   P Q R S T U V W X Y Z A B C D E F G H I J K L M N O 
    	Q   Q R S T U V W X Y Z A B C D E F G H I J K L M N O P 
    	R   R S T U V W X Y Z A B C D E F G H I J K L M N O P Q 
    	S   S T U V W X Y Z A B C D E F G H I J K L M N O P Q R  
    	T   T U V W X Y Z A B C D E F G H I J K L M N O P Q R S 
    	U   U V W X Y Z A B C D E F G H I J K L M N O P Q R S T 
    	V   V W X Y Z A B C D E F G H I J K L M N O P Q R S T U
    	W   W X Y Z A B C D E F G H I J K L M N O P Q R S T U V 
    	X   X Y Z A B C D E F G H I J K L M N O P Q R S T U V W 
    	Y   Y Z A B C D E F G H I J K L M N O P Q R S T U V W X 
    	Z   Z A B C D E F G H I J K L M N O P Q R S T U V W X Y 

Note that each row of the table corresponds to a Caesar Cipher. 
The first row is a shift of 0; the second is a shift of 1; 
and the last is a shift of 25.
The Vigenere cipher uses this table together 
with a keyword to encipher a message. For example, 
suppose we wish to encipher the plaintext message:
    TO BE OR NOT TO BE THAT IS THE QUESTION 
using the keyword RELATIONS. 
We begin by writing the keyword, 
repeated as many times as necessary, above the plaintext message. 
To derive the ciphertext using the tableau, for each letter in the plaintext, 
one finds the intersection of the row given by the corresponding keyword letter 
and the column given by the plaintext letter itself to pick out 
the ciphertext letter.

	Keyword:	RELAT IONSR ELATI ONSRE LATIO NSREL
	Plaintext:	TOBEO RNOTT OBETH ATIST HEQUE STION
	Ciphertext:	KSMEH ZBBLK SMEMP OGAJX SEJCS FLZSY

Decipherment of an encrypted message is equally straightforward. 
One writes the keyword repeatedly above the message:

	Keyword:	RELAT IONSR ELATI ONSRE LATIO NSREL
	Ciphertext:	KSMEH ZBBLK SMEMP OGAJX SEJCS FLZSY
	Plaintext:	TOBEO RNOTT OBETH ATIST HEQUE STION

This time one uses the keyword letter to pick a column of the table 
and then traces down the column to the row containing the ciphertext letter. 
The index of that row is the plaintext letter. 

In a Caesar cipher, 
each letter of the alphabet is shifted along some number of places; for example, 
in a Caesar cipher of shift 3, A would become D, B would become E and so on. 
The Vigenere cipher consists of several Caesar ciphers in sequence 
with different shift values.

To encipher, a table of alphabets can be used, termed a tabula recta, 
Vigenere square, or Vigenere table. 
It consists of the alphabet written out 26 times in different rows, 
each alphabet shifted cyclically to the left compared to the previous alphabet, 
corresponding to the 26 possible Caesar ciphers. 
At different points in the encryption process, 
the cipher uses a different alphabet from one of the rows. 
The alphabet used at each point depends on a repeating keyword.

For example, suppose that the plaintext to be encrypted is:

    ATTACKATDAWN

The person sending the message chooses a keyword and repeats it until it matches 
the length of the plaintext, for example, the keyword "LEMON":

    LEMONLEMONLE

The first letter of the plaintext, A, is enciphered using the alphabet in row L, 
which is the first letter of the key. 
This is done by looking at the letter in row L 
and column A of the Vigenere square, namely L. 
Similarly, for the second letter of the plaintext, 
the second letter of the key is used; the letter at row E and column T is X. 
The rest of the plaintext is enciphered in a similar fashion:
Plaintext: 	ATTACKATDAWN
Key: 	LEMONLEMONLE
Ciphertext: 	LXFOPVEFRNHR

Decryption is performed by finding the position of the ciphertext letter 
in a row of the table, and then taking the label of the column in which 
it appears as the plaintext. For example, in row L, 
the ciphertext L appears in column A, which taken as the first plaintext letter. 
The second letter is decrypted by looking up X in row E of the table; 
it appears in column T, which is taken as the plaintext letter.

Vigenere can also be viewed algebraically. 
If the letters A-Z are taken to be the numbers 0-25, 
and addition is performed modulo 26, then Vigenere encryption can be written,

    C_i = (P_i + K_i) \mod 26

and decryption,

    P_i = (C_i - K_i) \mod 26 
 * This implementation handles the Alphanumerec characters 
 * and punctuation characters so well. 
 * The digits and punctuation characters where added to the 
 * alphabet  
 *
 */

public class VigenereCipher 
{
    
	private String key;
	private String inputFileName;
	private String outputFileName;
	private boolean printOnConsole;
	private boolean decript;
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
	public VigenereCipher (  String key,
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

	
	}
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
			+ "$_JAVA_HOME/bin/java cipher.VigenereCipher -help"
			+ " for print this message.";
		
		// validate input
		for (int i = 0; i < args.length; i++) 
		{
// read the key
			if (args[i].equals("-k") && i + 1 < args.length )
		     {	 
		    	 key = args[++i];
		    	 continue;
		     }	 
// read the input file name
		     if (args[i].equals("-f") && i + 1 < args.length )
		     {	 
		    	 inputFileName = args[++i];
		    	 continue;
		     }	 
// read the desired action
		     if (args[i].equals("-d")  )
		     {	 
		    	 decript = true;
		    	 continue;
		     }	 

// read the output file name if it is not indicated then the output will redirected to 
// console
		     if (args[i].equals("-o") && i + 1 < args.length )
		     { 
		    	 outputFileName = args[++i];
		    	 printOnConsole = false;
		    	 continue;
		     }	 
// Show the help message
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
		VigenereCipher engine = new VigenereCipher ( key,
				                                   inputFileName,
				                                   outputFileName,
				                                   printOnConsole,
				                                   decript);
		engine.processInputFile();

 
		
	}
	
	/**
	 * This function in fact implement the 
	 * encript/decript algorithm
	 * This function functionality is
	 * Check input parameters,
	 * Open input file for read , open output file for write, in case the output
	 * to console indicated use the system.out stream for output
	 * While not EOF of input 
	 *  Read character encrypt/decript it using the TabulaRecta class, 
	 *  write generated character to output. 
	 */
	public void processInputFile()
	{
		java.io.FileReader fr = null;
// Check the input file existance and open it
		try 
		{
		 fr = new FileReader( this.inputFileName );
		}
		catch ( FileNotFoundException e )
		{
			e.printStackTrace();
			throw new RuntimeException ( "The input file " + 
					this.inputFileName + "\ndoes not exist." );
		}
// Open output for write		
		Writer os = null;
		try 
		{
		  os =
			 this.printOnConsole ?
					 new OutputStreamWriter ( System.out )
		 :
			 new OutputStreamWriter ( new FileOutputStream ( outputFileName ) ); 
		}
		catch ( IOException e )
		{
			e.printStackTrace();
			throw new RuntimeException ( "The problem open output file " + 
					this.outputFileName );
		}
        
		/*
		 *		Encript/decript the file
		 */
		try 
		{
			TabulaRecta tabulaRecta = TabulaRecta.getTabulaRectaInstance();
			int shift = 0;
			for ( int c = fr.read();c>-1; c = fr.read() )
			{
				char row = key.charAt ( shift );
				char result = 
					decript 
					?
							tabulaRecta.decritptChar(row, (char) c)
				    :
				    	tabulaRecta.encriptChar( row, (char) c );
				
			    os.write(  result   );
				shift = (shift + 1) % key.length();
			}
			os.close();
			fr.close();
		}
		catch (Exception e)
		{
			e.printStackTrace();
			System.exit(2);
		}
	}
	
	/**
	 * This class represent the single characer in the text.
	 * The Token object has the terminal for represnting the input character itself
	 * and shift value from the first alphbet character
	 * @author alexanderst
	 *
	 */
	static public class Token {
		private char terminal;
		private int shift;

		public Token(char terminal, int shift) {
			super();
			this.terminal = terminal;
			this.shift = shift;
		}
		public int getShift() {
			return shift;
		}
		public void setShift(int shift) {
			this.shift = shift;
		}
		public char getTerminal() {
			return terminal;
		}
		public void setTerminal(char terminal) {
			this.terminal = terminal;
		}
	}
	/**
	 * This class implementing the tabula recta object needed for 
	 * executing encritption/decritption the single characters
	 * @author alexanderst
	 *
	 */
	static public class TabulaRecta 
	{
		private HashMap<Character, Token> tabulaRectaRows = 
				new HashMap<Character, Token>(); 
		private HashMap <Integer,Token> tabulaRectaCols = 
				new HashMap<Integer, Token>();
		private static char[] arrNotAlphaNumericTerminals = 
		{'\t',' ','\r','\n','\'','\"','?','.',':',';','!','\\','/',',' };
		
		/**
		 * initialize the tabula recta object add the rows and columns
		 * to the Vigenere table.
		 *
		 */
		private final int size;
		private static TabulaRecta m_tabula = new TabulaRecta (); 
		public static TabulaRecta getTabulaRectaInstance()
		{
			return m_tabula;
		}
		private TabulaRecta ()
		{
			int count = 0;
			// Adding letters
			for ( char c = 'a'; c<'z'+1; c++ )
			{
			   char upperCaseChar = (char) ('A' + (c - 'a') );
			   Token lowCaseToken = new Token ( c, count++ );
			   Token upperCaseToken = new Token ( upperCaseChar , count++  );
			   tabulaRectaRows.put( new Character (c) , lowCaseToken );
			   tabulaRectaCols.put( new Integer (lowCaseToken.getShift() ), 
					                             lowCaseToken );
			   tabulaRectaRows.put( new Character (upperCaseChar) , upperCaseToken );
			   tabulaRectaCols.put( new Integer (upperCaseToken.getShift() ), 
					   upperCaseToken );

			}
			// Adding digits
			for (char c = '0' ; c < '9' + 1 ; c++)
			{
				Token digitToken = new Token ( c, count++ );
				tabulaRectaRows.put( new Character (c) , digitToken );
				tabulaRectaCols.put( new Integer ( digitToken.getShift() ) 
                , digitToken );

			}
			for (int i = 0 ; i < arrNotAlphaNumericTerminals.length ; i++)
			{
				Token nonAlphaToken = new Token ( arrNotAlphaNumericTerminals[i], count++ );
				tabulaRectaRows.put( new Character ( nonAlphaToken.getTerminal()) 
				                                , nonAlphaToken );
				tabulaRectaCols.put( new Integer ( nonAlphaToken.getShift() ) 
                , nonAlphaToken );

			}
			// Adding digits

			size = count;
		}
		
		public int getSize() {
			return size;
		}
		/**
		 * C_i = (P_i + K_i) mod size
		 * @param key the current row in the tabula
		 * @param c the character to encrypt
		 * @return encripted character
		 */

		public char encriptChar (char key, char c)
		{
			Token keyToken = tabulaRectaRows.get( new Character( key) );
			Token charToken = tabulaRectaRows.get( new Character( c ) );
			int shift = ( keyToken.getShift() + charToken.shift ) % this.size; 
			return tabulaRectaCols.get( new Integer ( shift ) ).getTerminal();
		}

		/**
		 * C_i = (P_i - K_i) mod size
		 * @param key the current row in the tabula
		 * @param c the character to decrypt
		 * @return decripted character
		 */
		public char decritptChar (char key, char c)
		{
			Token keyToken = tabulaRectaRows.get( new Character( key) );
			Token charToken = tabulaRectaRows.get( new Character( c ) );
			int shift = ( charToken.shift - keyToken.getShift() ) % this.size; 
			if (shift < 0 ) shift += size;
			return tabulaRectaCols.get( new Integer ( shift ) ).getTerminal();

		}

		/**
		 * K_i = (C_i - P_i) mod size
		 * @param s encripted charactrer
		 * @param c clear text character
		 * @return key character
		 */
		public char findKeyLetter ( char s, char c )
		{
			Token secretCharToken = tabulaRectaRows.get( new Character( s ) );
			Token clearCharToken = tabulaRectaRows.get( new Character( c ) );
			int shift =  ( secretCharToken.getShift() 
					- clearCharToken.getShift() ) % this.size;  
			if (shift < 0 ) shift += size;
			return tabulaRectaCols.get( new Integer ( shift ) ).getTerminal();

		}
	
	}
}
