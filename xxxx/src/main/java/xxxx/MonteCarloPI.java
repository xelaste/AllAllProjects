
package xxxx;

public class MonteCarloPI {
    public static void main(String[] args) {
        int inside = 0;
        int n=10000000;
        for (int i=0;i<n;i++ )
        {
            double x = Math.random();
            double y = Math.random();
            if ( (x*x) + (y*y) <=1 )
            {
                inside++;
            }
        }
        System.out.println(4.0 * inside/n);
    }
}
