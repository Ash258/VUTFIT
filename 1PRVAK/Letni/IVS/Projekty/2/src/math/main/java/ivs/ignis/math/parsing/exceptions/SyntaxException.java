package ivs.ignis.math.parsing.exceptions;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class SyntaxException extends RuntimeException {

    private final int position;

    public SyntaxException(int position) {
        this.position = position;
    }

    public int getPosition() {
        return position;
    }
}
