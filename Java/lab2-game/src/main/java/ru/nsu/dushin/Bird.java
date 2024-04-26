package ru.nsu.dushin;

class Bird {
    public static final int WIDTH = 40;
    public static final int HEIGHT = 28;
    private final int x;
    private int y;
    public Bird(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() { return x;}
    public int getY() { return y; }
    public void setY(int y) { this.y = y; }
    public void addY(int dy) { this.y += dy; }
}
