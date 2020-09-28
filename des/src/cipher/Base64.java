package cipher;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.IntStream;


public class Base64 {

	public final static Map<Character,Integer> mapFromBase64 = new HashMap<>();
	public final static char toBase64[]=
		{'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
		 '0','1','2','3','4','5','6','7','8','9', '+','/'
		};
	static
	{
		 IntStream.range(0, toBase64.length).forEach(idx->mapFromBase64.put(toBase64[idx], idx ));
	}

	private byte toBase64 (int src)
	{
		return (byte) toBase64[src];
	}
	public byte[] encode(byte input[])
	{
		
		int length =  4 * ((input.length / 3) + (input.length % 3 > 0 ? 1 : 0)) ;
		byte[] result = new byte[length];
		for (int i=0,k=0;i<input.length;i+=3,k+=4)
		{
			int b1 = (input[i] & 0xff) >> 2;
			int b2 = (input[i] & 0x03)<<4; 
			int b3 = -1;
			int b4 = -1;
			if (i+1 < input.length)
			{	
				b2 |= ( input[i+1] & 0xff)>>4;
				b3 = ( input[i+1] & 0x0f ) << 2;
			}
			if (i+2 < input.length)
			{	
				b3 |= ( input[i+2] & 0xc0)>>6;
				b4 = input[i+2] & 0x3f;
			}
			result[k]=toBase64(b1);
			result[k+1]=toBase64(b2);
			if (b3<0)
			{
				result[k+2]='=';
			}
			else
			{	
				result[k+2]=toBase64(b3);
			}

			if (b4<0)
			{
				result[k+3]='=';
			}
			else
			{	
				result[k+3]=toBase64(b4);
			}
		}
		return result;
	}

	public byte[] decode(byte input[])
	{
		
		int padding = 0;
		if ('='==(input[input.length - 1]))
		{
			padding++;
		}
		if ('='==(input[input.length - 2]))
		{
			padding++;
		}
		int length = ( 3 * input.length/4 ) - padding;
		byte[] result = new byte[length];
		for (int i=0,k=0;i<input.length-4;i+=4,k+=3)
		{
			int n1 = mapFromBase64.get(Character.valueOf((char)input[i])); 
			int n2 = mapFromBase64.get(Character.valueOf((char)input[i + 1]));
			int n3 = input[i + 2] != '=' ? mapFromBase64.get(Character.valueOf((char)input[i + 2])):-1;
			int n4 = input[i + 3] != '=' ? mapFromBase64.get(Character.valueOf((char)input[i + 3])):-1;
			result[k]= (byte)( (n1<<2) | (n2  >> 4) );
			result[k+1]= (byte ) ( (n2 & 0x0f) << 4);
			if ( n3 != -1 )
			{
				result[k+1]+=(n3>>2);
				result[k+2]= (byte) ((n3 & 0x03)<<6);
			}
			if ( n4 != -1 )
			{
				result[k+2]+=n4;
			}
		}
		return result;
	}


	public static void main(String[] args) 
	{
		byte[] data = {2,4,8,16,32,-128,10,12};
	    data=" ".getBytes();
		System.out.println(new String(data));
		Base64 encoder = new Base64();
		long t1 = System.nanoTime();
		for (int i=0;i<10000;i++)
		{
			java.util.Base64.getEncoder().encode(data);
		}
		System.out.println(System.nanoTime() - t1);
		t1 = System.nanoTime();
		for (int i=0;i<10000;i++)
		{
			encoder.encode(data);
		}
		System.out.println("==========================");
		System.out.println(System.nanoTime() - t1);

		String s1 = new String(java.util.Base64.getEncoder().encode(data));
		System.out.println(s1);
		String s2 = new String(encoder.encode(data));
		System.out.println(s2);
		System.out.println(s2.equals(s1));

		t1 = System.nanoTime();
		for (int i=0;i<10000;i++)
		{
			java.util.Base64.getDecoder().decode(s2.getBytes());
		}
		System.out.println(System.nanoTime() - t1);

		t1 = System.nanoTime();
		for (int i=0;i<10000;i++)
		{
			encoder.decode(s2.getBytes());
		}
		System.out.println("==========================");
		System.out.println(System.nanoTime() - t1);
		
		String s3 = new String(encoder.decode(s2.getBytes()));
		String s4 = new String(java.util.Base64.getDecoder().decode(s2.getBytes()));
		System.out.println("\""+ s3 + "\"");
		System.out.println("\""+ s4 + "\"");
	}

}
