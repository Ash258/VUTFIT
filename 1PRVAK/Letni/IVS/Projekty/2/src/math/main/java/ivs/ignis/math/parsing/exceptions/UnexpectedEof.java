package ivs.ignis.math.parsing.exceptions;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class UnexpectedEof extends SyntaxException {

    public UnexpectedEof(int position) {
        super(position);
    }
}
