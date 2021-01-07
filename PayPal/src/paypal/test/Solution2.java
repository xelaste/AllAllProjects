package paypal.test;

public class Solution2 
{
	    public int solution(int A, int B) {
	       long result = (long) A * (long)B;
	       int count=0;
	       while ( result > 0 )
	       {
	           count += result & 0x1;
	           result>>=1;
	       }
	       return count;
	    }
}

