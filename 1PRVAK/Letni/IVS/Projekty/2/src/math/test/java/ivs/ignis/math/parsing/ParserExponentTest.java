package ivs.ignis.math.parsing;

import ivs.ignis.math.tokenizing.Token;
import ivs.ignis.math.tokenizing.TokenType;
import org.apfloat.Apfloat;
import org.junit.Assert;
import org.junit.Test;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class ParserExponentTest extends ParserTestSuite {

    public static Token INT_2 = new Token(TokenType.INTEGER, "2", -1);

    @Test
    public void termOnly() throws Exception {
        tokenizer(INT_42);
        Assert.assertEquals(new Apfloat(42), parser.parseExponent());
    }

    @Test
    public void singleExponent() throws Exception {
        tokenizer(INT_42, POWER, INT_2);
        Assert.assertEquals(new Apfloat(1764), parser.parseExponent());
    }

    @Test
    public void complexExponent() throws Exception {
        tokenizer(INT_42, POWER, INT_2, POWER, INT_2);
        Assert.assertEquals(new Apfloat(3111696), parser.parseExponent());
    }
}
