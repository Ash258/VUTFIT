package ivs.ignis.math.parsing;

import ivs.ignis.math.helpers.MathHelper;
import ivs.ignis.math.parsing.exceptions.MissingArgumentForOperation;
import ivs.ignis.math.parsing.exceptions.MissingParenthesis;
import ivs.ignis.math.parsing.exceptions.SyntaxException;
import ivs.ignis.math.parsing.exceptions.UnexpectedEof;
import ivs.ignis.math.tokenizing.Token;
import ivs.ignis.math.tokenizing.TokenType;
import ivs.ignis.math.tokenizing.Tokenizer;
import org.apfloat.Apfloat;
import org.apfloat.ApfloatMath;

import java.util.function.IntFunction;

import static ivs.ignis.math.tokenizing.TokenType.*;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class Parser {

    private static IntFunction<SyntaxException> UNSPECIFIED = SyntaxException::new;

    private Validator validator = Validator.getInstance();

    private Tokenizer tokenizer;

    public Parser(Tokenizer tokenizer) {
        this.tokenizer = tokenizer;
    }

    /**
     * Replace active tokenizer with specified {@link ivs.ignis.math.tokenizing.Tokenizer}.
     *
     * @param tokenizer - to be replace with.
     */
    public void setTokenizer(Tokenizer tokenizer) {
        this.tokenizer = tokenizer;
    }

    public Apfloat parse() {
        Apfloat expression = parseExpression();
        if (!checkToken(EOF)) throw new UnexpectedEof(getPosition());
        return expression;
    }

    /**
     * @return Apfloat value of sequence.
     */
    Apfloat parseExpression() {
        Apfloat res = parseTerm();

        while (checkToken(PLUS, MINUS)) {
            Token   operator = stepToken(UNSPECIFIED, PLUS, MINUS);
            Apfloat operand  = parseTerm();

            res = operator.isType(PLUS) ? res.add(operand) : res.subtract(operand);
            res = MathHelper.roundUp(res);
        }

        return res;
    }

    /**
     * @return Apfloat value of sequence.
     */
    Apfloat parseTerm() {
        Apfloat res = parseUnary();

        while (checkToken(MULTIPLY, DIVIDE)) {
            Token   operator = stepToken(UNSPECIFIED, MULTIPLY, DIVIDE);
            int     pos      = getPosition();
            Apfloat operand  = parseUnary();

            if (operator.isType(DIVIDE)) {
                validator.validateDivision(pos, operand);
                res = res.divide(operand);
            } else {
                res = res.multiply(operand);
            }

            res = MathHelper.roundUp(res);
        }

        return res;
    }

    private Integer getPosition() {
        return tokenizer.current().getPosition();
    }

    /**
     * @return Apfloat value of token sequence.
     */
    Apfloat parseUnary() {
        boolean sign = true; // PLUS as default
        while (checkToken(PLUS, MINUS)) {
            sign = stepToken(UNSPECIFIED, PLUS, MINUS).isType(MINUS) != sign;
        }

        Apfloat apfloat = parseExponent();
        return sign ? apfloat : apfloat.negate();
    }

    /**
     * @return Aplfloat value of sequence.
     */
    Apfloat parseExponent() {
        Apfloat decimal = parseFactor();

        if (checkToken(POWER)) {
            stepToken(UNSPECIFIED, POWER);
            int     pos      = getPosition();
            Apfloat exponent = parseUnary();
            validator.validateRoot(pos, decimal, exponent);
            decimal = ApfloatMath.pow(decimal, exponent);
            decimal = MathHelper.roundUp(decimal);
        }

        return decimal;
    }

    /**
     * @return Apfloat value of token sequence.
     */
    Apfloat parseFactor() {
        Apfloat number = null;

        if (checkToken(INTEGER, DOUBLE)) {
            Token token = stepToken(UNSPECIFIED, INTEGER, DOUBLE);
            number = new Apfloat(token.getValue(), MathHelper.PRECISION);
        } else if (checkToken(OPEN_PARENTHESIS)) {
            stepToken(UNSPECIFIED, OPEN_PARENTHESIS);
            number = parseExpression();
            stepToken(MissingParenthesis::new, CLOSED_PARENTHESIS);
        }

        if (number == null) {
            throw new MissingArgumentForOperation(getPosition());
        }

        while (checkToken(FACTORIAL)) {
            stepToken(UNSPECIFIED, FACTORIAL);
            validator.validateFactorial(getPosition(), number);
            number = MathHelper.factorial(number, MathHelper.PRECISION);
            number = MathHelper.roundUp(number);
        }

        return number;
    }

    /**
     * @param types set of types that could be stepped.
     *
     * @param exception
     * @param types
     * @return Token if its type is in types.
     */
    private Token stepToken(IntFunction<SyntaxException> exception, TokenType... types) {
        Token token = tokenizer.current();

        for (TokenType type : types) {
            if (token.isType(type)) {
                return tokenizer.gain();
            }
        }

        throw exception.apply(token != null ? token.getPosition() : -1);
    }

    /**
     * @param types set of types that are allowed.
     *
     * @return True if any is find, false otherwise.
     */
    private boolean checkToken(TokenType... types) {
        Token token = tokenizer.current();

        for (TokenType type : types) {
            if (token.isType(type)) return true;
        }

        return false;
    }
}
