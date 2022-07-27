package xxxx;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

import static xxxx.ProbabilityStudentClub.States.*;

public class ProbabilityStudentClub {
    public static void main(String[] args) {

        Map<States,States[]> mapTransition55= new HashMap<> ();
        Map<States,States[]> mapTransition56= new HashMap<> ();

        States states[] = null;
        // Start
        states = new States[] {Start, Start, Start,Start,Half,Start};
        mapTransition55.put(Start,states);
        mapTransition56.put(Start,states);
        states = new States[] {Start,Start,Start,Start,Win,Start};
        mapTransition55.put(Half,states);
        states = new States[] {Start,Start,Start,Start,Half,Win};
        mapTransition56.put(Half,states);
        int samples=100000000;
        double p55=0;
        for (int i=0;i<samples;i++)
        {
            States state = Start;
            int count55=0;
            Random rand = new Random();
            while (state != Win)
            {
                int result = rand.nextInt(6);
                state = mapTransition55.get(state)[result];
                //System.out.print(result+ " ");
                count55++;
            }
            //System.out.println();
            //System.out.println(count55);
            p55 += count55;
        }
        double p56=0;
        for (int i=0;i<samples;i++)
        {
            States state = Start;
            Random rand = new Random();
            int count56 =0;
            while (state != Win)
            {
                int result = rand.nextInt(6);
                state = mapTransition56.get(state)[result];
                count56 ++;
            }
            p56 += count56;
        }
        int[] results = new int[samples];
        Random rand = new Random();
        for (int i=0;i<samples;i++)
        {
            int result = rand.nextInt(6) + 1;
            results[i]=result;
        }
        int _55=0;
        int _56=0;
        int _556=0;
        for (int i=0;i<samples-3;i++)
        {
            int x = results[i];
            int y = results[i+1];
            int z = results[i+2];
            if (x==5 && y==5)
            {
                _55++;
                if (z==6)
                {
                    _556++;
                }
            }
            if (x==5 && y==6)
            {
                _56++;
            }
        }
        System.out.println("**********************************");
        System.out.println((1.0 * _55)/samples);
        System.out.println(1.0 * (_56 + _556)/samples);
        System.out.println("**********************************");

        System.out.println(p55/samples);
        System.out.println(p56/samples);
    }
public static enum States {Start,Half,Win};
}
