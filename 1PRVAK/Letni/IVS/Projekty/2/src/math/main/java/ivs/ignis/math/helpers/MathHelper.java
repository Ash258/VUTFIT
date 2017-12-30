package ivs.ignis.math.helpers;

import org.apfloat.Apfloat;
import org.apfloat.ApfloatMath;

import java.math.RoundingMode;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class MathHelper {

    public static long PRECISION_ROUND_UP = 20;
    public static long PRECISION          = 21;

    private static Apfloat ZERO = Apfloat.ZERO;

    private static Apfloat ONE  = Apfloat.ONE;

    private MathHelper() {}

    public static Apfloat roundUp(Apfloat apfloat) {
        apfloat = ApfloatMath.round(apfloat, MathHelper.PRECISION_ROUND_UP, RoundingMode.HALF_UP);
        return apfloat.precision(MathHelper.PRECISION);
    }

    /**
     * F(n) = n * F(n - 1).
     */
    public static Apfloat factorial(Apfloat number, long precision) {
        if (number.compareTo(ZERO) < 0) { throw new IllegalArgumentException("Factorial of negative number!"); }

        Apfloat first = ONE;
        for (Apfloat i = ONE; number.compareTo(i) >= 0; i = i.add(ONE)) {
            first = first.multiply(i).precision(precision);
        }

        return first;
    }

    /**
     * F(n+2) = F(n+1) + F(n).
     */
    public static Apfloat fibonacci(Apfloat number, long precision) {
        Apfloat res  = ZERO;
        Apfloat tmp1 = ONE;

        for (Apfloat i = ONE; number.compareTo(i) >= 0; i = i.add(ONE)) {
            Apfloat tmp = res.add(tmp1).precision(precision);
            res = tmp1;
            tmp1 = tmp;
        }

        return res;
    }
}
