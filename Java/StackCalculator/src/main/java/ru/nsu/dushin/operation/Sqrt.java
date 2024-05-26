package ru.nsu.dushin.operation;

import ru.nsu.dushin.calculator.CalculatorStack;
import ru.nsu.dushin.exception.ExecuteOperationException;
import ru.nsu.dushin.exception.OperationException;

import java.util.ArrayList;

public class Sqrt implements Operation {
    @Override
    public void exec(CalculatorStack stack, ArrayList<Object> args) throws OperationException {
        if (!args.isEmpty()) {
            throw new ExecuteOperationException("incorrect number of arguments in sqrt");
        }
        double val = stack.pop();
        stack.push(Math.sqrt(val));
    }
}
