/*! \mainpage Project description
 *
 * \section intro_sec Introduction
 *
 * Basic math library with text parsing.
 *
 * \section Authors
 * - Vojtěch Bargl (xbargl01)
 * - Pavel Parma (xparma02)
 */

package ivs.ignis.math;

import ivs.ignis.math.exception.CalculatorException;
import ivs.ignis.math.exception.ExceptionHandler;
import ivs.ignis.math.parsing.Parser;
import ivs.ignis.math.tokenizing.Tokenizer;
import org.apfloat.Apfloat;

/**
 * @author Pavel Parma <pavelparma0@gmail.com>
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class IgnisCalculator {

    private static IgnisCalculator ourInstance = new IgnisCalculator();

    private Parser parser;

    private Tokenizer tokenizer;

    private IgnisCalculator() {
        this.tokenizer = new Tokenizer();
        this.parser = new Parser(tokenizer);
    }

    public static IgnisCalculator getInstance() {
        return ourInstance;
    }

    /**
     * @param statement Statement to calculate
     *
     * @return Statement result
     *
     * @throws CalculatorException if anything goes wrong.
     */
    public Apfloat calculate(String statement) throws CalculatorException {

        try {
            tokenizer.reset(statement);
            return this.parser.parse();
        } catch (Exception e) {
            throw ExceptionHandler.handle(e);
        }
    }
}
