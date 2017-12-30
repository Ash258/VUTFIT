package ivs.ignis.math.parsing;

import org.apfloat.Apfloat;
import org.junit.Assert;
import org.junit.Test;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class ParserUnaryTest extends ParserTestSuite {

    @Test
    public void plus() throws Exception {
        tokenizer(PLUS, INT_42);
        Assert.assertEquals(new Apfloat(42), parser.parseUnary());
    }

    @Test
    public void minus() throws Exception {
        tokenizer(MINUS, INT_42);
        Assert.assertEquals(new Apfloat(-42), parser.parseUnary());
    }

    @Test
    public void messy() throws Exception {
        tokenizer(PLUS, PLUS, MINUS, MINUS, PLUS, MINUS, PLUS, PLUS, PLUS, MINUS, INT_42);
        Assert.assertEquals(new Apfloat(42), parser.parseUnary());
    }
}
