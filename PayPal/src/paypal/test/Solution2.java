package paypal.test;

public class Solution2 
{
	    public int solution(int A, int B) {
	       long result = (long) A * (long)B;
	       int count=0;
	       while ( result!=0 )
	       {
	           count += result & 0x1;
	           result=result>>>1;

	       }
	       return count;
	    }

	public static void main(String[] args)
	{
		Solution2 sol = new Solution2();
		//System.out.println(sol.solution(-1, 1));
		System.out.println(Long.bitCount(-1));

	}
}

