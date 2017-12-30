package ivs.ignis.math.parsing.exceptions;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class DivisionByZero extends SyntaxException {

    public DivisionByZero(int position) {
        super(position);
    }
}
