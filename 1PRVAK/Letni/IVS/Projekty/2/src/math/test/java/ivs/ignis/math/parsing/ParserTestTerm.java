package ivs.ignis.math.parsing;

import ivs.ignis.math.tokenizing.Token;
import ivs.ignis.math.tokenizing.TokenType;
import org.apfloat.Apfloat;
import org.junit.Assert;
import org.junit.Test;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class ParserTestTerm extends ParserTestSuite {

    public static Token INT_2 = new Token(TokenType.INTEGER, "2", -1);

    public static Token INT_3 = new Token(TokenType.INTEGER, "3", -1);

    public static Token INT_6 = new Token(TokenType.INTEGER, "6", -1);

    public static Token INT_7 = new Token(TokenType.INTEGER, "7", -1);

    @Test
    public void termOnly() throws Exception {
        tokenizer(INT_42);
        Assert.assertEquals(new Apfloat("42"), parser.parseTerm());
    }

    @Test
    public void simpleMul() throws Exception {
        tokenizer(INT_6, MULTIPLY, INT_7);
        Assert.assertEquals(new Apfloat("42"), parser.parseTerm());
    }

    @Test
    public void simpleDiv() throws Exception {
        tokenizer(INT_42, DIVIDE, INT_6);
        Assert.assertEquals(new Apfloat("7"), parser.parseTerm());
    }

    @Test
    public void complexMul() throws Exception {
        tokenizer(INT_2, MULTIPLY, INT_3, MULTIPLY, INT_7);
        Assert.assertEquals(new Apfloat("42"), parser.parseTerm());
    }

    @Test
    public void complexDiv() throws Exception {
        tokenizer(INT_42, DIVIDE, INT_7, DIVIDE, INT_3);
        Assert.assertEquals(new Apfloat("2"), parser.parseTerm());
    }
}