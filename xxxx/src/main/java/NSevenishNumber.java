public class NSevenishNumber {
    public static void main(String[] args) {
        NSevenishNumber calc = new NSevenishNumber();
        for (int i=1;i<=20;i++)
        {
            System.out.println(i + " " + calc.nsevenish(i));
        }
    }
    public long nsevenish(int n)
    {
        int num = n;
        long result = 0;
        int factor = 1;
        while (num > 0 )
        {
            result +=  factor * (1 & num);
            num>>=1;
            factor  *= 7;
        }
        return result;
    }

}
