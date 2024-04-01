package ru.nsu.dushin.operation;

import ru.nsu.dushin.calculator.CalculatorStack;
import ru.nsu.dushin.exception.ExecuteOperationException;
import ru.nsu.dushin.exception.OperationException;

import java.util.ArrayList;

public class Minus implements Operation {
    @Override
    public void exec(CalculatorStack stack, ArrayList<Object> args) throws OperationException {
        if (!args.isEmpty()) {
            throw new ExecuteOperationException("incorrect number of arguments in minus");
        }
        double val1 = stack.pop();
        double val2 = stack.pop();
        stack.push(val2 - val1);
    }
}