package ru.nsu.dushin.operation;

import ru.nsu.dushin.calculator.CalculatorStack;
import ru.nsu.dushin.exception.OperationException;

import java.util.ArrayList;

public interface Operation {
    public void exec(CalculatorStack stack, ArrayList<Object> args) throws OperationException;
}
