package ivs.ignis.math.tokenizing.exceptions;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class ExpectedDigit extends LexicalException {

    public ExpectedDigit(int position) {
        super(position);
    }
}
