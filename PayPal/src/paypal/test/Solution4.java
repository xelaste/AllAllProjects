package paypal.test;


public class Solution4 
{
	 private static final int MAX_VALUE=1000000007;
	 
	 int[][] dp;
	 public int solution(int[] A, int K, int L) 
	 {
		 if (A==null || K+L>A.length)
	     {
	    	 return -1;
	     }
		 dp = new int[A.length][A.length];
		 for (int i = 0; i < A.length; i++) 
		 {
			 for (int j = 0; j < A.length; j++) 
			 {
				 dp[i][j]=Integer.MIN_VALUE;
			 }
		 }
	     int sum = 0;
	     int firstInterval = K > L ? K:L;
	     int secondInterval = firstInterval == K ? L: K;
	     for(int i=0;i<A.length-(firstInterval+secondInterval);i++)
	     {
	    	 for (int j = i+firstInterval;j + secondInterval - 1 <A.length;j++ )
	    	 {
	    		 if (dp[i][j]==Integer.MIN_VALUE)
	    		 {	 
	    			 dp[i][j] = count(A,i,j,firstInterval,secondInterval);
	    		 }	 
	    		 if (dp[i][j] > sum)
	    		 {
	    			 sum = dp[i][j];
	    		 }
	    	 }
	     }
	     for(int i=0;i<A.length-(firstInterval+secondInterval);i++)
	     {
	    	 for (int j = i+secondInterval;j + firstInterval -1 <A.length;j++ )
	    	 {
	    		 if (dp[i][j]==Integer.MIN_VALUE)
	    		 {	 
	    			 dp[i][j] = count(A,i,j,secondInterval,firstInterval);
	    		 }	 
	    		 if (dp[i][j] > sum)
	    		 {
	    			 sum = dp[i][j];
	    		 }
	    	 }
	     }

	     
	     return sum;
	 }

	 int count (int[] A,int startK,int startL,int K,int L)
	 {
		 int sumA = 0;
		 int sumB = 0;
		 for (int i=startK;i<startK+K;i++)
		 {
			 long result = sumA + A[i]; 
			 sumA = (int) (result % MAX_VALUE); 
		 }
		 for (int i=startL;i<startL+L;i++)
		 {
			 long result = sumB + A[i]; 
			 sumB = (int) (result % MAX_VALUE); 
		 }
		 return sumA + sumB;
	 }
public static void main(String[] args) 
{
	Solution4 sol = new Solution4();
	System.out.println(sol.solution(new int[] {6, 1, 4, 6, 3, 2, 7, 4}, 2, 3));
}
}
