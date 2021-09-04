import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Properties;


public class PropertiesTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception 
	{
		// TODO Auto-generated method stub
        Properties p = new Properties();
        p.setProperty("b", "a" );
        p.setProperty("d", "b" );
        p.setProperty("c", "c" );
        p.setProperty("a", "d" );
        OutputStream os = new FileOutputStream("xx");
        p.store(os, " new properties " );
        os.close();
        InputStream is = new FileInputStream ( "xx" );
        p.load( is );
        is.close();
        p.setProperty("d", "xyz" );
        os = new FileOutputStream("xx");
        p.store(os," updated properties" );
        os.close();
        
	}

}
