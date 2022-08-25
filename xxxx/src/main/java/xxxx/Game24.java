package xxxx;


public class Game24 {
	private static String ops[] = { "+", "-", "/", "*" };
	private boolean play(int[] x) {

		for (int i=0;i<4;i++) {
			for (int j=0;j<4;j++) {
				for (int k=0;k<4;k++) {
					boolean samePriority = (i< 2 && j < 2 && k <2 ) || (i>1  && j>1 && k>1 );
					if (evaluate(x, new String[] { ops[i], ops[j], ops[k] },samePriority)) {
						return true;
					}
				}
			}
		}
		return false;
	}

	private boolean evaluate(int[] x, String[] operands,boolean samePriority) {
		for (int i = 0; i < x.length; i++) {
			for (int j = 0; j < x.length; j++) {
				for (int k = 0; k < x.length; k++) {
					for (int l = 0; l < x.length; l++) {
						if (i != j && i != l && i != k && j != k && j != l && k != l) {
							for (int t = 0; t < 5; t++) {
								try {
									double val = calculate(t, new int[] { x[i], x[j], x[k], x[l] }, operands);
									if (Math.abs(val - 24) < 0.00001) {
										return true;
									}
									if (samePriority)
									{
										break;
									}
								
								} catch (Exception e) {
									continue;
								}

							}
						}
					}
				}
			}
		}
		return false;
	}

	private float calculate(int templateId, int[] values, String[] ops) {

		switch (templateId) {
		case 0: // "(x1op1x2)op2(x3op3x4)"
		{
			float v1 = applyOperation(values[0], values[1], ops[0]);
			float v2 = applyOperation(values[2], values[3], ops[2]);
			return (applyOperation(v1, v2, ops[1]));
		}
		case 1: // "x1op1(x2op2(x3op3x4))":
		{
			float v1 = applyOperation(values[2], values[3], ops[2]);
			float v2 = applyOperation(values[1], v1, ops[1]);
			return applyOperation(values[0], v2, ops[0]);
		}
		case 2:// "x1op1((x2op2x3)op3x4)":
		{
			float v1 = applyOperation(values[1], values[2], ops[1]);
			float v2 = applyOperation(values[3], v1, ops[2]);
			return applyOperation(values[0], v2, ops[0]);

		}
		case 3:// "(x1op1(x2op2x3))op3x4":
		{
			float v1 = applyOperation(values[1], values[2], ops[1]);
			float v2 = applyOperation(values[0], v1, ops[0]);
			return applyOperation(values[3], v2, ops[2]);
		}
		case 4: // "((x1op1x2)op2x3)op3x4":
		{
			float v1 = applyOperation(values[0], values[1], ops[0]);
			float v2 = applyOperation(values[2], v1, ops[1]);
			return applyOperation(values[3], v2, ops[2]);
		}
		}
		return 0;
	}

	private float applyOperation(float a1, float a2, String operand) {
		switch (operand) {
		case "+":
			return a1 + a2;
		case "-":
			return a1 - a2;
		case "*":
			return a1 * a2;
		case "/":
			if (a2 != 0) {
				return a1 / a2;
			} else {
				throw new ArithmeticException();
			}
		}
		return Integer.MIN_VALUE;
	}

	public static void main(String[] args) {
		Game24 game = new Game24();
		Long ts = System.nanoTime();
		System.out.println(" [9,6,2,2]" + "  " + game.play(new int[] { 9,6,2,2 }));
		System.out.println(System.nanoTime() - ts );
		/*
		System.out.println("4, 1, 8, 7 " + game.play(new int[] { 4, 1, 8, 7 }));
		System.out.println("2, 3, 4, 5 " + game.play(new int[] { 2, 3, 4, 5 }));
		System.out.println("1, 2, 1, 2 " + game.play(new int[] { 1, 2, 1, 2 }));
		*/


	}
}
