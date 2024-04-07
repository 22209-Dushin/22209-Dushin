package ru.nsu.dushin.main;

import ru.nsu.dushin.calculator.Interpretator;

import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;

public class Main {
    public static Reader createReader(String[] args) throws IOException {
        if (args.length > 0) {
            return new FileReader(args[0]);
        }
        return new InputStreamReader(System.in);
    }

    public static void main(String[] args) {
        try (Reader reader = createReader(args)) {
            Interpretator interpretator = new Interpretator(reader);
            interpretator.execute();
        }catch (IOException e)) {
            System.out.println("Error " + e.getMessage());
        }
    }
}