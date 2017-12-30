package ivs.ignis.math.exception;

import ivs.ignis.math.parsing.exceptions.*;
import ivs.ignis.math.tokenizing.exceptions.ExpectedDigit;
import ivs.ignis.math.tokenizing.exceptions.LexicalException;
import ivs.ignis.math.tokenizing.exceptions.UnrecognizedSequence;

import java.util.HashMap;
import java.util.Map;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class ExceptionHandler {

    private static Map<Class, String> exceptions = new HashMap<>();

    static {
        exceptions.put(ExpectedDigit.class, "Očekáváná číslice!");
        exceptions.put(UnrecognizedSequence.class, "Nerozpoznaná sada znaků!");
        exceptions.put(DivisionByZero.class, "Dělení nulou!");
        exceptions.put(FactorialOfDouble.class, "Faktoriál desetinného čísla!");
        exceptions.put(FactorialOfNegative.class, "Faktoriál záporného čísla!");
        exceptions.put(MissingArgumentForOperation.class, "Chybějící argument pro operaci!");
        exceptions.put(MissingParenthesis.class, "Chybějící závorka!");
        exceptions.put(RootOfNegative.class, "Odmocňování sudého základu ze záporného čísla!");
        exceptions.put(UnexpectedEof.class, "Neočekáváný konec!");
    }

    private ExceptionHandler() {}

    /**
     * Recognizes exception and provides presentable message in CalculatorException
     */
    public static CalculatorException handle(Exception e) {
        String message = exceptions.get(e.getClass());
        message = message != null ? message : "Neznámá chyba!";

        Integer position = null;
        if (e instanceof SyntaxException) {
            position = ((SyntaxException) e).getPosition();
        }
        if (e instanceof LexicalException) {
            position = ((LexicalException) e).getPosition();
        }

        return new CalculatorException(message, position, e);
    }
}
