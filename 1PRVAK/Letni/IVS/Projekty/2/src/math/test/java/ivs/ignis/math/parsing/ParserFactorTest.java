package ivs.ignis.math.parsing;

import org.apfloat.Apfloat;
import org.junit.Assert;
import org.junit.Test;

import static ivs.ignis.math.helpers.MathHelper.roundUp;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class ParserFactorTest extends ParserTestSuite {

    @Test
    public void parseInt() throws Exception {
        tokenizer(INT_42);
        Assert.assertEquals(new Apfloat("42"), parser.parseFactor());
    }

    @Test
    public void parseDouble() throws Exception {
        tokenizer(DOUBLE_42);
        Assert.assertEquals(new Apfloat(42d), parser.parseFactor());
    }

    @Test
    public void parseParenthesis() throws Exception {
        tokenizer(OPEN_P, INT_42, CLOSED_P);
        Assert.assertEquals(new Apfloat("42"), parser.parseFactor());
    }

    @Test
    public void parseFactorial() throws Exception {
        tokenizer(INT_42, FACTORIAL);
        Assert.assertEquals(roundUp(new Apfloat("1.405006117752879898543142606244e51")), parser.parseFactor());
    }
}