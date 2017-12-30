package ivs.ignis.math.parsing;

import ivs.ignis.math.helpers.MathHelper;
import ivs.ignis.math.parsing.exceptions.DivisionByZero;
import ivs.ignis.math.parsing.exceptions.FactorialOfDouble;
import ivs.ignis.math.parsing.exceptions.FactorialOfNegative;
import ivs.ignis.math.parsing.exceptions.RootOfNegative;
import org.apfloat.Apcomplex;
import org.apfloat.Apfloat;
import org.apfloat.ApfloatMath;

import java.util.Objects;

import static org.apfloat.Apfloat.ONE;
import static org.apfloat.Apfloat.ZERO;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class Validator {

    private static Apfloat TWO = ONE.add(ONE).precision(MathHelper.PRECISION);

    private static Validator ourInstance = new Validator();

    private Validator() {}

    public static Validator getInstance() {
        return ourInstance;
    }

    /**
     * Validate root (square root, cube root, ..) function by domain of function.
     *
     * @throws RootOfNegative if arguments does not corresponds with domain of function.
     */
    public void validateRoot(int position, Apfloat number, Apfloat exponent) {
        if (betweenZeroAndOne(exponent) && isInverseEven(exponent) && isNegative(number)) {
            throw new RootOfNegative(position);
        }
    }

    /**
     * Validate division.
     *
     * @throws DivisionByZero if factor is zero.
     */
    public void validateDivision(int position, Apfloat factor) {
        if (isZero(factor)) {
            throw new DivisionByZero(position);
        }
    }

    /**
     * Validate factorial function.
     *
     * @throws DivisionByZero    if argument is not a possitive number.
     * @throws FactorialOfDouble if argument is floating point number.
     */
    public void validateFactorial(int position, Apfloat argument) {
        if (isNegative(argument)) {
            throw new FactorialOfNegative(position);
        }
        if (!isInteger(argument)) {
            throw new FactorialOfDouble(position);
        }
    }

    private boolean isInteger(Apfloat apfloat) {
        return apfloat != null && Objects.equals(apfloat.truncate(), apfloat);
    }

    private boolean isNegative(Apfloat apfloat) {
        return apfloat != null && apfloat.compareTo(ZERO) < 0;
    }

    private boolean isZero(Apfloat apfloat) {
        return apfloat != null && apfloat.compareTo(ZERO) == 0;
    }

    private boolean betweenZeroAndOne(Apfloat apfloat) {
        return apfloat != null && apfloat.compareTo(ZERO) > 0 && apfloat.compareTo(ONE) < 0;
    }

    private boolean isInverseEven(Apfloat apfloat) {
        apfloat = MathHelper.roundUp(ApfloatMath.pow(apfloat, Apcomplex.ONE.negate()));
        apfloat = MathHelper.roundUp(apfloat.mod(TWO));
        return apfloat.compareTo(ZERO) == 0;
    }
}
