package ivs.ignis.math.parsing;

import com.tngtech.java.junit.dataprovider.DataProvider;
import com.tngtech.java.junit.dataprovider.DataProviderRunner;
import com.tngtech.java.junit.dataprovider.UseDataProvider;
import ivs.ignis.math.helpers.MathHelper;
import org.apfloat.Apfloat;
import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
@RunWith(DataProviderRunner.class)
public class MathHelperTest {

    public static final int PRECISION = 31;

    @DataProvider
    public static Object[][] dataFactorial() {
        return new Object[][] {
                {1, "1"},
                {2, "2"},
                {3, "6"},
                {4, "24"},
                {5, "120"},
                {6, "720"},
                {7, "5040"},
                {100, "9.332621544394415268169923885615e157"},
                {3628800, "9.051993835479934590662232550906e22228103"}
        };
    }

    @DataProvider
    public static Object[][] dataFibonacci() {
        return new Object[][] {
                {0, "0"},
                {1, "1"},
                {2, "1"},
                {3, "2"},
                {4, "3"},
                {5, "5"},
                {6, "8"},
                {7, "13"},
                {8, "21"},
                {100, "354224848179261915075"},
                {300, "2222322446294204455297398934615e32"},
                {3628800, "9.987438559818673901874346336999e758373"}
        };
    }

    @Test
    @UseDataProvider("dataFactorial")
    public void factorial(long actual, String expected) throws Exception {
        Apfloat factorial = MathHelper.factorial(new Apfloat(actual), PRECISION);
        Assert.assertEquals(new Apfloat(expected), factorial);
    }

    @Test
    @UseDataProvider("dataFibonacci")
    public void fibonacci(long actual, String expected) throws Exception {
        Apfloat factorial = MathHelper.fibonacci(new Apfloat(actual), PRECISION);
        Assert.assertEquals(new Apfloat(expected), factorial);
    }
}