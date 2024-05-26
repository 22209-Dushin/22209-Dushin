package ru.nsu.dushin.operation;

import ru.nsu.dushin.calculator.CalculatorStack;
import ru.nsu.dushin.exception.ExecuteOperationException;
import ru.nsu.dushin.exception.OperationException;

import java.util.ArrayList;

public class Push implements Operation {
    @Override
    public void exec(CalculatorStack stack, ArrayList<Object> args) throws OperationException {
        if (args.size() != 1) {
            throw new ExecuteOperationException("incorrect number of arguments in push");
        }
        if (args.get(0) instanceof String) {
            stack.push((String) args.get(0));
        } else if (args.get(0) instanceof Double) {
                stack.push((Double) args.get(0));
        } else {
            throw new ExecuteOperationException("Bad argument in pop");
        }
    }
}
