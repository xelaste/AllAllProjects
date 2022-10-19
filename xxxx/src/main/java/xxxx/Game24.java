package xxxx;

public class Game24 {
    private static char operators[] = {'+', '-', '/', '*'};
    private static int[][] operatorsPermutation = new int[64][4];
    private static int[][] cardPermutation = new int[24][4];

    static {
        int row = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    boolean samePriority = (i < 2 && j < 2 && k < 2) || (i > 1 && j > 1 && k > 1);
                    operatorsPermutation[row][0] = i;
                    operatorsPermutation[row][1] = j;
                    operatorsPermutation[row][2] = k;
                    operatorsPermutation[row][3] = samePriority ? 1 : 0;
                    row++;
                }
            }
        }
        row = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    for (int l = 0; l < 4; l++) {
                        if (i != j && i != l && i != k && j != k && j != l && k != l) {
                            cardPermutation[row][0] = i;
                            cardPermutation[row][1] = j;
                            cardPermutation[row][2] = k;
                            cardPermutation[row][3] = l;
                            row++;
                        }
                    }
                }
            }
        }
    }


    private boolean play(int[] x) {

        for (int i = 0; i < operatorsPermutation.length; i++) {
            for (int j = 0; j < cardPermutation.length; j++) {
                int[] cards = {x[cardPermutation[j][0]], x[cardPermutation[j][1]], x[cardPermutation[j][2]], x[cardPermutation[j][3]]};
                char ops1 = operators[operatorsPermutation[i][0]];
                char ops2 = operators[operatorsPermutation[i][1]];
                char ops3 = operators[operatorsPermutation[i][2]];
                char[] ops = {ops1, ops2, ops3};
                boolean samePriority = operatorsPermutation[i][3] > 0;
                for (int t = 0; t < 5; t++) {
                    try {
                        double val = calculate(t, cards, ops);
                        if (Math.abs(val - 24) < 0.00001) {
                            return true;
                        }
                        if (samePriority) {
                            break;
                        }

                    } catch (Exception e) {
                        continue;
                    }
                }
            }
        }
        return false;
    }

    private float calculate(int templateId, int[] values, char[] ops) {

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

    private float applyOperation(float a1, float a2, char operator) {
        switch (operator) {
            case '+':
                return a1 + a2;
            case '-':
                return a1 - a2;
            case '*':
                return a1 * a2;
            case '/':
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
        Long ts = System.currentTimeMillis();
        for (int i = 0; i < 100; i++) {
            game.play(new int[]{4, 1, 8, 7});
            game.play(new int[]{1, 2, 1, 2});
            game.play(new int[]{1, 7, 4, 5});
        }
        System.out.println(System.currentTimeMillis() - ts);
        System.out.println("1,7,4,5 " + game.play(new int[]{1, 7, 4, 5}));
        System.out.println("4, 1, 8, 7 " + game.play(new int[]{4, 1, 8, 7}));
        System.out.println("2, 3, 4, 5 " + game.play(new int[]{2, 3, 4, 5}));
        System.out.println("1, 2, 1, 2 " + game.play(new int[]{1, 2, 1, 2}));


    }
}
