package ru.nsu.dushin.main;

import ru.nsu.dushin.calculator.Interpretator;

import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;

public class Main {
    private static Reader reader;
    public static void checkArgs(String[] args) {
        if (args.length > 0) {
            try (FileReader in = new FileReader(args[0])) {
                reader = in;
            } catch (IOException e) {
                System.out.println("Error " + e.getMessage());
            }
        }
        else {
            try (InputStreamReader in = new InputStreamReader(System.in)) {
                reader = in;
            } catch (IOException e) {
                System.out.println("Error " + e.getMessage());
            }
        }
    }
    public static void main(String[] args) {
        checkArgs(args);
        Interpretator interpretator = new Interpretator(reader);
        interpretator.execute();
    }
}