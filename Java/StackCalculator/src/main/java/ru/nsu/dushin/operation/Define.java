package ru.nsu.dushin.operation;

import ru.nsu.dushin.calculator.CalculatorStack;
import ru.nsu.dushin.exception.ExecuteOperationException;
import ru.nsu.dushin.exception.OperationException;

import java.util.ArrayList;

public class Define implements Operation {
    @Override
    public void exec(CalculatorStack stack, ArrayList<Object> args) throws OperationException {
        if (args.size() != 2) {
            throw new ExecuteOperationException("incorrect number of arguments in define");
        }
        if (!(args.get(0) instanceof String)) {
            throw new ExecuteOperationException("argument with an index of 1 is not a String in define");
        }
        if (!(args.get(1) instanceof Double)) {
            throw new ExecuteOperationException("argument with an index of 2 is not a double in define");
        }
        stack.createVar((String) args.get(0), (double) args.get(1));
    }
}
