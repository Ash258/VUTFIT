package ivs.ignis.math.tokenizing;

import java.util.Iterator;

/**
 * @author Pavel Parma <pavelparma0@gmail.com>
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
class InputTextReader implements Iterator<Character> {

    protected String source;

    protected int position = -1;

    public InputTextReader(String text) {
        this.source = text;
    }

    public int getPosition() {
        return position;
    }

    @Override
    public boolean hasNext() {
        return this.position < this.source.length() - 1;
    }

    @Override
    public Character next() {
        return this.source.charAt(++this.position);
    }

    /**
     * Get following character of input text.
     *
     * @return String with found chars
     */
    public char peek() {
        return this.source.charAt(position + 1);
    }

    /**
     * Get n number of input text.
     *
     * @param offset Offset which will by added to current position.
     * @param limit  Limit from offset
     *
     * @return String with found chars
     */
    public String peek(int offset, int limit) {
        return this.source.substring(offset, limit);
    }
}
