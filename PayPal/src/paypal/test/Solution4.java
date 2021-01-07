package paypal.test;
import java.util.Arrays;

public class Solution4 {
    private static final int MAX_VALUE = 1000000007;

    public int solution(int[] A, int K, int L) {
        if (A == null || K + L > A.length) {
            return -1;
        }
        long[] sumK = new long[A.length - K + 1];
        long[] sumL = new long[A.length - L + 1];
        Arrays.fill(sumK, Integer.MIN_VALUE);
        Arrays.fill(sumL, Integer.MIN_VALUE);

        int sum = 0;
        for (int i = 0; i < A.length - (K + L); i++) {

            if (sumK[i] == Integer.MIN_VALUE) {
                if (i == 0 || sumK[i - 1] == Integer.MIN_VALUE) {
                    sumK[i] = count(A, i, K);
                } else {
                    sumK[i] = (sumK[i - 1] - A[i - 1] + A[i + K - 1]) % MAX_VALUE;
                }
            }
            for (int j = i + K; j + L - 1 < A.length; j++) {
                if (sumL[j] == Integer.MIN_VALUE) {
                    if (j == 0 || sumL[j - 1] == Integer.MIN_VALUE) {
                        sumL[j] = count(A, j, L);
                    } else {
                        sumL[j] = (sumL[j - 1] - A[j - 1] + A[j + L - 1]) % MAX_VALUE;
                    }
                }
                long currentSum = (sumK[i] + sumL[j]) % MAX_VALUE;
                sum = sum < currentSum ? (int) currentSum : sum;
            }
        }
        for (int i = 0; i < A.length - (K + L); i++) {
            if (sumL[i] == Integer.MIN_VALUE) {
                if (i == 0 || sumL[i - 1] == Integer.MIN_VALUE) {
                    sumL[i] = count(A, i, L);
                } else {
                    sumL[i] = (sumL[i - 1] - A[i - 1] + A[i + L - 1]) % MAX_VALUE;
                }
            }
            for (int j = i + L; j + K - 1 < A.length; j++) {
                if (sumK[j] == Integer.MIN_VALUE) {
                    if (j == 0 || sumK[j - 1] == Integer.MIN_VALUE) {
                        sumK[j] = count(A, j, K);
                    } else {
                        sumK[j] = (sumK[j - 1] - A[j - 1] + A[j + K - 1]) % MAX_VALUE;
                    }
                }
                long currentSum = (sumL[i] + sumK[j]) % MAX_VALUE;
                sum = sum < currentSum ? (int) currentSum : sum;
            }
        }
        return sum;
    }

    int count(int[] A, int start, int size) {
        long sum = 0;
        for (int i = start; i < start + size; i++) {
            sum += A[i];
            sum %= MAX_VALUE;
        }
        return (int) sum;
    }

    public static void main(String[] args) {
        Solution4 sol = new Solution4();
        System.out.println(sol.solution(new int[]{6, 1, 4, 6, 3, 2, 7, 4}, 3, 2));
    }
}
