package ivs.ignis.math.tokenizing;

import com.tngtech.java.junit.dataprovider.DataProvider;
import com.tngtech.java.junit.dataprovider.DataProviderRunner;
import com.tngtech.java.junit.dataprovider.UseDataProvider;
import ivs.ignis.math.tokenizing.exceptions.LexicalException;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.util.Arrays;
import java.util.List;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.is;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

/**
 * @author Pavel Parma <pavelparma0@gmail.com>
 */
@RunWith(DataProviderRunner.class)
public class TokenizerTest {

    private Tokenizer tokenizer = new Tokenizer();

    @DataProvider
    public static Object[][] dataProviderTokenizeString() {
        return new Object[][] {
                {"/", TokenType.DIVIDE},
                {"^", TokenType.POWER},
                {"*", TokenType.MULTIPLY},
                {"+", TokenType.PLUS},
                {"-", TokenType.MINUS},
                {"(", TokenType.OPEN_PARENTHESIS},
                {")", TokenType.CLOSED_PARENTHESIS},
                {"!", TokenType.FACTORIAL},
                {"1254.487", TokenType.DOUBLE},
                {"1254.487E12", TokenType.DOUBLE},
                {"1254.487e12", TokenType.DOUBLE},
                {"1254e12", TokenType.DOUBLE},
                {"1254E12", TokenType.DOUBLE},
                {"1254", TokenType.INTEGER}
        };
    }

    @Test
    public void peekOnEmpty() throws Exception {
        tokenizer.reset("");
        assertNull(tokenizer.peek());
    }

    @Test
    public void currentOnEmpty() throws Exception {
        tokenizer.reset("");
        assertEquals(TokenType.EOF, tokenizer.current().getType());
    }

    @Test
    public void prevOnEmpty() throws Exception {
        tokenizer.reset("");
        assertNull(tokenizer.previous());
    }

    @Test
    @UseDataProvider("dataProviderTokenizeString")
    public void tokenizeString(String operator, TokenType type) throws Exception {
        this.tokenizer.reset(operator);
        Token current = this.tokenizer.gain();

        assertEquals(type, current.getType());
        assertEquals(operator.toLowerCase(), current.getValue());
    }

    @Test
    public void singleTokenAndDependencies() throws Exception {
        tokenizer.reset("+");

        assertEquals(TokenType.PLUS, tokenizer.current().getType());
        assertEquals(TokenType.EOF, tokenizer.peek().getType());

        tokenizer.tokenizeSingleToken();
        assertEquals(TokenType.PLUS, tokenizer.previous().getType());
        assertEquals(TokenType.EOF, tokenizer.current().getType());
        assertNull(tokenizer.peek());
    }

    @Test
    public void twoTokensAndDependencies() {
        this.tokenizer.reset("+ -");

        assertEquals(TokenType.PLUS, this.tokenizer.current().getType());
        assertEquals(TokenType.MINUS, this.tokenizer.peek().getType());

        this.tokenizer.tokenizeSingleToken();
        assertEquals(TokenType.MINUS, this.tokenizer.current().getType());
        assertEquals(TokenType.PLUS, this.tokenizer.previous().getType());
        assertEquals(TokenType.EOF, this.tokenizer.peek().getType());

        this.tokenizer.tokenizeSingleToken();
        assertEquals(TokenType.EOF, this.tokenizer.current().getType());
        assertEquals(TokenType.MINUS, this.tokenizer.previous().getType());
        assertNull(this.tokenizer.peek());
    }

    @Test
    public void tokenizeAll() throws Exception {
        this.tokenizer.reset("145 + 87 / 78.1");
        List<Token> tokens = this.tokenizer.tokenize();

        assertThat(tokens, is(Arrays.asList(
                new Token(TokenType.INTEGER, "145", 0),
                new Token(TokenType.PLUS, "+", 4),
                new Token(TokenType.INTEGER, "87", 6),
                new Token(TokenType.DIVIDE, "/", 9),
                new Token(TokenType.DOUBLE, "78.1", 11),
                new Token(TokenType.EOF, null, 14)
        )));
    }

    @Test
    public void checkPrevious() throws Exception {
        this.tokenizer.reset("+ + - -");
        tokenizer.tokenizeSingleToken();
        tokenizer.tokenizeSingleToken();
        tokenizer.tokenizeSingleToken();

        List<Token> tokens = this.tokenizer.previousTokens();
        assertThat(tokens, is(Arrays.asList(
                new Token(TokenType.PLUS, "+", 0),
                new Token(TokenType.PLUS, "+", 2)
        )));
    }

    @Test(expected = LexicalException.class)
    public void testUnrecognizedToken() throws LexicalException {
        this.tokenizer.reset("foo");
        this.tokenizer.gain();
    }
}

