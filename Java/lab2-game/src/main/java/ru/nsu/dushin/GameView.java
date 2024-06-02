package ru.nsu.dushin;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.IOException;

public class GameView extends JPanel {
    private final GameModel model;
    private final JButton playButton;
    private final Sound sound = new Sound();
    private final BufferedImage[] digits = new BufferedImage[10];

    public GameView(GameModel model)  {
        this.model = model;

        setLayout(null);
        setPreferredSize(new Dimension(GameModel.BOARD_WIDTH, GameModel.BOARD_HEIGHT));
        setFocusable(true);

        playButton = new JButton();

        ImageIcon resizedPlayIcon = new ImageIcon(ImageManager.getImage("playButtonImg").getScaledInstance(200, 100, java.awt.Image.SCALE_SMOOTH));
        playButton.setIcon(resizedPlayIcon);
        playButton.setPreferredSize(new Dimension(200, 100));
        playButton.setBounds(80,400,200,100);
        playButton.setBorderPainted(false);
        playButton.setContentAreaFilled(false);
        playButton.setActionCommand("play");
        this.add(playButton);
        this.setVisible(true);

        loadDigitsimage();
    }
    public JButton getPlayButton(){
        return playButton;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        draw(g);
    }

    public void playMusic() {
        //sound.setFile(2);
        sound.play(2);
        sound.loop(2);
    }

    public void playSE(int i) {
       // sound.setFile(i);
        sound.play(i);
    }

    private void loadDigitsimage() {
        for (int i = 0; i < 10; i++) {
            try {
                digits[i] = ImageIO.read(getClass().getResource("/number_medium_" + i + ".png"));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void draw(Graphics g) {
        drawBackground(g);

        if (model.getGameState() == GameState.MENU) {
            drawGameMenu(g);
            return;
        }
        if (model.getGameState() == GameState.TAPMENU) {
            drawStartScreen(g);
        } else {
            drawBird(g);
            drawPipes(g);
            drawNumber(g, model.getScore(), 5, 5,21, 30,18);
            if (model.getGameState() == GameState.GAMEOVER) {
                g.drawImage(ImageManager.getImage("panelScoreImg"), 36, 200, 288, 150, null);
                g.drawImage(ImageManager.getImage("gameOverImg"), 36, 88, 288, 63, null);
                drawMedal(g);
                drawNumber(g, model.getScore(), 262, 250,10, 14,5);
                drawNumber(g, model.getRecord(),262,300, 10, 14, 5);
            } else if (model.isPaused()) {
                g.drawImage(ImageManager.getImage("pauseImg"), 36, 288, 288, 288, null);
            }
        }
    }

    private void drawBackground(Graphics g) {
        g.drawImage(ImageManager.getImage("backgroundImg"), 0, 0, null);
    }
    private void drawGameMenu(Graphics g) {
        g.drawImage(ImageManager.getImage("labelImg"), 46, 113, 267, 75, null);
        g.drawImage(ImageManager.getImage("upBirdImg"),(360 - (model.getBird().getX() + 18)) / 2, 250, Bird.WIDTH + 18, Bird.HEIGHT + 13, null);
    }
    private void drawStartScreen(Graphics g) {
        g.drawImage(ImageManager.getImage("startImg"), 46, 50, 267, 414, null);
        g.drawImage(ImageManager.getImage("midBirdImg"), model.getBird().getX(), model.getBird().getY(), Bird.WIDTH , Bird.HEIGHT , null);
    }

    private void drawPipes(Graphics g) {
        for (Pipe pipe : model.getPipes()) {
            g.drawImage(ImageManager.getImage("topPipeImg"), pipe.getX(), pipe.getY(), Pipe.WIDTH, Pipe.HEIGHT, null);
            g.drawImage(ImageManager.getImage("bottomPipeImg"), pipe.getX(), pipe.getY() + Pipe.HEIGHT + GameModel.BOARD_HEIGHT/ 4, Pipe.WIDTH, Pipe.HEIGHT, null);
        }
    }

    private void drawNumber(Graphics g, int number, int x, int y, int w, int h, int offset) {
        String numberString = String.valueOf(number);
        for (int i = 0; i < numberString.length(); i++) {
            char digitChar = numberString.charAt(i);
            int digit = Character.getNumericValue(digitChar);
            BufferedImage digitImage = digits[digit];
            g.drawImage(digitImage, x, y, w, h,null);
            x += digitImage.getWidth() + offset;
        }
    }

    private void drawMedal(Graphics g) {
        int score = model.getScore();

        if(score > 9 && score < 20){
            g.drawImage(ImageManager.getImage("medalBronzeImg"),68, 258,60, 60, null);
        }else if (score > 19 && score < 30){
            g.drawImage(ImageManager.getImage("medalSilverImg"),68, 258,60, 60, null);
        }else if (score > 29){
            g.drawImage(ImageManager.getImage("medalGoldImg"),68, 258,60, 60, null);
        }
    }
    private void drawBird(Graphics g) {
        Image birdImage;
        int velocityY = model.getVelocityY();

        if (velocityY == 0) {
            birdImage = ImageManager.getImage("midBirdImg");
        } else if (velocityY > 0) {
            birdImage = ImageManager.getImage("upBirdImg");
        } else {
            birdImage = ImageManager.getImage("downBirdImg");
        }

        double angle = Math.toDegrees(Math.atan((double) velocityY / 8 - 0.5));

        int centerX = model.getBird().getX() + Bird.WIDTH / 2;
        int centerY = model.getBird().getY() + Bird.HEIGHT / 2;

        Graphics2D g2d = (Graphics2D) g;
        AffineTransform old = g2d.getTransform();
        g2d.rotate(Math.toRadians(angle), centerX, centerY);
        g.drawImage(birdImage, model.getBird().getX(), model.getBird().getY(), Bird.WIDTH, Bird.HEIGHT, null);
        g2d.setTransform(old);
    }
}
