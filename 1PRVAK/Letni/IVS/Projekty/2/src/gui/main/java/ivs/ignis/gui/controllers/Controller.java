package ivs.ignis.gui.controllers;

import ivs.ignis.math.IgnisCalculator;
import ivs.ignis.math.exception.CalculatorException;
import ivs.ignis.math.helpers.MathHelper;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollBar;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.Pane;
import org.apfloat.Apfloat;
import org.fxmisc.richtext.InlineCssTextArea;

import java.net.URL;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.function.Consumer;
import java.util.stream.IntStream;

/**
 * Main Controller. Handle
 *
 * @author Jakub "Ash258" Čábera <cabera.jakub@gmail.com>
 */
public class Controller implements Initializable {

    private static final String LABEL_NORMAL = "-fx-text-fill: #FFFFFF; -fx-font-style: normal";

    private static final String LABEL_ERROR = "-fx-text-fill: #cd0000; -fx-font-style: italic";

    private static final String TEXTAREA_NORMAL = "-fx-fill: inherit !important;";

    private static final String TEXTAREA_ERROR = "-fx-fill: #cd0000 !important;";

    @FXML public Pane topPane, inputPane, extendedFunctionsPane, baseButtonsPane;

    /** Label with history. */
    @FXML public Label inputLabel;

    /** Field for user inputs. */
    @FXML public InlineCssTextArea inputField;

    @FXML public ScrollBar inputBar;

    private boolean error = false;

    private Map<String, Consumer<String>> operations = new HashMap<>();

    {
        IntStream.range(0, 10).forEach(number -> operations.put(String.valueOf(number), this::append));
        Arrays.asList("+", "-", "*", ".", "/", "!").forEach(symbol -> operations.put(symbol, this::append));

        operations.put("\u00F7", t -> this.divide()); // \u00F7 = ÷
        operations.put("n!", t -> this.factorial());
        operations.put("CA", t -> this.clear());
        operations.put("Ans", t -> this.recall());
        operations.put("BACK", t -> this.backspace());
        operations.put("=", t -> this.evaluate());

    }

    private void append(String toAppend) {
        inputField.appendText(toAppend);
    }

    private void factorial() {
        inputField.appendText("!");
    }

    private void divide() {
        inputField.appendText("/");
    }

    private void clear() {
        inputField.clear();
    }

    private void backspace() {
        String text = inputField.getText();
        if (text.isEmpty()) return;
        clear();
        inputField.appendText(text.substring(0, text.length() - 1));
    }

    private void recall() {
        if (error) return;
        inputField.appendText(inputLabel.getText());
    }

    private void revertNormal() {
        if (!error) return;

        String text = inputField.getText();
        if (!text.isEmpty()) { inputField.setStyle(0, text.length(), TEXTAREA_NORMAL); }
    }

    private void evaluate() {
        try {
            String  expression = inputField.getText();
            Apfloat result     = IgnisCalculator.getInstance().calculate(expression);
            inputLabel.setStyle(LABEL_NORMAL);
            inputLabel.setText(result.scale() >= MathHelper.PRECISION ? result.toString() : result.toString(true));
            clear();
            error = false;
        } catch (CalculatorException e) {
            inputLabel.setStyle(LABEL_ERROR);
            inputLabel.setText(e.getMessage());
            if (e.getPosition() != null && e.getPosition() >= 0) {
                inputField.setStyle(e.getPosition(), e.getPosition() + 1, TEXTAREA_ERROR);
            }
            error = true;
        }
    }

    private void process(String text) {
        operations.get(text).accept(text);
    }

    /**
     * Handle user inputs.
     *
     * @param mouseEvent Event to listen.
     */
    @FXML
    public void processInput(MouseEvent mouseEvent) {
        process(((Button) mouseEvent.getSource()).getText());
    }

    @Override public void initialize(URL location, ResourceBundle resources) {
        inputField.setWrapText(true);
        inputField.textProperty().addListener((observable, oldValue, newValue) -> revertNormal());

        inputField.totalHeightEstimateProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue == null) return;
            inputBar.setVisible(newValue > inputField.getHeight());
            inputBar.setMax(newValue - inputField.getHeight());
        });

        inputField.heightProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue == null) return;
            inputBar.visibleAmountProperty().setValue(inputField.getHeight() / 4);
        });

        inputBar.valueProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue == null) return;
            inputBar.valueProperty().setValue(newValue.doubleValue());
        });
        inputField.estimatedScrollYProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue == null) return;
            inputBar.valueProperty().setValue(newValue);
        });
    }
}
