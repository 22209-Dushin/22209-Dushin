package ru.nsu.ccfit.dushin;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class Counter {
    private int wordsCount = 0;
    public Map<String, Integer> countWords(String fileName) {
        Map<String, Integer> wordMap = new HashMap<>();

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(fileName), StandardCharsets.UTF_8))){
            StringBuilder wordBuilder = new StringBuilder();
            int c;

            while ((c = reader.read()) != -1) {
                char character = Character.toLowerCase((char) c);

                if (Character.isLetterOrDigit(character)) {
                    wordBuilder.append(character);
                } else {
                    if (!wordBuilder.isEmpty()) {
                        String word = wordBuilder.toString();
                        wordMap.put(word, wordMap.getOrDefault(word, 0) + 1);
                        wordBuilder.setLength(0);
                        wordsCount++;
                    }
                }
            }

            if (!wordBuilder.isEmpty()) {
                String word = wordBuilder.toString();
                wordMap.put(word, wordMap.getOrDefault(word, 0) + 1);
                wordsCount++;
            }
        } catch (IOException e) {
            e.printStackTrace(System.err);
        }

        return wordMap;
    }

    public List<Map.Entry<String, Integer>> sortWords(Map<String, Integer> wordMap) {
        List<Map.Entry<String, Integer>> sortedList = new ArrayList<>(wordMap.entrySet());

        sortedList.sort(Map.Entry.comparingByValue(Comparator.reverseOrder()));

        return sortedList;
    }

    public void writeWordsToCSVFile(List<Map.Entry<String, Integer>> wordList, String fileName) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(fileName))) {
            writer.println("Word, Frequency, Frequency (%)");

            for (Map.Entry<String, Integer> entry : wordList) {
                double frequency = (double) entry.getValue() / wordsCount * 100;
                writer.println(entry.getKey() + ", " + entry.getValue() + ", " + frequency);
            }
        } catch (IOException e) {
            e.printStackTrace(System.err);
        }
    }

    public static void main(String[] args) {
        if (args.length == 2) {
            Counter wordCounter = new Counter();

            Map<String, Integer> wordMap = wordCounter.countWords(args[0]);

            List<Map.Entry<String, Integer>> sortedWords = wordCounter.sortWords(wordMap);

            wordCounter.writeWordsToCSVFile(sortedWords, args[1]);
        }
        else {
            System.out.println("Неправильное кличество аргументов!");
        }
    }
}