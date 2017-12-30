package ivs.ignis.math.exception;

import javax.annotation.Nullable;
import java.util.Objects;

/**
 * @author Vojtěch Bargl <bargl.vojtech@gmail.com>
 */
public class CalculatorException extends RuntimeException {

    private final Integer position;

    public CalculatorException(String message, Integer position, Throwable cause) {
        super(Objects.requireNonNull(message), cause);
        this.position = position;
    }

    @Nullable
    public Integer getPosition() {
        return position;
    }
}
