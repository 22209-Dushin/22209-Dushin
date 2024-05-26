package ru.nsu.dushin.exception;

public class VariableAlreadyExistsException extends CalculatorStackException {
    public VariableAlreadyExistsException(String s) {
        super(s);
    }
}