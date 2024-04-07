package ru.nsu.dushin.calculator;

import java.io.Reader;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.logging.Logger;

public class Interpretator {
    private final Reader reader;
    private final CalculatorStack stack = new CalculatorStack();
    private static final Logger LOGGER = Logger.getLogger(Interpretator.class.getName());
    public Interpretator(Reader reader) {
        this.reader = reader;
    }
    public void execute() {
        String line = "";
        String operationName = "";
        try (Scanner scan = new Scanner(reader)) {
            while (scan.hasNext()) {
                ArrayList<Object> args = new ArrayList<>();
                line = scan.nextLine();
                if (line.isEmpty() || line.charAt(0) == '#')
                    continue;

                for (String word : line.split(" ")) {
                    if (operationName.isEmpty()) {
                        operationName = word;
                    } else if (ArgCheck.isDouble(word)) {
                        args.add(Double.parseDouble(word));
                    } else {
                        args.add(word);
                    }
                }
                OperationFactory.getOperation(operationName).exec(stack, args);
                LOGGER.info(operationName + args.toString());
                operationName = "";
            }
        } catch (Throwable e) {
            LOGGER.severe("Error in command: " + line + "\n" + e.getClass().getSimpleName() + (e.getMessage() == null ? "" : ": " + e.getMessage()));
        }
    }
}

class ArgCheck {
    public static boolean isDouble(String str) {
        return str.matches("-?\\d+(\\.\\d+)?") || str.matches("-?\\d+");
    }
}