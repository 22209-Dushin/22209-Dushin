package ru.nsu.dushin.calculator;

import ru.nsu.dushin.exception.UnknownVariableException;
import ru.nsu.dushin.exception.VariableAlreadyExistsException;
import ru.nsu.dushin.exception.EmptyStackException;

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

public class CalculatorStack {
    private final Stack<Double> stack = new Stack<>();
    private final  Map<String, Double> variableMap = new HashMap<>();
    public void createVar(String name, double value) throws VariableAlreadyExistsException {
        if (variableMap.containsKey(name)) {
            throw new VariableAlreadyExistsException("variable " + name + " already exists");
        } else {
            variableMap.put(name, value);
        }
    }
    public void push(double value) {
        stack.push(value);
    }

    public void push(String var) throws UnknownVariableException {
        if (variableMap.containsKey(var)) {
            stack.push(variableMap.get(var));
        } else {
            throw new UnknownVariableException(var);
        }
    }

    public double pop() throws EmptyStackException {
        if (stack.isEmpty()) {
            throw new EmptyStackException("stack is empty!");
        }
        return stack.pop();
    }
    public void pop(String var) throws UnknownVariableException {
        if (variableMap.containsKey(var)) {
            variableMap.put(var, stack.pop());
        }
        else {
            throw new UnknownVariableException(var);
        }
    }

    public double peek() throws EmptyStackException{
        if (stack.isEmpty()) {
            throw new EmptyStackException("stack is empty!");
        }
        return stack.peek();
    }
}