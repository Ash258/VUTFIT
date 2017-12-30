package ivs.ignis.math.parsing.exceptions;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class FactorialOfNegative extends SyntaxException {

    public FactorialOfNegative(int position) {
        super(position);
    }
}
