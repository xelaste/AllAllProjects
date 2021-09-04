package cipher;
import java.util.BitSet;

import util.DesBitSet;


public class KeyGenerator {
    
	static public final int PROVIDED_KEY_LENGTH = 64;
	static public final int SUB_KEY_LENGTH = 48;
	static public final int ITERATIONS = 16;
	private byte [] m_byteKey;
	private byte [][] m_byteCipherKeys = new byte[ITERATIONS][SUB_KEY_LENGTH];
	private int [][] intKeyPC1 = {
			                        {57,49,41,33,25,17,9},
			 	                    {1,	58,	50,	42,34,26,18},
			 	                    {10,2,59,51,43,35,27},
			 	                    {19,11,3,60,52,44,36},
			 	                    {63,55,47,39,31,23,15},
			 	                    {7,62,54,46,38,30,22},
			 	                    {14,6,61,53,45,37,29},
			 	                    {21,13,5,28,20,12,4}
	                             };   
	private int [][] intKeyPC2 = 
	{
			{14,17,11,24,1,5},
			{3,28,15,6,21,10},
			{23,19,12,4,26,8},
			{16,7,27,20,13,2},
			{41,52,31,37,47,55},
			{30,40,51,45,33,48},
			{44,49,39,56,34,53},
			{46,42,50,36,29,32}
	};
	private int[] intSubKeyRotation = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

	public KeyGenerator(byte[] bytes) 
	{
		setBaseKey( bytes );
	}

	public KeyGenerator() 
	{
		super();
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
		KeyGenerator gen = new KeyGenerator();
		gen.setBaseKey( "12345678".getBytes() );
		gen.generateKeys();

	}
    
   	public void setBaseKey ( byte[] byteKey )
   	{
   		m_byteKey = byteKey;
   	}
   	
   	public byte[] getKey()
   	{
   		return m_byteKey;
   	}
   	public DesBitSet[] generateKeys ()
   	{
   	    int intKeyLength = intKeyPC1.length * intKeyPC1[0].length;
   	    int intHalfKeyLength = intKeyPC1.length * intKeyPC1[0].length / 2;
   		BitSet bits = DesBitSet.bytes2BitSet( m_byteKey );
   	    BitSet bitsPermutated = new BitSet( intKeyLength );
   	    for ( int i=0;i<intKeyPC1.length;i++ )
   	    {
   	    	for (int j=0;j<intKeyPC1[0].length;j++ )
   	    	{
   	             int intNewPos = i * intKeyPC1[0].length + j;
        	     bitsPermutated.set ( intNewPos , bits.get( intKeyPC1 [i][j] - 1 ) );
   	    	}
   	    }
   	    
   	    DesBitSet keys[] = new DesBitSet[ ITERATIONS ];
   	 
   	    keys [0] =  new DesBitSet ( bitsPermutated, intKeyLength );
   	    DesBitSet current_key = keys[0];
   	    for (int i=0;i<keys.length;i++ )
   	    {
   	    	//System.out.println ( current_key + " | " + current_key.length() );
   	    	DesBitSet l = new DesBitSet ( current_key.get( 0, intHalfKeyLength  ) , intHalfKeyLength);
   	   	    DesBitSet r = new DesBitSet ( current_key.get( intHalfKeyLength, intKeyLength ) , intHalfKeyLength );

   	   	    //System.out.println( l +  " | " + l.length());
       	    //System.out.println( r +  " | " + r.length() );

   	   	    l.lrotate( intSubKeyRotation[i] );
            r.lrotate( intSubKeyRotation[i] );

   	   	    //System.out.println( l +  " | " + l.length());
       	    //System.out.println( r +  " | " + r.length() );

       	    current_key = l.append(r);
       	    int keyLength = intKeyPC2.length * intKeyPC2[0].length; 
       	    keys[i] = new DesBitSet ( new BitSet( keyLength ), keyLength );
       	    for (int j=0;  j < intKeyPC2.length ;j++)
       	    {
       	    	for (int k=0;  k < intKeyPC2[j].length ;k++)
       	    	{
       	    		int intNewPos = j * intKeyPC2[j].length + k;
       	    		keys[i].set(intNewPos, current_key.get ( intKeyPC2[j][k] - 1 )  );
       	    	}
       	    }
//       	    System.out.println( current_key + " | " + current_key.length() );
//       	    System.out.println( keys[i] + " | " + keys[i].length() );
//       	    System.out.println( "============================" );
   	    }
   	    
   		return keys;
   	}
}
