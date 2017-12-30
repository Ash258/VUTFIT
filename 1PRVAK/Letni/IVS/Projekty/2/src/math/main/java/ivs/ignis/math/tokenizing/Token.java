package ivs.ignis.math.tokenizing;

import java.util.Objects;

/**
 * @author Pavel Parma <pavelparma0@gmail.com>
 */
public final class Token {

    private TokenType type;

    private String value;

    private Integer position;

    public Token(TokenType type, String value, Integer position) {
        this.type = type;
        this.value = value;
        this.position = position;
    }

    public String getValue() {
        return value;
    }

    public TokenType getType() {
        return type;
    }

    public Integer getPosition() {
        return position;
    }

    public boolean isType(TokenType type) {
        return getType() == type;
    }

    @Override public String toString() {
        return "Token{" +
               "type=" + type +
               ", value='" + value + '\'' +
               ", position=" + position +
               '}';
    }

    @Override public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Token token = (Token) o;

        return Objects.equals(type, token.type) &&
               Objects.equals(value, token.value) &&
               Objects.equals(position, token.position);
    }

    @Override public int hashCode() {
        int result = type.hashCode();
        result = 31 * result + value.hashCode();
        result = 31 * result + position.hashCode();
        return result;
    }
}
