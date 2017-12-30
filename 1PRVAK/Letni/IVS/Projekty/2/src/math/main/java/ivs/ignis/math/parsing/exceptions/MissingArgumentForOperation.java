package ivs.ignis.math.parsing.exceptions;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class MissingArgumentForOperation extends SyntaxException {

    public MissingArgumentForOperation(int position) {
        super(position);
    }
}
