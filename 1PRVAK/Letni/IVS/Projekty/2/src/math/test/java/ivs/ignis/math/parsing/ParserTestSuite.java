package ivs.ignis.math.parsing;

import ivs.ignis.math.tokenizing.Token;
import ivs.ignis.math.tokenizing.TokenType;
import ivs.ignis.math.tokenizing.Tokenizer;
import org.junit.Before;
import org.junit.Rule;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.junit.MockitoJUnit;
import org.mockito.junit.MockitoRule;
import org.mockito.stubbing.Answer;

import java.util.Arrays;
import java.util.List;
import java.util.Objects;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class ParserTestSuite {

    public static Token EOF = new Token(TokenType.EOF, null, -1);

    public static Token MINUS = new Token(TokenType.MINUS, "-", -1);

    public static Token PLUS = new Token(TokenType.PLUS, "+", -1);

    public static Token MULTIPLY = new Token(TokenType.MULTIPLY, "*", -1);

    public static Token DIVIDE = new Token(TokenType.DIVIDE, "/", -1);

    public static Token POWER = new Token(TokenType.POWER, "^", -1);

    public static Token FACTORIAL = new Token(TokenType.FACTORIAL, "!", -1);

    public static Token OPEN_P = new Token(TokenType.OPEN_PARENTHESIS, "(", -1);

    public static Token CLOSED_P = new Token(TokenType.CLOSED_PARENTHESIS, ")", -1);

    public static Token INT_42 = new Token(TokenType.INTEGER, "42", -1);

    public static Token DOUBLE_42 = new Token(TokenType.DOUBLE, "42.0", -1);

    public static Token DOUBLE_42_1 = new Token(TokenType.DOUBLE, "42.1", -1);

    @Rule
    public MockitoRule mockitoRule = MockitoJUnit.rule();

    Parser parser;

    @Mock
    private Tokenizer tokenizer;

    @Before
    public void setUp() throws Exception {
        parser = new Parser(tokenizer);
    }

    public void tokenizer(Token... tokens) {
        TokenizerMock tokenizerMock = new TokenizerMock(Arrays.asList(tokens));

        Mockito.when(tokenizer.gain()).then(tokenizerMock);
        Mockito.when(tokenizer.current()).then(tokenizerMock);
    }

    private static class TokenizerMock implements Answer<Token> {

        private final List<Token> tokens;

        private int position = 0;

        TokenizerMock(List<Token> tokens) {
            this.tokens = tokens;
        }

        @Override public Token answer(InvocationOnMock invocation) throws Throwable {
            if (position >= tokens.size()) return EOF;

            if (Objects.equals(invocation.getMethod().getName(), "current")) return tokens.get(position);
            if (Objects.equals(invocation.getMethod().getName(), "gain")) {
                position++;
                return tokens.get(position - 1);
            }

            return null;
        }
    }
}
