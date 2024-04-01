package ru.nsu.dushin.exception;

public class UnknownVariableException extends CalculatorStackException
{
    public UnknownVariableException(String s) {
        super(s);
    }
}