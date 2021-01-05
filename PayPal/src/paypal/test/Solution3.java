package paypal.test;

public class Solution3 
{
	private int[][] dp;
	public int solution(int N, int K) 
	{
		if (N<=0)
		{
			return 0; 
		}
		if (K<0)
		{
			return 0;
		}
		
		dp = new  int[N+1][K+1];
		for (int i = 0; i < dp.length; i++) 
		{
			for (int j = 0; j < dp[i].length; j++) 
			{
				dp[i][j] = Integer.MAX_VALUE;
				if (i==0)
				{
					dp[i][j]=0;
				}
				if (j==0)
				{
					dp[i][j]=N-1;
				}
				
			}
			
		}
		
		return round (N,K,1); 
		
		
	}
	private int round (int currN,int currentK,int numberOfChips)
	{
		if (currN<=0 )
		{
			return 0;
		}

        if (currentK == 0)
        {
            return currN - 1;
        }

        
		if (dp[currN][currentK]<Integer.MAX_VALUE)
		{
			return dp[currN][currentK];
		}
		
		
		
        int res1 =  round(currN - numberOfChips ,currentK-1, numberOfChips * 2 );
		int res2 =  currentK >0 ? round(currN - 1,currentK,numberOfChips + 1 ):Integer.MAX_VALUE;
		if (res1 < res2 )
		{
			dp[currN][currentK] = res1 + 1;
		}
		else
		{
			dp[currN][currentK] = res2 + 1;
		}
		return dp[currN][currentK];
	}
	
	public static void main(String[] args) 
	{
		 Solution3 sol = new Solution3();
		 int result = sol.solution(18, 2);
	}
}
