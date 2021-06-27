package operative;

public class Solution1 {
	public int solution(int[] A) {
		if ( A==null || A.length == 0)
		{
			return 0;
		}
		int sum = 0;
		int maxLamp = -1;
        for (int i=0 ; i < A.length; i++ )
        {
        	int lamp = A[i];
        	if (lamp > maxLamp )
        	{
        		maxLamp = lamp;
        	}
        	if (i+1 == maxLamp)
        	{
        		sum++;
        	}
        }
        return sum;
    }
	
	public static void main(String[] args) 
	{
		int A[] = {2,3,4,1,5};
		Solution1 sol  = new Solution1();
		System.out.println(sol.solution(A));
	}
}
