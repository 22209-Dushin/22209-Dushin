package ru.nsu.dushin;

import javax.swing.*;
import java.awt.event.*;

public class GameController {
    private final GameModel model;
    private final GameView view;
    private final Timer gameLoop;
    private final GameListener gameListener = new GameListener();

    public GameController(GameModel model, GameView view) {
        this.model = model;
        this.view = view;

        MenuListener menuListener = new MenuListener();
        view.getPlayButton().addActionListener(menuListener);
        view.addKeyListener(gameListener);

        gameLoop = new Timer(1000 / 60, gameListener);
        view.playMusic();
    }

    class GameListener implements ActionListener, KeyListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            if (!model.isPaused() && model.getGameState() == GameState.STARTED) {
                model.update();
            }
            view.repaint();
            if (model.getGameState() == GameState.GAMEOVER) {
                view.playSE(0);
                view.getPlayButton().setVisible(true);
                gameLoop.stop();
            }
        }

        @Override
        public void keyPressed(KeyEvent e) {
            if (e.getKeyCode() == KeyEvent.VK_SPACE && model.getGameState() == GameState.STARTED) {
                model.setVelocityY(-9);
                view.playSE(1);
            } else if (e.getKeyCode() == KeyEvent.VK_SPACE && model.getGameState() == GameState.TAPMENU) {
                model.setGameState(GameState.STARTED);
                model.setVelocityY(-9);
                view.playSE(1);
            } else if (e.getKeyCode() == KeyEvent.VK_P && model.getGameState() == GameState.STARTED) {
                model.togglePause();
                if (model.isPaused()) {
                    model.setStartPauseTime(System.currentTimeMillis());
                } else {
                    long endPauseTime = System.currentTimeMillis();
                    model.changeTimePause(endPauseTime);
                }
            }
        }

        @Override
        public void keyReleased(KeyEvent e) {}

        @Override
        public void keyTyped(KeyEvent e) {}
    }

    class MenuListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {
            if (e.getActionCommand().equals("play") && model.getGameState() != GameState.GAMEOVER) {
                view.getPlayButton().setVisible(false);
                model.setGameState(GameState.TAPMENU);
                gameLoop.start();
            } else if (e.getActionCommand().equals("play")) {
                view.getPlayButton().setVisible(false);
                model.setGameState(GameState.TAPMENU);
                model.restart();
                gameLoop.start();
            }
        }
    }
}

