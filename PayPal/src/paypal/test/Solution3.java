package paypal.test;

public class Solution3 
{
	public int solution(int N, int K)
	{
		int n=N;
		int k=K;
		int rounds=0;
		System.out.println(n);
		while ( n>1 )
		{
			if (n % 2 == 0 && k>0)
			{
				n >>= 1;
				k--;
			}
			else
			{
				n--;
			}
			System.out.println(n);
			rounds++;
		}
		return rounds;
	}

	public static void main(String[] args) 
	{
		 Solution3 sol = new Solution3();
		 int result = sol.solution(1024*1024*1024 * 2 - 1, 100);
		 //int result = sol.solution(8, 0);
		 System.out.println(result);
		 result = sol.solution(32, 4);
		 System.out.println(result);
	}
}
