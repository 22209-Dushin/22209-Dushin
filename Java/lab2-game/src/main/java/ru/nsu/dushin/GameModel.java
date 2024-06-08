package ru.nsu.dushin;

import java.util.ArrayList;
import static ru.nsu.dushin.RecordManager.*;

public class GameModel {
    private static final int PIPE_SPAWN_INTERVAL = 1500;
    public static final int BOARD_WIDTH          = 360;
    public static final int BOARD_HEIGHT         = 640;
    private static final int GRAVITY             = 1;
    private GameState gameState;
    private final Bird bird = new Bird(BOARD_WIDTH / 8, BOARD_HEIGHT / 2);
    private ArrayList<Pipe> pipes = new ArrayList<>();
    private int score = 0;
    private int velocityY = 0;
    private final int velocityX = -4;
    private boolean paused = false;
    private long lastUpdateTime;
    private long timePause = 0;
    private long startPauseTime = 0;

    public GameModel() {
        lastUpdateTime = System.currentTimeMillis();
        gameState = GameState.MENU;
        loadRecord();
    }

    public void restart(){
        checkNewRecord();
        score = 0;
        velocityY = 0;
        gameState = GameState.TAPMENU;
        bird.setY(BOARD_HEIGHT / 2);
        pipes.clear();
    }

    private boolean collision(Pipe pipe){
        boolean pipeTop = bird.getX() < pipe.getX() + Pipe.WIDTH && bird.getX() + Bird.WIDTH > pipe.getX()
                && bird.getY() < pipe.getY() + Pipe.HEIGHT && bird.getY() + Bird.HEIGHT > pipe.getY();

        boolean pipeBottom = bird.getX() < pipe.getX() + Pipe.WIDTH && bird.getX() + Bird.WIDTH > pipe.getX()
                && bird.getY() < pipe.getY() + Pipe.HEIGHT + Pipe.HEIGHT + BOARD_HEIGHT / 4 &&
                bird.getY() + Bird.HEIGHT > pipe.getY() + Pipe.HEIGHT + BOARD_HEIGHT / 4;

        return pipeTop || pipeBottom;
    }

    public void update() {
        long currentTime = System.currentTimeMillis();

        if (currentTime - lastUpdateTime - timePause > PIPE_SPAWN_INTERVAL){
            placePipes();
            lastUpdateTime = currentTime;
            timePause = 0;
        }

        velocityY += GRAVITY;
        bird.addY(velocityY);
        bird.setY(Math.max(0, bird.getY()));

        updatePipes();

        pipes.removeIf(pipe -> pipe.getX() + Pipe.WIDTH < 0);

        checkGameOver();
    }
    private void updatePipes(){
        for (Pipe pipe : pipes) {
            pipe.addX(velocityX);
            if (!pipe.isPassed() && bird.getX() > pipe.getX() + Pipe.WIDTH) {
                pipe.setPassed();
                score++;
            }
            if (collision(pipe)) {
                gameState = GameState.GAMEOVER;
            }
        }
    }

    private void placePipes(){
        int randomPipeY = (int) (-Pipe.HEIGHT / 4 - Math.random() * (Pipe.HEIGHT / 2));
        Pipe pipe = new Pipe();
        pipe.setY(randomPipeY);
        pipes.add(pipe);
    }
    private void checkGameOver(){
        if (bird.getY() > BOARD_HEIGHT) {
            gameState = GameState.GAMEOVER;
        }
    }
    private void checkNewRecord() {
        if (score > getRecord()) {
            saveRecord(score);
        }
    }

    public void togglePause() { paused = !paused; }
    public boolean isPaused() { return paused; }

    public GameState getGameState() { return gameState; }
    public void setGameState(GameState gameState) { this.gameState = gameState; }

    public ArrayList<Pipe> getPipes() { return pipes; }

    public Bird getBird() {return bird;}

    public int getRecord() { return RecordManager.getRecord();}

    public int getScore() { return score; }

    public int getVelocityY() { return velocityY; }

    public void setVelocityY(int v) { velocityY = v; }

    public void setStartPauseTime(long t) { startPauseTime = t; }

    public void changeTimePause(long endPauseTime) {
        timePause += endPauseTime - startPauseTime;
    }
}

enum GameState {
    MENU,
    TAPMENU,
    STARTED,
    GAMEOVER
}
