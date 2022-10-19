package xxxx;

/**
 * Write an algorithm that finds the total number of set bits in all integers
 * between 1 and N.
 */
public class CountBits {
	public static void main(String[] args) {
		CountBits bitCounter = new CountBits();
		bitCounter.countBits(9);
		for (int i = 0; i < 32; i++) {
			System.out.println("" + i + " " + bitCounter.countBits(i));
		}

	}

	private int countBits(int n) {
		int counter = 0;
		int pos = 0;
		int period = 2;
		if (n == 0) {
			return counter;
		}
		do {
			int a = n / period;
			counter += (period / 2) * a;
			int b = 1 + (n % period);
			if (b > (period / 2)) {
				counter += b - (period / 2);
			}
			period <<= 1;
			pos++;
		} while (n >> pos > 0);
		return counter;
	}
}
