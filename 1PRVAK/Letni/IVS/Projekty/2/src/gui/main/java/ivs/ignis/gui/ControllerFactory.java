package ivs.ignis.gui;

import java.util.HashMap;
import java.util.Map;

/**
 * Class ControllerFactory.
 *
 * @author Jakub "Ash258" Čábera <cabera.jakub@gmail.com>
 * @author Pavel Parma <pavelparma0@gmail.com>
 */
class ControllerFactory {

    private static Map<Class, Object> instances = new HashMap<>();

    static Object generate(Class<?> type) {
        if(instances.containsKey(type)) return instances.get(type);

        try {
            Object instance = type.newInstance();
            instances.put(type, instance);
            return instance;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
