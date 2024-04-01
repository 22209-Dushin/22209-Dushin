package ru.nsu.dushin.operation;

import ru.nsu.dushin.calculator.CalculatorStack;
import ru.nsu.dushin.exception.ExecuteOperationException;
import ru.nsu.dushin.exception.OperationException;

import java.util.ArrayList;

public class Pop implements Operation {
    @Override
    public void exec(CalculatorStack stack, ArrayList<Object> args) throws OperationException {
        if (args.size() > 1) {
            throw new ExecuteOperationException("incorrect number of arguments in pop");
        }
        else if (args.size() == 1 && args.get(0) instanceof String) {
            stack.pop((String) args.get(0));
        }
        else if (args.isEmpty()) {
            stack.pop();
        }
        else {
            throw new ExecuteOperationException("Bad argument in pop");
        }
    }
}
