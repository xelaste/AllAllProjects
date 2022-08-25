package xxxx;

public class Game24 {
	private static String[] templates = { "x1op1x2op2x3op3x4", "(x1op1x2)op2(x3op3x4)", "x1op1(x2op2x3op3x4)",
			"x1op1(x2op2(x3op3x4))", "x1op1((x2op2x3)op3x4)", "(x1op1x2op2x3)op3x4", "(x1op1(x2op2x3))op3x4",
			"((x1op1x2)op2x3)op3x4", };
	private static String ops[] = { "+", "-", "/", "*" };
	private static ExpressionEvaluator evaluator = new ExpressionEvaluator();

	private boolean play(int[] x) {
		for (String template : templates) {
			for (int i = 0; i < x.length; i++) {
				for (int j = 0; j < x.length; j++) {
					for (int k = 0; k < x.length; k++) {
						for (int l = 0; l < x.length; l++) {
							if (i != j && i != l && i != k && j!=k && j!=l && k!=l ) {
								String expr = template.replace("x1", String.valueOf(x[i]));
								expr = expr.replace("x2", String.valueOf(x[j]));
								expr = expr.replace("x3", String.valueOf(x[k]));
								expr = expr.replace("x4", String.valueOf(x[l]));
								if (calculate(expr)) {
									return true;
								}
							}
						}
					}
				}
			}
		}
		return false;
	}

	private boolean calculate(String template) {
		for (String op1 : ops) {
			for (String op2 : ops) {
				for (String op3 : ops) {
					String expr = template.replace("op1", op1);
					expr = expr.replace("op2", op2);
					expr = expr.replace("op3", op3);
					try {
						double val = evaluator.evaluate(expr);
						if (Math.abs(val - 24) < 0.00001) {
							System.out.println(expr);
							return true;
						}
					} catch (Exception e) {
						continue;
					}
				}
			}
		}
		return false;
	}

	public static void main(String[] args) {
		Game24 game = new Game24();
		game.play(new int[] { 4, 1, 8, 7 });
		game.play(new int[] { 2, 3, 4, 5 });
	}
}
