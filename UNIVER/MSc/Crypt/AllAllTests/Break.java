
public class Break {

	public Break() {
		super();
		// TODO Auto-generated constructor stub
	}
public static final void main (String args[])
{
	int i=0,count=100;
	label:
	for (int j=0;j<count;j++ ) 
	{
	for (i = 0; i < count; i++) {
		System.out.println(i);
		if ( (i+1) %2 == 0  )
			break label;
			
	}
	System.out.println("aaa");
	}
}
}
