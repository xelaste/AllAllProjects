package xxxx;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Shufle {
    public static void main(String[] args) {
        List<Integer> arr = new ArrayList<>();
        for (int i=0;i <40;i++)
        {
            arr.add(i);
        }
        System.out.println( String.join(",",arr.stream().map(String::valueOf).toList()));

        Random randomNum = new Random();
        for (int i=1;i <40;i++)
        {
            int idx = randomNum. nextInt(i);
            int val = arr.get(idx);
            arr.set(idx,arr.get(i));
            arr.set(i,val);
        }
        System.out.println( String.join(",",arr.stream().map(String::valueOf).toList()));

    }


}
