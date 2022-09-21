package xxxx;
	import java.util.*;

	class Solution {
	    public static int findJudge(int N, int[][] trust) {
	    	Boolean[] connections = new Boolean[N]; 
	    	int ans = 0;
	        for (int i=0;i<	trust.length;i++)
	        {
	        	for (int j=0;j<trust[i].length;j++)
	        	{
	        		int x1 = trust[i][0];
	        		int x2 = trust[i][1];
	        		connections[x1 - 1] = true;
	        		break;
	        	}
	        }
	       for (int i = 0; i < connections.length; i++) {
	    	   if (!connections[i])
	    	   {
	    		   ans = i + 1;
	    	   }
	       }
	        return ans;
	    }
	}

	/**
	 * R E A D M E
	 * DO NOT CHANGE the code below, we use it to grade your submission.
	 * If changed your submission will be failed automatically.
	 **/
	public class Turing
	{  
	    public static void main(String args[])
	    {
	        Scanner sc = new Scanner(System.in);
	        
	        String N = sc.nextLine();

	        String[] components = sc.nextLine().split(",");
	        List<int[]> myList = new ArrayList<int[]>();

	        int size = components.length;
	        int[][] trust = new int[1][size];
	        int [] arr = new int [size];
	        for(int i=0; i<size; i++) {
	            String[] result = components[i].split(" ");
	            myList.add(new int[]{Integer.parseInt(result[0]),Integer.parseInt(result[1])});
	        }
	       
	        trust = myList.toArray(trust);
	        System.out.println(Solution.findJudge(Integer.parseInt(N), trust));
	    }
	}