package operative;

public class Solution3 {
	public int solution(int[] A) 
	{
		if (A== null )
		{
			return 0;
		}
		if(A.length <= 2 ) {
			return A.length;
		}
		int first = A[0],second = A[1];
		int start = 0,maxLen = 0;
		for(int i=2;i<A.length;i++){
			if(i%2 == 0 && A[i] != first || i%2 == 1 && A[i] != second){
				maxLen = Math.max(maxLen,i - start);
				start = i-1;
				if(i%2 == 0){
					first = A[i];
					second = A[i-1];
				}else{
					first = A[i-1];
					second = A[i];
				}
			}
		}     
		return Math.max(maxLen,A.length - start);	 

	}

	public static void main(String[] args) 
	{
		//int A[] = {20,300,4,10,5};
		//int A[] = {7,-5,-5,-5,7,-1,7};
		int A[] = {7,4,-2,4,-2,-9};
		Solution3 sol  = new Solution3();
		System.out.println(sol.solution(A));

	}
}
