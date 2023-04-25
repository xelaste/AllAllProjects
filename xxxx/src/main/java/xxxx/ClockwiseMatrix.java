package xxxx;

import java.util.ArrayList;
import java.util.List;

public class ClockwiseMatrix {
    private static int[][] matrix=

           // {{1, 2, 3, 4},{ 5 ,6 ,7 ,8 },{9, 10, 11, 12},{ 13, 14, 15, 16}};

           // {{22, 20, 29, 17} ,{6, 21, 13, 19}, {17, 11, 3, 5}, {29, 27 ,16, 21}, {10, 11, 21, 7}}
            {{27, 29, 4 ,15, 29},{ 25, 30, 20, 3 ,16},{ 26, 4, 4, 14, 28},{ 5, 24, 9, 1, 19},{ 19, 1, 27, 9, 12}}
            //{ {9 ,1 ,9 ,8}, {18, 9, 14 ,19} ,{14, 18, 22, 1}, {18, 14, 5 ,30} ,{27 ,6 ,22, 21}}
            ;
            /*
            {{1, 2, 3, 4, 5},
            {6, 7, 8, 9, 10},
            {11, 12, 13, 14, 15},
            {16, 17, 18, 19, 20} };
    */

    int [] directions = {0,1,2,3}; // 0 top , 1 -right, , 2- bottom , 3  - left

    public static void main(String[] args) {
        ClockwiseMatrix clockwiseMatrix = new ClockwiseMatrix();
        clockwiseMatrix.solution(matrix,matrix.length,matrix[0].length);
    }
    private ArrayList<Integer> solution(int[][] matrix,int r,int c) {
        int width =c;
        int height = r;
        int topY = 0 , topS = 0, topE= width - 1;
        int leftX= topE, leftS = topY + 1 , leftE= height -1;
        int downY= leftE, downS = topE - 1 , downE= topS;
        int rightX= downE, rightS = downY - 1 , rightE= topY+1;
        int currentDirection = 0;
        int count = 0;
        ArrayList<Integer> result = new ArrayList<>();
        while (count<width*height){
            switch (currentDirection) {
                case 0:
                    for (int i= topS;i<=topE;i++ )
                    {
                        System.out.print(matrix[topY][i] + " ");
                        result.add(matrix[topY][i]);
                        count++;
                        if (count>=width*height)
                        {
                            break;
                        }
                    }
                    topY++;
                    topS++;
                    topE--;
                    break;
                case 1:
                    for (int j=leftS;j<=leftE;j++ )
                    {
                        System.out.print(matrix[j][leftX] + " ");
                        result.add(matrix[j][leftX]);
                        count++;
                        if (count>=width*height)
                        {
                            break;
                        }
                    }
                    leftX--;
                    leftS = topY + 1;
                    leftE--;
                    break;
                case 2:
                    for (int i = downS ; i >= downE;i--)
                    {
                        System.out.print(matrix[downY][i] + " ");
                        result.add(matrix[downY][i]);
                        count++;
                        if (count>=width*height)
                        {
                            break;
                        }
                    }
                    downY--;
                    downE++;
                    downS--;
                    break;
                case 3:
                    for(int j=rightS;j>=rightE;j--) {
                        System.out.print(matrix[j][rightX] + " ");
                        result.add(matrix[j][rightX]);
                        count++;
                        if (count>=width*height)
                        {
                            break;
                        }
                    }
                    rightX++;
                    rightS--;
                    rightE++;
                break;
            }
            currentDirection = (currentDirection + 1) % directions.length;
        }
        return result;
    }
}
