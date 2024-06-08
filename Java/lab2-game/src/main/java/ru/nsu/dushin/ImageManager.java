package ru.nsu.dushin;

import javax.swing.*;
import java.awt.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.io.InputStream;

public abstract class ImageManager {
    private static final Map<String, Image> imagesMap = new HashMap<>();
    static {
        try (InputStream inputStream = ImageManager.class.getResourceAsStream("/config");
             Scanner scanner = new Scanner(inputStream)) {
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] parts = line.split(" ");

                String opName = parts[0].toLowerCase();
                String imagePath = parts[1];
                Image image = new ImageIcon(ImageManager.class.getResource(imagePath)).getImage();
                imagesMap.put(opName, image);
            }
        } catch (Throwable e) {
            System.out.println("Error while reading the configuration file: " + e.getMessage());
        }
    }

    public static Image getImage(String name) {
        name = name.toLowerCase();
        return imagesMap.get(name);
    }
}