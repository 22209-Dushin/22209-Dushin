package ru.nsu.dushin.calculator;

import ru.nsu.dushin.exception.*;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import ru.nsu.dushin.operation.*;

import java.io.*;
import java.util.ArrayList;

public class TestInterpretator {
    @Test
    void testExec() throws OperationException {
        CalculatorStack stack = new CalculatorStack();
        ArrayList<Object> args = new ArrayList<>();
        Define define = new Define();

        args.add("a");
        args.add(1.0);
        define.exec(stack, args);
        stack.push("a");
        Assertions.assertEquals(1.0, stack.pop());

        args.clear();
        args.add(1);
        args.add(1.0);
        Assertions.assertThrows(ExecuteOperationException.class, () -> define.exec(stack, args));


        args.clear();
        args.add("a");
        args.add("b");
        Assertions.assertThrows(ExecuteOperationException.class, () -> define.exec(stack, args));

        args.clear();
        args.add("a");
        Assertions.assertThrows(OperationException.class, () -> define.exec(stack, args));

    }

    @Test
    public void testCalcExec() throws OperationException {
        ByteArrayOutputStream outContent = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outContent));
        String testInput = "DEFINE a 20\n" + "PUSH a\n" +
                "PUSH 100\n" +
                "Define b 1\n" +
                "PUSH b\n" +
                "+\n" +
                "+\n" +
                "sqrt\n" +
                "push -1\n" +
                "#hello\n" +
                "*\n" +
                "pUsH -11\n" +
                "*\n" +
                "sqrt\n" +
                "pop a\n" +
                "push a\n" +
                "print\n";
        Reader reader = new StringReader(testInput);
        Interpretator interpretator = new Interpretator(reader);
        interpretator.execute();
        String expectedOutput = "11.0";
        Assertions.assertEquals(expectedOutput, outContent.toString().trim());
    }

    @Test
    public void testCalcExecThrow() throws OperationException {
        ByteArrayOutputStream outContent = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outContent));
        String testInput = "pop\n";
        Reader reader = new StringReader(testInput);
        Interpretator interpretator = new Interpretator(reader);
        interpretator.execute();
    }


    @Test
    public void testGetOperationUnknown()  {
        Assertions.assertThrows(UnknownOperationException.class, () -> OperationFactory.getOperation("unknown"));
    }
    @Test
    void testConstructor() {
        IncorrectFileConfigurationException exception = new IncorrectFileConfigurationException("test message");
        Assertions.assertEquals("test message", exception.getMessage());
    }

    @Test
    public void testStackException() throws VariableAlreadyExistsException {
        CalculatorStack stack = new CalculatorStack();
        Assertions.assertThrows(EmptyStackException.class, () -> stack.peek());
        Assertions.assertThrows(EmptyStackException.class, () -> stack.pop());
        stack.createVar("a", 1.0);
        Assertions.assertThrows(VariableAlreadyExistsException.class, () -> stack.createVar("a", 1.0));
        Assertions.assertThrows(UnknownVariableException.class, () -> stack.pop("b"));
    }

}
