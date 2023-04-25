package xxxx;

public class ClockwiseMatrix {
    private static int[][] matrix= {{1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15},
            {16, 17, 18, 19, 20} };
    int [] directions = {0,1,2,3}; // 0 top , 1 -right, , 2- bottom , 3  - left
    public static void main(String[] args) {
        ClockwiseMatrix clockwiseMatrix = new ClockwiseMatrix();
        clockwiseMatrix.solution(matrix);
    }
    private void solution(int[][] matrix) {
        int width = matrix[0].length;
        int height = matrix.length;
        int topY = 0 , topS = 0, topE= width - 1;
        int leftX= topE, leftS = topY + 1 , leftE= height -1;
        int downY= leftE, downS = topE - 1 , downE= topS;
        int rightX= downE, rightS = downY - 1 , rightE= topY+1;
        int currentDirection = 0;
        int count = 0;
        while (count<width*height){
            switch (currentDirection) {
                case 0:
                    for (int i= topS;i<=topE;i++ )
                    {
                        System.out.print(matrix[topY][i] + " ");
                        count++;
                    }
                    topY++;
                    topS++;
                    topE--;
                    break;
                case 1:
                    for (int j=leftS;j<=leftE;j++ )
                    {
                        System.out.print(matrix[j][leftX] + " ");
                        count++;
                    }
                    leftX--;
                    leftS = topY + 1;
                    leftE--;
                    break;
                case 2:
                    for (int i = downS ; i >= downE;i--)
                    {
                        System.out.print(matrix[downY][i] + " ");
                        count++;
                    }
                    downY--;
                    downE++;
                    downS--;
                    break;
                case 3:
                    for(int j=rightS;j>=rightE;j--) {
                        System.out.print(matrix[j][rightX] + " ");
                        count++;
                    }
                    rightX++;
                    rightS++;
                    rightE--;
                break;
            }
            currentDirection = (currentDirection + 1) % directions.length;
        }

    }
}
