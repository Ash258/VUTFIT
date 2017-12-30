package ivs.ignis.math;

import com.tngtech.java.junit.dataprovider.DataProvider;
import com.tngtech.java.junit.dataprovider.DataProviderRunner;
import com.tngtech.java.junit.dataprovider.UseDataProvider;
import ivs.ignis.math.helpers.MathHelper;
import org.apfloat.Apfloat;
import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.assertEquals;

/**
 * @author Pavel Parma <pavelparma0@gmail.com>
 */
@RunWith(DataProviderRunner.class)
public class IgnisCalculatorTest {

    private IgnisCalculator calculator = IgnisCalculator.getInstance();

    @DataProvider
    public static Object[][] dataProviderCalculate() {
        return new Object[][] {
                {"1", new Apfloat(1)},
                {"3+2", new Apfloat(5)},
                {"3*2", new Apfloat(6)},
                {"3^3", new Apfloat(27)},
                {"9/3", new Apfloat(3)},
                {"2 + 3 * 4", new Apfloat(14)},
                {"(2 + 3) * 4", new Apfloat(20)},
                {"(2 + 3)^2 * 4", new Apfloat(100)},
                {"-(-2 + 3)^2 * 4", new Apfloat(-4)},
                {"-2^-2^2", new Apfloat(-0.0625)},
                {"-2^-2^-2", MathHelper.roundUp(new Apfloat("-0.84089641525371454303"))},
                {"5 - -3", new Apfloat(8)},
                {"10 - +--+-12", new Apfloat(22)},
                {"3!!", new Apfloat(720)}
        };
    }

    @Test
    @UseDataProvider("dataProviderCalculate")
    public void calculate(String text, Apfloat result) {
        assertEquals(result, this.calculator.calculate(text));
    }
}