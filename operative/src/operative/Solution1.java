package operative;

import java.util.HashSet;
import java.util.Set;

public class Solution1 {

	
	
	public int solution(int[] A) {
		if ( A==null || A.length == 0)
		{
			return 0;
		}
		int sum = 0;
		Set <Integer> lampsOnSet = new HashSet<>();
        for (int i=0 ; i < A.length; i++ )
        {
        	int lamp = A[i];
        	lampsOnSet.add(lamp);
        	if (lamp > i+1)
        	{
        		continue;
        	}
        	boolean allShine = true;
        	for (int j=1;j<lamp && allShine;j++)
        	{
        		allShine = lampsOnSet.contains(j);
        	}
        	if (allShine)
        	{
        		sum++;
        	}
        }
        return sum;
    }
	
	public static void main(String[] args) 
	{
		int A[] = {20,300,4,10,5};
		Solution1 sol  = new Solution1();
		System.out.println(sol.solution(A));
	}
}
