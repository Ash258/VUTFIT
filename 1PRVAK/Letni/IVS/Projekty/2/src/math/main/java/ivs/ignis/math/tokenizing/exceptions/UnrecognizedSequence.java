package ivs.ignis.math.tokenizing.exceptions;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class UnrecognizedSequence extends LexicalException {

    public UnrecognizedSequence(int position) {
        super(position);
    }
}
