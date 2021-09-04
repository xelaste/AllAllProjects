import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.io.StringWriter;
import java.util.StringTokenizer;

public class Overload extends Parent implements Serializable
{
	static final long serialVersionUID = -485682040073170817L;
	int x = 0;
	public static void main (String[] args)
	{
		
		int s = 64 / 9 ;
		float f = 64 / 9 ;
		double d = 64 / 9d ;
		
		System.out.println ( s + " & " + f + " & " + d ) ;
		
		
		long t11 = System.currentTimeMillis();
		System.out.println("t11=" + t11);
		
		
		for (int i=0;i<1000;i++) {
			try {
				Overload  o3 = new Overload();
				StringBuffer  bf1 = serialize (o3);
				String strResult1 = bf1.toString();
				Overload o2= ( Overload ) deSerialize(strResult1);
			}
			catch (Exception e)
			{
				
			}
		}  
		long t12 = System.currentTimeMillis();
		System.out.println("t12=" + t12);
		System.out.println("Kosta " + ( t12-t11 ) );
		
		
		Overload o = new Overload ();
		long t1 = System.currentTimeMillis();
		System.out.println("t1_=" + t1);
		
		for (int k=0;k<1000;k++ ) 
		{
			ByteArrayOutputStream  baos = new ByteArrayOutputStream ();
			byte [] result = null ;
			try {
				ObjectOutputStream os = new ObjectOutputStream ( baos );
				os.writeObject( o );
				os.flush();
				result = baos.toByteArray();
			}
			catch ( Exception e )
			{
				e.printStackTrace();
			}
			
			StringBuffer bf = new StringBuffer( result.length * 2 );
			for (int i=0; result !=null && i < result.length ; i++ )
			{
				byte b = result[i];
				bf.append ( b );
				if ( i < result.length -1 )
					bf.append ( ";" );
			}
			String strResult = bf.toString();
			
			String strBytes[] = strResult.split(";");
			byte[] back = new byte [ strBytes.length ];
			for ( int j=0;j<back.length; j++ )
			{
				byte b = Integer.valueOf( strBytes[j] ).byteValue();
				back[j]  = b;
			}
			
			Overload o1;
			try {
				ByteArrayInputStream bais = new ByteArrayInputStream ( back ); 
				ObjectInputStream is = new ObjectInputStream ( bais );
				o1 = (Overload) is.readObject();
			}
			catch ( Exception e )
			{
				e.printStackTrace();
			}
		} 
		long t2 = System.currentTimeMillis();
		System.out.println("t1_=" + t1);
		System.out.println("t2_=" + t2);
		System.out.println("My" + ( t2-t1 ));
		
		
	}
     
	  public static Serializable deSerialize(String serializedVo)throws IOException,
	  ClassNotFoundException{
	    Serializable ret = null;

	    char[] cr = serializedVo.toCharArray();
	    byte[] nbytes = new byte[cr.length/2];
	    for(int i = 0, cri = 0; i < nbytes.length; i++, cri+=2 ){
	      nbytes[i] = (byte)((cr[cri] - 'A')<<4 | (cr[cri+1] - 'A'));
	    }

	    ObjectInputStream in = new ObjectInputStream(new ByteArrayInputStream(nbytes));

	    ret = (Serializable) in.readObject();
	    in.close();
	    return ret;
	  }
  
	
	public static StringBuffer serialize(Serializable vo) throws IOException
	  {
	    ByteArrayOutputStream baos = new ByteArrayOutputStream();
	    ObjectOutputStream oos = new ObjectOutputStream(baos);
	    oos.writeObject(vo);
	    oos.flush();
	    byte[] bytes = baos.toByteArray();
	    StringBuffer sb = new StringBuffer(bytes.length * 2);
	    for(int i = 0; i < bytes.length; i++)
	    {
	      sb.append( (char)('A' + ( (bytes[i]&255) >> 4)) );
	      sb.append( (char)('A' + (bytes[i] & 0xF)) );
	    }
	    return sb;
	  }

public Overload() {
		doSomething ( null );
}

public void doSomething ( Object s )
{
	System.out.println( "Object" );
}

public void doSomething ( String s )
{
	//System.out.println( "String" );
	//System.out.println( str );
}
public int getX()
{
	return x;
}
}

abstract class  Parent {
	protected String str="aa";
	public Parent() {
		InterfaceParent.aa aa = new InterfaceParent.aa(); 
		aa.x++;
	}

	abstract public void doSomething ( String s );
	abstract public void doSomething ( Object s );
}


interface InterfaceChild extends InterfaceParent  
{
  int i=2;
}

interface InterfaceParent
{
  int i=0;
  public class aa implements InterfaceParent
  {
    int x = i;
  }

}
