package ivs.ignis.profiling;

import org.apfloat.Apfloat;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

/**
 * @author Pavel Parma <pavelparma0@gmail.com>
 */
public class Profiler {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        List<Apfloat> values = new ArrayList<>();
        while(sc.hasNextLine()) {
            //Expected tsv format, because none was defined in project description
            Arrays.stream(sc.nextLine().split("\t")).forEach(value -> values.add(new Apfloat(value)));
        }

        try {
            System.out.printf("Směrodatná odchylka je: %s", new StandardDeviation().calculate(values).toString(true));
        } catch (Exception e) {
            System.err.println("Při výpočtu došlo k chybě.");
        }
    }
}
