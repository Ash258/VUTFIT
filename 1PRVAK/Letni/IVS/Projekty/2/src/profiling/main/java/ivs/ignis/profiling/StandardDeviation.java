package ivs.ignis.profiling;

import ivs.ignis.math.helpers.MathHelper;
import org.apfloat.Apfloat;
import org.apfloat.ApfloatMath;

import java.util.List;

/**
 * @author Pavel Parma <pavelparma0@gmail.com>
 */
public class StandardDeviation {

    /**
     * @param values List of values to calculate upon
     * @return standard deviation of given values
     */
    public Apfloat calculate(List<Apfloat> values) {
        Apfloat sum = Apfloat.ZERO, squareSum = Apfloat.ZERO;
        for(Apfloat value : values) {
            sum = sum.add(value);
            squareSum = squareSum.add(value.multiply(value));
        }

        Apfloat size = new Apfloat(values.size());
        Apfloat mean = sum.precision(MathHelper.PRECISION).divide(size);
        Apfloat dividend = squareSum.subtract(mean.multiply(mean).multiply(size));

        return ApfloatMath.sqrt(dividend.divide(size.subtract(Apfloat.ONE)).precision(MathHelper.PRECISION));
    }

}
