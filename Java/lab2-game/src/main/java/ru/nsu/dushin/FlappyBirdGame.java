package ru.nsu.dushin;

import javax.swing.*;
import java.awt.*;

public class FlappyBirdGame {
    public static void createFrame(GameView view) {
        JFrame frame = new JFrame("Flappy Bird");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        ImageIcon icon = new ImageIcon(FlappyBirdGame.class.getResource("/bluebird-upflap.png"));
        Image image = icon.getImage();

        Image resizedImage = image.getScaledInstance(48, 38, Image.SCALE_SMOOTH);

        frame.setIconImage(resizedImage);
        frame.add(view);
        frame.pack();
        frame.setLocationRelativeTo(null);
        frame.setResizable(false);
        frame.requestFocus();
        frame.setVisible(true);
    };
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() ->
        {
            GameModel model = new GameModel();
            GameView view = new GameView(model);
            GameController controller = new GameController(model, view);
            createFrame(view);
        });
    }
}