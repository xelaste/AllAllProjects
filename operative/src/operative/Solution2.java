package operative;

public class Solution2 {
	
	public void solution(int N) {
        int enable_print = 1 & (N % 10);
        while (N > 0) {
            if (enable_print == 0 && N % 10 != 0) {
                enable_print = 1;
            }
            if (enable_print == 1) {
                System.out.print(N % 10);
            }
            N = N / 10;
        }
    }

public static void main(String[] args) {
	Solution2 sol  = new Solution2();
	sol.solution(10000230);
}

}
