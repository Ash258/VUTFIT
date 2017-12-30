package ivs.ignis.math.parsing;

import ivs.ignis.math.parsing.exceptions.*;
import ivs.ignis.math.tokenizing.Token;
import ivs.ignis.math.tokenizing.TokenType;
import org.junit.Test;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class ParserWrongSyntaxTest extends ParserTestSuite {

    private static final Token INT_ONE  = new Token(TokenType.INTEGER, "1", -1);

    private static final Token INT_ZERO = new Token(TokenType.INTEGER, "0", -1);

    @Test(expected = UnexpectedEof.class)
    public void unexpectedEnd() throws Exception {
        tokenizer(INT_42, INT_42);
        parser.parse();
    }

    @Test(expected = MissingArgumentForOperation.class)
    public void expressionMissingNumber() throws Exception {
        tokenizer(INT_42, PLUS);
        parser.parseExpression();
    }

    @Test(expected = MissingArgumentForOperation.class)
    public void termMissingNumber() throws Exception {
        tokenizer(INT_42, MULTIPLY);
        parser.parseTerm();
    }

    @Test(expected = MissingArgumentForOperation.class)
    public void unaryMissingNumber() throws Exception {
        tokenizer(PLUS);
        parser.parseUnary();
    }

    @Test(expected = MissingArgumentForOperation.class)
    public void factorMissingNumber() throws Exception {
        tokenizer(FACTORIAL);
        parser.parseFactor();
    }

    @Test(expected = FactorialOfNegative.class)
    public void factorialNegative() throws Exception {
        tokenizer(OPEN_P, MINUS, INT_42, CLOSED_P, FACTORIAL);
        parser.parse();
    }

    @Test(expected = FactorialOfDouble.class)
    public void factorialDouble() throws Exception {
        tokenizer(DOUBLE_42_1, FACTORIAL);
        parser.parse();
    }

    @Test(expected = RootOfNegative.class)
    public void rootOfNegative() throws Exception {
        tokenizer(OPEN_P, MINUS, DOUBLE_42, CLOSED_P, POWER, OPEN_P, INT_ONE, DIVIDE, INT_42, CLOSED_P);
        parser.parse();
    }

    @Test(expected = MissingParenthesis.class)
    public void missingParenthesis() throws Exception {
        tokenizer(OPEN_P, MINUS, DOUBLE_42);
        parser.parse();
    }

    @Test(expected = DivisionByZero.class)
    public void divisionByZero() throws Exception {
        tokenizer(INT_42, DIVIDE, INT_ZERO);
        parser.parse();
    }
}
