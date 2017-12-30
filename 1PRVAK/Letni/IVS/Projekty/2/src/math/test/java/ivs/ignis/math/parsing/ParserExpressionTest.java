package ivs.ignis.math.parsing;

import ivs.ignis.math.tokenizing.Token;
import ivs.ignis.math.tokenizing.TokenType;
import org.apfloat.Apfloat;
import org.junit.Assert;
import org.junit.Test;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class ParserExpressionTest extends ParserTestSuite {

    public static Token INT_84 = new Token(TokenType.INTEGER, "84", -1);

    public static Token INT_21 = new Token(TokenType.INTEGER, "21", -1);

    @Test
    public void termOnly() throws Exception {
        tokenizer(INT_42);
        Assert.assertEquals(new Apfloat("42"), parser.parseExpression());
    }

    @Test
    public void simpleSubtract() throws Exception {
        tokenizer(INT_84, MINUS, INT_42);
        Assert.assertEquals(new Apfloat("42"), parser.parseExpression());
    }

    @Test
    public void simpleAddition() throws Exception {
        tokenizer(INT_42, PLUS, INT_42);
        Assert.assertEquals(new Apfloat("84"), parser.parseExpression());
    }

    @Test
    public void complexSubtract() throws Exception {
        tokenizer(INT_84, MINUS, INT_42, MINUS, INT_21);
        Assert.assertEquals(new Apfloat("21"), parser.parseExpression());
    }

    @Test
    public void complexAddition() throws Exception {
        tokenizer(INT_21, PLUS, INT_21, PLUS, INT_42);
        Assert.assertEquals(new Apfloat("84"), parser.parseExpression());
    }
}