package cipher;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.StringBufferInputStream;
import java.io.StringReader;
import java.io.Writer;
import java.util.BitSet;

import javax.print.DocFlavor.BYTE_ARRAY;

import static util.DESInvariants.*;

import com.sun.org.apache.xerces.internal.impl.dv.util.Base64;

import util.DesBitSet;

public class Des {
    
	public static final int BLOCK_SIZE = 64;
	private DesBitSet[] m_keys = null;
	private boolean m_boolDecryptMode = false;

    /**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
		
		Des des = new Des();
		long t1 = System.currentTimeMillis();
		String encrypted = null;
		String decrypted = null;
		for ( int i=0;i<10000;i++ )
		{
	    
			ByteArrayInputStream is = new ByteArrayInputStream (  "12345678".getBytes() );
			ByteArrayOutputStream os = new ByteArrayOutputStream ();
			des.encrypt ( is ,os,"00000000" );
			encrypted = os.toString();
			Des decryptDes = new Des ( true );
			ByteArrayInputStream is1 = new ByteArrayInputStream (  encrypted.getBytes() );
			ByteArrayOutputStream os1 = new ByteArrayOutputStream ();
			decryptDes.encrypt( is1, os1, "00000000" );
			decrypted =   os1.toString();
		}
        
		System.out.println( ( System.currentTimeMillis() - t1 ) /  10000.0 );
        System.out.println( encrypted + "\n" + decrypted );
       	
	}

	public Des ()
	{
		setDecryptMode ( false );
	}
	
	public Des ( boolean boolMode )
	{
	     setDecryptMode ( boolMode );	
	}
	
	private void setDecryptMode ( boolean mode )
	{
		m_boolDecryptMode = mode;
	}
    
	private boolean isDecryptMode ()
	{
		return m_boolDecryptMode;
	}
	
	public void encrypt ( InputStream is, String key )
	{
		encrypt ( is, null, key );
	}

	
	public void encrypt ( InputStream is, OutputStream os , String key )
	{
		if ( os == null )
		{
			os = System.out;
		}
			
		byte [] block = new byte [BLOCK_SIZE / Byte.SIZE ];
		KeyGenerator kg = new KeyGenerator ( key.getBytes() );
		m_keys = kg.generateKeys();

	
		try {
			for ( int count = is.read( block ); count >0; count = is.read( block ) )
			{
			  if ( count * Byte.SIZE < BLOCK_SIZE )
			  {
				  for (int i=count ; i < block.length ;i++ )
					  block[i]=0;
			  }
			  byte[] encripted = encryptBlock( block );
			  os.write ( encripted );
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	protected byte[] encryptBlock ( byte[] input  )
    {
    	DesBitSet plainBitSet = DesBitSet.bytes2BitSet( input );
    	
    	DesBitSet workBitSet = new DesBitSet (  plainBitSet.paddedLength() );
    	int intSize = workBitSet.paddedLength();
    	int intLsize = intSize / 2;
    	int intRsize = intSize - intLsize; 
    	
    	for ( int i=0;i<IP.length;i++)
    		for (int j=0;j<IP[0].length;j++)
    		{
    			int pos = i * IP[0].length + j;
    			workBitSet.set( pos,  plainBitSet.get( IP[i][j] - 1 )  );
    		}
        
    	for (int i=0;i<m_keys.length;i++)
    	{
    		int key_idx = ( isDecryptMode() ? m_keys.length - ( i +1 ): i ); 
    		DesBitSet key = m_keys[ key_idx ];
   		    DesBitSet L = new DesBitSet ( workBitSet.get(0, intLsize ),intLsize );
    		DesBitSet R = new DesBitSet ( workBitSet.get(intLsize,intSize ),intRsize );
    		
            DesBitSet f_bitset = desFeistelFunction (R,key);
            
    		f_bitset.xor( L );
   			workBitSet = R.append (  f_bitset );
    	}
    	
	    DesBitSet L = new DesBitSet ( workBitSet.get(0, intLsize ),intLsize );
  		DesBitSet R = new DesBitSet ( workBitSet.get(intLsize,intSize ),intRsize );
  		workBitSet = R.append(L); 
  			
    	DesBitSet outputBitSet = new DesBitSet ( workBitSet.paddedLength() );
    	
    	for ( int i=0;i<IP_1.length;i++)
    		for (int j=0;j<IP_1[0].length;j++)
    		{
    			int pos = i * IP_1[0].length + j;
    			outputBitSet.set( pos,  workBitSet.get( IP_1[i][j] - 1 ) );
    		}
    		
    	return outputBitSet.bitSet2Bytes();
    }
   
protected DesBitSet desFeistelFunction ( DesBitSet R, DesBitSet key )
   {
	   DesBitSet R_1 = new DesBitSet ( key.paddedLength() );

	   for ( int i=0;i<E_BIT.length;i++ )
	   {
		   for (int j=0;j<E_BIT[0].length;j++)
		   {
		       int pos = i *  E_BIT[0].length + j;
		       R_1.set(pos,R.get( E_BIT[i][j] - 1 ) );
		   }
	   }
	   R_1.xor( key );
	   DesBitSet S_BOX_result= new DesBitSet ( 0 );
	   int B_size = R_1.paddedLength() / 8;
	   for (int i=0;i<8;i++ )
	   {
		   DesBitSet sixBytes =  new DesBitSet( R_1.get(i * B_size , ( i + 1 ) * B_size ), B_size );
		   byte[]  S_BOX_bits = new byte[1];
		   int y = ( sixBytes.get( 0 )?1:0 )  * 2  + ( sixBytes.get( 5 )?1:0 );
		   int x =( ( sixBytes.get( 1 )?1:0 )  << 3  )
		   	+ ( ( sixBytes.get( 2 )?1:0 ) << 2 ) 
		   	+ ( ( sixBytes.get( 3 )?1:0 ) << 1 )
		   	+ ( sixBytes.get( 4 )?1:0 );
		   
		   S_BOX_bits[0] = S_BOXES[i][y][x];
	       BitSet fourBits = DesBitSet.bytes2BitSet ( S_BOX_bits ).get(4,8);
	       S_BOX_result.append( new DesBitSet ( fourBits, 4 ));
	   }
	   DesBitSet permutatedS_BOX_result = new DesBitSet ( S_BOX_result.paddedLength() );
	   for ( int i =0;i<P_BOX.length; i++ )
	   {
		   for (int j=0;j<P_BOX[0].length;j++)
		   {
			 int pos = i *  P_BOX[0].length + j;
			 permutatedS_BOX_result.set( pos,S_BOX_result.get( P_BOX[i][j] - 1 ) );
		   }
	   }
	   
	   return permutatedS_BOX_result;
   }
}
