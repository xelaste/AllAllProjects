	import static com.sun.PkgAccess.*;
public class PkgAccess2 
{

}
class Synapse {
   protected int gap() { return 7; }
 }

class Creb extends Synapse 
{
   // insert code here
	public int gap() { return Integer.getInteger("42"); }
}
