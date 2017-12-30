package ivs.ignis.gui;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

/**
 * Calculator main class.
 *
 * @author Jakub "Ash258" Čábera <cabera.jakub@gmail.com>
 */
public class CalculatorFX extends Application {

    /**
     * The main() method is ignored in correctly deployed JavaFX application.
     * main() serves only as fallback in case the application can not be
     * launched through deployment artifacts, e.g., in IDEs with limited FX
     * support. NetBeans ignores main().
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) throws Exception {
        FXMLLoader loader = new FXMLLoader(getClass().getClassLoader().getResource("views/Calculator.fxml"));

        // JavaFx don't share controller instance between multiple FXML files. => Controller factory.
        loader.setControllerFactory(ControllerFactory::generate);
        Scene scene = new Scene(loader.load());

        stage.setScene(scene);
        stage.setTitle("IVS Ignis Calculator");
        stage.getIcons().add(0, new Image("images/icon.ico"));
        stage.setResizable(false);
        stage.show();
    }
}
