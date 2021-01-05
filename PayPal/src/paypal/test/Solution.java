package paypal.test;
import java.util.HashMap;
import java.util.Map;
public class Solution {
	public int solution(int[] A) 
	{
		if (A!=null && A.length>0)
		{
			Map<Integer,Integer> map = new HashMap<>();

			for (int j = 0; j < A.length; j++) {
				map.put(A[j],1);
			}

			for (int i = 1; i <= A.length+1; i++) 
			{
				if(map.get(i)==null )
				{
					return i;
				}
				
			}
		}
		return 0;
	}
public static void main(String[] args) 
{
	Solution sol = new Solution();
	sol.solution(new int[] {1,2,3});
}
}
