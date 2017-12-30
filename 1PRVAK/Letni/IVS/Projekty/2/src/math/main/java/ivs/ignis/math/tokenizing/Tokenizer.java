package ivs.ignis.math.tokenizing;

import ivs.ignis.math.tokenizing.exceptions.ExpectedDigit;
import ivs.ignis.math.tokenizing.exceptions.UnrecognizedSequence;

import java.util.*;
import java.util.function.Function;

/**
 * @author Pavel Parma <pavelparma0@gmail.com>
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class Tokenizer {

    private static List<Character> exponent = Arrays.asList('E', 'e');

    private static List<Character> unary    = Arrays.asList('+', '-');

    private static HashMap<String, Function<Integer, Token>> knownCharacters = new HashMap<>();

    private static Function<Integer, Token> EOF = x -> new Token(TokenType.EOF, null, x);

    static {
        knownCharacters.put("/", x -> new Token(TokenType.DIVIDE, "/", x));
        knownCharacters.put("*", x -> new Token(TokenType.MULTIPLY, "*", x));
        knownCharacters.put("+", x -> new Token(TokenType.PLUS, "+", x));
        knownCharacters.put("-", x -> new Token(TokenType.MINUS, "-", x));
        knownCharacters.put("(", x -> new Token(TokenType.OPEN_PARENTHESIS, "(", x));
        knownCharacters.put("^", x -> new Token(TokenType.POWER, "^", x));
        knownCharacters.put(")", x -> new Token(TokenType.CLOSED_PARENTHESIS, ")", x));
        knownCharacters.put("!", x -> new Token(TokenType.FACTORIAL, "!", x));
    }

    private InputTextReader input;

    private List<Token> tokens;

    private Token peek = null;

    public Tokenizer() {
        this.tokens = new LinkedList<>();
        this.reset("");
    }

    /**
     * Initialize tokenizer for new tokenizing.
     *
     * @param text Text to be tokenized
     */
    public void reset(String text) {
        this.tokens.clear();
        this.peek = null;
        this.input = new InputTextReader(text);
        this.tokenizeSingleToken();
    }

    /**
     * Tokenize single token and get current.
     *
     * @return Current token
     */
    public Token gain() {
        this.tokenizeSingleToken();

        return this.previous();
    }

    /**
     * @return Next token.
     */
    public Token peek() {
        if (this.peek != null) return this.peek;

        return this.reachedEnd() ? null : (this.peek = this.getToken());
    }

    /**
     * @return Current token.
     */
    public Token current() {
        return this.tokens.get(this.tokens.size() - 1);
    }

    /**
     * @return Previous token.
     */
    public Token previous() {
        return (this.tokens.isEmpty() || this.tokens.size() == 1) ? null : this.tokens.get(this.tokens.size() - 2);
    }

    /**
     * @return All tokens.
     */
    public List<Token> previousTokens() {
        if (this.tokens.isEmpty() || this.tokens.size() == 1) return Collections.emptyList();
        return new ArrayList<>(this.tokens.subList(0, this.tokens.size() - 2));
    }

    /**
     * Transform input into list of tokens.
     *
     * @return All tokens from current position
     */
    public List<Token> tokenize() {
        while (!this.reachedEnd()) {
            tokenizeSingleToken();
        }

        return new ArrayList<>(tokens.subList(0, tokens.size()));
    }

    /**
     * Tokenize following text if any.
     */
    public void tokenizeSingleToken() {
        if (this.reachedEnd()) return;

        this.tokens.add((this.peek != null) ? this.peek : this.getToken());
        this.peek = null;
    }

    /**
     * @return True if tokenizer reached end, False otherwise
     */
    public boolean reachedEnd() {
        return !this.tokens.isEmpty() && this.tokens.get(this.tokens.size() - 1).isType(TokenType.EOF);
    }

    /**
     * Get lastOne token in input.
     *
     * @return Next token from current position
     */
    private Token getToken() {

        if (!this.input.hasNext()) {
            return EOF.apply(this.input.getPosition());
        }
        if (Character.isWhitespace(this.input.peek())) {
            this.skipWhitespaces();
        }
        if (Character.isDigit(this.input.peek())) {
            return this.tokenizeNumber();
        }

        Function<Integer, Token> token = knownCharacters.get(String.valueOf(this.input.peek()));
        if (token != null) {
            input.next();
            return token.apply(this.input.getPosition());
        }

        throw new UnrecognizedSequence(input.getPosition() + 1);
    }

    /**
     * Tokenize number in input.
     *
     * @return Number token. Can be double or integer.
     */
    private Token tokenizeNumber() {
        int       position = this.input.getPosition() + 1;
        TokenType type     = TokenType.INTEGER;
        String    integer  = tokenizeDigitSequence();

        if (!this.input.hasNext()) {
            return new Token(type, integer, position);
        }

        if (this.input.hasNext() && this.input.peek() == '.') {
            integer += this.input.next();
            integer += tokenizeDigitSequence();
            type = TokenType.DOUBLE;
        }

        if (this.input.hasNext() && exponent.contains(this.input.peek())) {
            integer += Character.toLowerCase(this.input.next());
            if (unary.contains(this.input.peek())) {
                integer += this.input.next();
            }
            integer += tokenizeDigitSequence();
            type = TokenType.DOUBLE;
        }

        return new Token(type, integer, position);
    }

    /**
     * Tokenize digit sequence in input.
     *
     * @return Digit sequence.
     */
    private String tokenizeDigitSequence() {
        StringBuilder sb = new StringBuilder();

        if (!this.input.hasNext() || !Character.isDigit(this.input.peek())) {
            throw new ExpectedDigit(this.input.getPosition() + 1);
        }

        do {
            sb.append(this.input.next());
        } while (this.input.hasNext() && Character.isDigit(this.input.peek()));

        return sb.toString();
    }

    /**
     * Skip whitespaces in input.
     */
    private void skipWhitespaces() {
        while (this.input.hasNext() && Character.isWhitespace(this.input.peek())) {
            this.input.next();
        }
    }
}
