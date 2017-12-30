package ivs.ignis.math.parsing.exceptions;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class MissingParenthesis extends SyntaxException {

    public MissingParenthesis(int position) {
        super(position);
    }
}
