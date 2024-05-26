package ru.nsu.dushin.operation;

import ru.nsu.dushin.calculator.CalculatorStack;
import ru.nsu.dushin.exception.*;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.io.*;
import java.util.ArrayList;

public class TestOperation {
    @Test
    public void testMinus() throws Exception {
        CalculatorStack stack = new CalculatorStack();
        Minus minus = new Minus();
        ArrayList<Object> args = new ArrayList<>();
        stack.push(1.0);
        stack.push(2.0);
        minus.exec(stack, args);
        Assertions.assertEquals(-1.0, stack.pop());

        args.clear();
        args.add(1.0);
        Assertions.assertThrows(OperationException.class, () -> minus.exec(stack, args));
    }

    @Test
    public void testDivide() throws OperationException {
        CalculatorStack stack = new CalculatorStack();
        Divide divide = new Divide();
        ArrayList<Object> args = new ArrayList<>();
        stack.push(1.0);
        stack.push(2.0);
        divide.exec(stack, args);
        Assertions.assertEquals(0.5, stack.pop());

        args.clear();
        args.add(1.0);
        Assertions.assertThrows(OperationException.class, () -> divide.exec(stack, args));
    }

    @Test
    public void testMultiply() throws Exception {
        CalculatorStack stack = new CalculatorStack();
        Multiply multiply = new Multiply();
        ArrayList<Object> args = new ArrayList<>();
        stack.push(1.0);
        stack.push(2.0);
        multiply.exec(stack, args);
        Assertions.assertEquals(2.0, stack.pop());

        args.clear();
        args.add(1.0);
        Assertions.assertThrows(OperationException.class, () -> multiply.exec(stack, args));
    }

    @Test
    public void testPlus() throws Exception{
        CalculatorStack stack = new CalculatorStack();
        Plus plus = new Plus();
        ArrayList<Object> args = new ArrayList<>();
        stack.push(1.0);
        stack.push(2.0);
        plus.exec(stack, args);
        Assertions.assertEquals(3.0, stack.pop());

        args.clear();
        args.add(1.0);
        Assertions.assertThrows(OperationException.class, () -> plus.exec(stack, args));
    }

    @Test
    public void testPop() throws Exception {
        CalculatorStack stack = new CalculatorStack();
        Pop pop = new Pop();
        ArrayList<Object> args = new ArrayList<>();
        stack.push(1.0);
        stack.push(2.0);
        pop.exec(stack, args);
        Assertions.assertEquals(1.0, stack.pop());

        args.clear();
        stack.createVar("a", 1.0);
        stack.push(2.0);
        args.add("a");
        pop.exec(stack, args);
        stack.push("a");
        Assertions.assertEquals(2.0, stack.pop());

        args.clear();
        args.add(1.0);
        args.add("a");
        Assertions.assertThrows(OperationException.class, () -> pop.exec(stack, args));

        args.clear();
        args.add(1.0);
        Assertions.assertThrows(OperationException.class, () -> pop.exec(stack, args));
    }

    @Test
    public void testPrint() throws Exception {
        ByteArrayOutputStream outContent = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outContent));
        CalculatorStack stack = new CalculatorStack();
        Print print = new Print();
        ArrayList<Object> args = new ArrayList<>();
        stack.push(1.0);
        print.exec(stack, args);
        Assertions.assertEquals("1.0", outContent.toString().trim());

        args.clear();
        args.add(1.0);
        Assertions.assertThrows(OperationException.class, () -> print.exec(stack, args));
    }

    @Test
    public void testPush() throws Exception {
        CalculatorStack stack = new CalculatorStack();
        Push push = new Push();
        ArrayList<Object> args = new ArrayList<>();
        args.add(1.0);
        push.exec(stack, args);
        Assertions.assertEquals(1.0, stack.pop());

        args.clear();
        Define define = new Define();
        args.add("a");
        args.add(2.0);
        define.exec(stack, args);

        args.clear();
        args.add("a");
        push.exec(stack, args);
        Assertions.assertEquals(2.0, stack.pop());

        args.clear();
        args.add(stack);
        Assertions.assertThrows(OperationException.class, () -> push.exec(stack, args));

        args.clear();
        args.add("a");
        args.add(stack);
        Assertions.assertThrows(OperationException.class, () -> push.exec(stack, args));
    }

    @Test
    public void testSqrt() throws Exception {
        CalculatorStack stack = new CalculatorStack();
        Sqrt sqrt = new Sqrt();
        ArrayList<Object> args = new ArrayList<>();
        stack.push(4.0);
        sqrt.exec(stack, args);
        Assertions.assertEquals(2.0, stack.pop());

        args.clear();
        args.add(1.0);
        Assertions.assertThrows(OperationException.class, () -> sqrt.exec(stack, args));
    }

    @Test
    public void testCalcStackPush() throws Exception {
        CalculatorStack stack = new CalculatorStack();
        ArrayList<Object> args = new ArrayList<>();
        Assertions.assertThrows(UnknownVariableException.class , () -> stack.push("a"));
    }
}






