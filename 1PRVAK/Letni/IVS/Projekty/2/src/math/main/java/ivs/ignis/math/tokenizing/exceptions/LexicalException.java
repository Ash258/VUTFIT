package ivs.ignis.math.tokenizing.exceptions;

/**
 * @author Pavel Parma <pavelparma0@gmail.com>
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class LexicalException extends RuntimeException {

    private final int position;

    public LexicalException(int position) {
        this.position = position;
    }

    public int getPosition() {
        return position;
    }
}
