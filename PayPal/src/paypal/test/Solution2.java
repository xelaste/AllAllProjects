package paypal.test;

public class Solution2 
{
	    public int solution(int A, int B) {
	       Long result = (long) (A * B);
	       int count=0;
	       while (result > 0 )
	       {
	           count += result & 0x1;
	           result = result>>1;
	       }
	       return count;
	    }
}

