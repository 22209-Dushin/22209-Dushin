package ru.nsu.dushin.calculator;

import ru.nsu.dushin.exception.IncorrectFileConfigurationException;
import ru.nsu.dushin.exception.UnknownOperationException;
import ru.nsu.dushin.operation.Operation;

import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.logging.Logger;

public abstract class OperationFactory {
    private static final Map<String, Class<? extends Operation>> operationsMap = new HashMap<>();
    private static final Logger LOGGER = Logger.getLogger(OperationFactory.class.getName());
    static {
        try (Scanner scanner = new Scanner(OperationFactory.class.getResourceAsStream("/config"))){
            while(scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] parts = line.split(" ");

                if (parts.length >= 2) {
                    String opName = parts[0].toLowerCase();
                    String classPath = parts[1];
                    operationsMap.put(opName, (Class<? extends Operation>) Class.forName(classPath));
                } else {
                    throw new IncorrectFileConfigurationException("invalid line in the configuration file: " + line);
                }
            }

        } catch (Throwable e) {
            LOGGER.severe("Error while reading the configuration file: " + e.getMessage());
        }
    }
    public static Operation getOperation(String name) throws NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException, UnknownOperationException {
        name = name.toLowerCase();
        if (!operationsMap.containsKey(name)) {
            throw new UnknownOperationException(name + " is unknown");
        }
       return operationsMap.get(name).getDeclaredConstructor().newInstance();
    }
}